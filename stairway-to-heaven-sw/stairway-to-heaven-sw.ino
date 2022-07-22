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


struct Led
{
	Led() : r(0), g(0), b(0)
	{}

	Led(uint16_t rValue, uint16_t gValue, uint16_t bValue) : r(rValue), g(gValue), b(bValue)
	{}

	uint16_t r;
	uint16_t g;
	uint16_t b;
};


struct LedStrip
{
	LedStrip(uint8_t pinR, uint8_t pinG, uint8_t pinB) : _pinR(pinR), _pinG(pinG), _pinB(pinB)
	{
		digitalWrite(pinR, 1);
		digitalWrite(pinG, 1);
		digitalWrite(pinB, 1);
		pinMode(pinR, OUTPUT);
		pinMode(pinG, OUTPUT);
		pinMode(pinB, OUTPUT);
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
		digitalWrite(_pinR, (led.r - frame) >> 15);
		digitalWrite(_pinG, (led.r - frame) >> 15);
		digitalWrite(_pinB, (led.r - frame) >> 15);
	}

	const uint8_t _pinR;
	const uint8_t _pinG;
	const uint8_t _pinB;
	Led led;
};

static LedStrip strips[]
{
	{30, 31, 29},
	{7, 6, 8},
	{3, 2, 4},
	{10, 9, 11},

	{7, 6, 8},
	{3, 2, 4},
	{10, 9, 11},
	{7, 6, 8},
	{3, 2, 4},
	{10, 9, 11},
	{7, 6, 8},
	{3, 2, 4},
	{10, 9, 11},
	{7, 6, 8},
	{3, 2, 4},
	{10, 9, 11},
};

static constexpr int stripCount = sizeof(strips) / sizeof(strips[0]);


static BtnDebounce button(BUTTON_IN, 0);


// Enable printf
int SerialPutc(char c, __attribute__((unused)) FILE* f)
{
	return Serial.write(c);
}


void setup()
{
	// pinMode(BUTTON_IN, INPUT_PULLUP);
	// digitalWrite(LED1_OUT, 1);
	// digitalWrite(LED2_OUT, 1);
	// digitalWrite(LED3_OUT, 1);
	// pinMode(LED1_OUT, OUTPUT);
	// pinMode(LED2_OUT, OUTPUT);
	// pinMode(LED3_OUT, OUTPUT);
	
	Serial.begin(115200);
	fdevopen(&SerialPutc, 0);

	printf(" Slice mask is %08lx\n", SLICE_BITMASK);
	printf("Period mask is %08lx\n", PERIOD_BITMASK);

	// Wait until the end of PWM period so that loop() begins at the start of a new period
	// unsigned long const currentPeriod = micros() & PERIOD_BITMASK;
	// while ((micros() & PERIOD_BITMASK) == currentPeriod);


	uint16_t ledr = 256;
	for (int i=0; i<257; ++i)
	{
		uint16_t frame = i + 1;
		uint8_t result = (uint8_t)((ledr - frame) >> 15);
		printf("led %d at frame %d = %d\n", ledr, i, result);
	}
	while (1);
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


void loop()
{
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
