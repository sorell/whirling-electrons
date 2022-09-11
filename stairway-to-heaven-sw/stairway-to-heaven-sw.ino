#include "BtnDebounce.h"

#define BUTTON_IN 3
#define LED1_OUT 4
#define LED2_OUT 5
#define LED3_OUT 6

#define SLICE_OFFSET (6)
#define PWM_SLICE (1UL << SLICE_OFFSET)  // Smallest slice of pwm time is 2^6 = 64 us
#define PWM_PERIOD (PWM_SLICE * 256UL)  // Full pwm period is 16,384 ms => 61 Hz led freq
#define PERIOD_OFFSET (SLICE_OFFSET + 8)
#define PERIOD_DISCARDED_BITS (PWM_PERIOD - 1)
#define PERIOD_BITMASK (~PERIOD_DISCARDED_BITS)
#define SLICE_DISCARDED_BITS (PWM_SLICE - 1)
#define SLICE_BITMASK (PERIOD_DISCARDED_BITS & (~SLICE_DISCARDED_BITS))

#define PERIOD_NR(x) (((x) & PERIOD_BITMASK) >> PERIOD_OFFSET)
#define SLICE_NR(x) (((x) & SLICE_BITMASK) >> SLICE_OFFSET)

#if (((PERIOD_DISCARDED_BITS + 1) & PERIOD_DISCARDED_BITS) != 0)
#error PERIOD_DISCARDED_BITS is not a continuous bitmask
#endif
#if (((SLICE_DISCARDED_BITS + 1) & SLICE_DISCARDED_BITS) != 0)
#error SLICE_DISCARDED_BITS is not a continuous bitmask
#endif


class LedIo
{
public:
	LedIo(uint8_t pin) : _reg(portOutputRegister(digitalPinToPort(pin))), _bitMask(digitalPinToBitMask(pin))
	{}

	__attribute__((always_inline)) void set() const
	{
		*_reg |= _bitMask;
	}

	__attribute__((always_inline)) void clr() const
	{
		*_reg &= ~_bitMask;
	}

	__attribute__((always_inline)) void write(int value) const
	{
		if (value >= 0)
			set();
		else
			clr();
	}

	__attribute__((always_inline)) void write(uint8_t *const byte, int value) const
	{
		if (value >= 0)
			*byte |= _bitMask;
		else
			*byte &= ~_bitMask;
	}

private:
	uint8_t volatile *const _reg;
	uint8_t const _bitMask;
};


class LedStrip
{
public:
	LedStrip(uint8_t pinR, uint8_t pinG, uint8_t pinB) : _ledIoR(pinR), _ledIoG(pinG), _ledIoB(pinB), _ledBrightnessR(0), _ledBrightnessG(0), _ledBrightnessB(0)
	{
		digitalWrite(pinR, 1);
		digitalWrite(pinG, 1);
		digitalWrite(pinB, 1);
		pinMode(pinR, OUTPUT);
		pinMode(pinG, OUTPUT);
		pinMode(pinB, OUTPUT);
	}

	__attribute__((always_inline)) void set() const
	{
		_ledIoR.set();
		_ledIoG.set();
		_ledIoB.set();
	}

	void write(uint16_t frame) const
	{
		// The FET is open when Gate is at 0V.
		// Led's value (r, g and b) tells at which frame of [0..255] it will be lit.
		// With led value of:
		//  - 0 => none of the frames are lit,
		//  - 1 => frame number 0 is lit,
		//  - 255 => all 256 frames are lit.
		// Calculate this in if-less way: MSB of uint16_t signifies is the frame lit or not.
		++frame;

		_ledIoR.write(_ledBrightnessR - frame);
		_ledIoG.write(_ledBrightnessG - frame);
		_ledIoB.write(_ledBrightnessB - frame);

		// digitalWrite(_pinR, (_ledBrightnessR - frame) >> 15);
		// digitalWrite(_pinG, (_ledBrightnessG - frame) >> 15);
		// digitalWrite(_pinB, (_ledBrightnessB - frame) >> 15);
	}

	void write(uint8_t *const byte, int frame) const
	{
		_ledIoR.write(byte, _ledBrightnessR - frame);
		_ledIoG.write(byte, _ledBrightnessG - frame);
		_ledIoB.write(byte, _ledBrightnessB - frame);
	}

private:
	LedIo const _ledIoR;
	LedIo const _ledIoG;
	LedIo const _ledIoB;

public:
	uint16_t _ledBrightnessR;
	uint16_t _ledBrightnessG;
	uint16_t _ledBrightnessB;
};

static LedStrip strips[]
{
	{11, 10, 8},
	{3, 4, 2},
	{14, 15, 13},
	{7, 9, 6},
	{17, 18, 16},
	{21, 22, 20},
	{30, 31, 29},
	{A11, A9, A13},
	{A0, A1, A2},
	{33, A14, 32},
	{A5, A4, A11},
	{34, 35, 37},
	{38, 39, 40},
	{48, 49, 51}
};

static constexpr int stripCount = sizeof(strips) / sizeof(strips[0]);


static BtnDebounce button(BUTTON_IN, 0);


// Printf callback function
int SerialPutc(char c, __attribute__((unused)) FILE *f)
{
	return Serial.write(c);
}


// 3 * 14 looped writes = 24 us
// 3 * 14 inlined set functions (or) = 40 us
// 3 * 14 inlined set functions (assign) = 32 us

