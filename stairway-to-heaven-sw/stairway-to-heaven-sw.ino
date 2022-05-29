#include "BtnDebounce.h"

#define BUTTON_IN 3
#define LED1_OUT 4
#define LED2_OUT 5
#define LED3_OUT 6

#define SLICE_OFFSET 7  // 
#define PWM_SLICE (1UL << SLICE_OFFSET)  // Smallest slice of pwm time is 128 us
#define PWM_PERIOD (PWM_SLICE * 256UL)  // Full pwm period is 32,768 ms
#define PERIOD_DISCARDED_BITS (PWM_PERIOD - 1)
#define PERIOD_BITMASK (~PERIOD_DISCARDED_BITS)
#define SLICE_DISCARDED_BITS (PWM_SLICE - 1)
#define SLICE_BITMASK (PERIOD_DISCARDED_BITS & (~SLICE_DISCARDED_BITS))

#if ((PERIOD_DISCARDED_BITS + 1) & PERIOD_DISCARDED_BITS)
#error PERIOD_DISCARDED_BITS is not a continuous bitmask
#endif
#if ((SLICE_DISCARDED_BITS + 1) & SLICE_DISCARDED_BITS)
#error SLICE_DISCARDED_BITS is not a continuous bitmask
#endif


struct Led
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};


BtnDebounce button(BUTTON_IN, 0);


FILE f_out;
int SerialPutc(char c, __attribute__((unused)) FILE* f) {return !Serial.write(c);}


void setup()
{
	pinMode(BUTTON_IN, INPUT_PULLUP);
	digitalWrite(LED1_OUT, 1);
	digitalWrite(LED2_OUT, 1);
	digitalWrite(LED3_OUT, 1);
	pinMode(LED1_OUT, OUTPUT);
	pinMode(LED2_OUT, OUTPUT);
	pinMode(LED3_OUT, OUTPUT);
	
	Serial.begin(115200);
	fdevopen(&SerialPutc, 0);

	printf(" Slice mask is %08lx\n", SLICE_BITMASK);
	printf("Period mask is %08lx\n", PERIOD_BITMASK);

	// Wait until the end of PWM period so that loop() begins at the start of a new period
	// unsigned long const currentPeriod = micros() & PERIOD_BITMASK;
	// while ((micros() & PERIOD_BITMASK) == currentPeriod);
}

void loop()
{
	static uint8_t constexpr brightnessInc = 64;
	static uint8_t brightness = 0;
	static uint8_t mode = 1;
	static Led led = {0, 0, 0};
	static uint8_t constexpr ModeR = 1 << 0;
	static uint8_t constexpr ModeG = 1 << 1;
	static uint8_t constexpr ModeB = 1 << 2;
	static int rounds = 0;

	if (button.isPressed()) {
		if ((uint8_t)(brightness + brightnessInc) < brightness) {
			if (++mode > 0x7) {
				mode = 1;
			}
		}
		brightness += brightnessInc;
		led.r = (mode & ModeR) != 0 ? brightness : 0;
		led.g = (mode & ModeG) != 0 ? brightness : 0;
		led.b = (mode & ModeB) != 0 ? brightness : 0;
		
		printf("Led %d, %d, %d; %d\n", led.r, led.g, led.b, rounds);
	}

	while ((micros() & SLICE_BITMASK) != 0);

	rounds = 0;
	while (1) {
		unsigned long const now = micros();
		int const sliceBits = (now & SLICE_BITMASK);
		uint8_t const slice = sliceBits >> SLICE_OFFSET;

		digitalWrite(LED1_OUT, slice < led.r);
		digitalWrite(LED2_OUT, slice < led.g);
		digitalWrite(LED3_OUT, slice < led.b);
		// printf("led %d %d %d\n", slice < led.r, slice < led.g, slice < led.b);

		++rounds;
		if (sliceBits == SLICE_BITMASK) {
			break;
		}
	};
}