void setup()
{
	pinMode(BUTTON_IN, INPUT_PULLUP);

	
	Serial.begin(115200);
	fdevopen(&SerialPutc, 0);

	printf(" Slice mask is %08lx\n", SLICE_BITMASK);
	printf("Period mask is %08lx\n", PERIOD_BITMASK);

	// Wait until the end of PWM period so that loop() begins at the start of a new period
	// unsigned long const currentPeriod = micros() & PERIOD_BITMASK;
	// while ((micros() & PERIOD_BITMASK) == currentPeriod);


	auto const &strip = strips[0];
	uint8_t volatile *const reg = portOutputRegister(digitalPinToPort(31));
	uint8_t byte[stripCount] = {0};
	uint8_t _bitMask = 0x30;

	unsigned long const t0 = micros();

	for (auto const &strip: strips)
	// for (int i=0; i<stripCount; ++i)
	{
		strip.set();
		// strips[i].write(&byte[i], 1);
	}

	// digitalWriteFast(11, 1);
	// digitalWriteFast(10, 1);
	// digitalWriteFast(8, 1);


	unsigned long const t1 = micros();

	printf("write all %lu\n", t1 - t0);

	for (auto b: byte)
	{
		printf("Byte %x\n", b);
	}


	while (1)
	{
		break;
		// strips[6].write(1);
		// delay(1000);
		// strips[6].write(0);
		// delay(1000);
	}
}


static void processSensors()
{
	if (button.isPressed()) {
		// if ((uint8_t)(brightness + brightnessInc) < brightness) {
		// 	if (++mode > 0x7) {
		// 		mode = 1;
		// 	}
		// }
		// brightness += brightnessInc;
		// led.r = (mode & ModeR) != 0 ? brightness : 0;
		// led.g = (mode & ModeG) != 0 ? brightness : 0;
		// led.b = (mode & ModeB) != 0 ? brightness : 0;
		
		// printf("Led %d, %d, %d; %d\n", led.r, led.g, led.b, rounds);
	}
}


struct ColorDelta
{
	int16_t r;
	int16_t g;
	int16_t b;
};


static ColorDelta colorDelta[stripCount]
{
	{4000, 0, 0},
	{0, 4000, 0},
	{0, 0, 4000},
	{4000, 0, 0},
	{0, 4000, 0},
	{0, 0, 4000},
	{4000, 0, 0},
	{0, 4000, 0},
	{0, 0, 4000},
	{4000, 0, 0},
	{0, 4000, 0},
	{0, 0, 4000},
	{0, 4000, 0},
	{0, 0, 4000}
};


static void fadeUpLights()
{
	auto inc = [](uint16_t &value, int16_t increment)
	{
		uint16_t const result = value + increment;
		if (value < result) {
			value = result;
		}
	};


	int i = 0;

	do
	{
		unsigned long now = micros();
	// printf("in %lu\n", now & 0x7F800);
		if ((now & 0x1F800) != 0x1F800) {
			continue;
		}

		// for (int stage = i >> 2; stage >= 0; --stage)
		// {
		// 	strips[stage]._ledBrightnessR += colorDelta[stage].r;
		// 	strips[stage]._ledBrightnessG += colorDelta[stage].g;
		// 	strips[stage]._ledBrightnessB += colorDelta[stage].b;
		// }

	// debug for loop
		for (int stage = 0; stage < stripCount; ++stage)
		{
			inc(strips[stage]._ledBrightnessR, colorDelta[stage].r);
			inc(strips[stage]._ledBrightnessG, colorDelta[stage].g);
			inc(strips[stage]._ledBrightnessB, colorDelta[stage].b);
		}
	unsigned long const t1 = micros();
	printf("write all %lu\n", t1 - now);
	
		++i;

		int idx = 0;
		for (auto const &strip: strips)
		{
			printf("%d: %d, %d, %d\n", idx++, strip._ledBrightnessR >> 8, strip._ledBrightnessG >> 8, strip._ledBrightnessB >> 8);
		}
	} while (strips[0]._ledBrightnessR < 60000);
}


void loop()
{
	fadeUpLights();



	while (1);


	// static uint8_t constexpr brightnessInc = 64;
	// static uint8_t brightness = 0;
	// static uint8_t mode = 1;
	// static Led led = {0, 0, 0};
	// static uint8_t constexpr ModeR = 1 << 0;
	// static uint8_t constexpr ModeG = 1 << 1;
	// static uint8_t constexpr ModeB = 1 << 2;
	static int rounds = 0;

	// Wait for the start of the next PWM period
	while ((micros() & SLICE_BITMASK) != 0);

	if ((PERIOD_NR(micros()) & 64) == 0)
	{
		printf("%d\n", rounds);
	}

	rounds = 0;
	uint8_t prevSlice = 255;
	while (1) {
		uint8_t slice;

		for (auto const *strip = strips; strip < strips + stripCount; ++strip)
		{
			strip->write(0);
		}

		do {
			unsigned long const now = micros();
			slice = SLICE_NR(now);
			++rounds;
		} while (slice == prevSlice);

		prevSlice = slice;

		// digitalWrite(LED1_OUT, slice < led.r);
		// digitalWrite(LED2_OUT, slice < led.g);
		// digitalWrite(LED3_OUT, slice < led.b);
		// printf("led %d %d %d\n", slice < led.r, slice < led.g, slice < led.b);

		if (slice == 255) {
			break;
		}
	};
}
