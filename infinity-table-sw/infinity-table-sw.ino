#include <FastLED.h>
#include "ledUtils.h"
#include "algorithms.h"
#include "debug.h"

#define DATA_PIN 2
#define MAX_BRIGHT 255


/*----- Facts -----------------------------------------------------------------
 * - There are 260 leds in the table, in two rows.
 * - It takes:
 *   - 9,4 ms to draw all the 260 leds once.
 *   - 5,6 ms to fill leds array with floating point multiplied values
 *   - 0,4 ms to fill leds array with integer multiplied and shifted values
 * Does:
 *   Create a trail of colors gradually shifting from a color to another over
 *   specified number of leds.
 *
 * Wants:
 *   array: The LedArray to apply the color shift on.
 *   atFunc: The LedArray at() function used to determine starting position.
 *   beginColor: The color of the led at pos.
 *   endColor: The color of the last led of the applied color trail.
 *   pos: The position to start the trail from.
 *   amount: Number of leds to cover.
 *----------------------------------------------------------------------------*/


/*----- Dimension -------------------------------------------------------------
 *
 *  * * * * * * * * * .. * * * * * * * * *  <-- top1 (42)
 *   * * * * * * * * *..* * * * * * * * *   <-- top2 (41)
 *  *                                    *
 *   *                                  *
 *  *                                    *
 *   *                                  *
 *  *                                    *
 *   *                                  *
 *  .. <-- left1 (24)  right2 (23) -->  ..
 *  ..  <-- left2 (23)                  .. <-- right1 (24)
 *   *                                  *
 *  *                                    *
 *   *                                  *
 *  *                                    *
 *   *                                  *
 *  *                                    *
 *   * * * * * * * * *..* * * * * * * * *   <-- btm2 (41)
 *  * * * * * * * * * .. * * * * * * * * *  <-- btm1 (42)
 *  ^
 *  \- wire
 *----------------------------------------------------------------------------*/
#define NUM_LEDS 260
static CRGB leds[NUM_LEDS];

static LedArray all1(leds, 132);
static LedArray all2(leds + 132, 128);

static LedArray btm1(leds, 42);
static LedArray right1(leds + 42, 24);
static LedArray top1(leds + 66, 42);
static LedArray left1(leds + 108, 24);
static LedArray btm2(leds + 132, 41);
static LedArray right2(leds + 173, 23);
static LedArray top2(leds + 196, 41);
static LedArray left2(leds + 237, 23);


static SquaredVal const squaredVal;


/*----- Helper functions ------------------------------------------------------
 * Does:
 *   Library CRGB class initialization helper to set TwoBytes upper bytes to
 *   the actual color.
 *----------------------------------------------------------------------------*/
static inline CRGB CrgbInit(uint8_t const red, uint8_t const green, uint8_t const blue)
{
	return {.r = red, .g = green, .b = blue};
}

static inline CRGB CrgbInit(uint16_t const red, uint16_t const green, uint16_t const blue, int const scale)
{
	CRGB crgb {.r = (uint8_t)(red * scale / 100), 
		.g = (uint8_t)(green * scale / 100), 
		.b = (uint8_t)(blue * scale / 100)};
	Serial.print("scale = ");
	Serial.print(scale);
	Serial.print(": ");
	print(crgb);
	return crgb;
}


// Warning: apparently there is no move ctor defined for CRGB
CRGB squareTo(uint8_t const r, uint8_t const g, uint8_t const b)
{
	return CRGB(squaredVal[r], squaredVal[g], squaredVal[b]);
}


//----- Predetermined colors --------------------------------------------------
static CRGB const black = CrgbInit(0, 0, 0);
static CRGB const pink = CrgbInit(255, 20, 147);
static CRGB const forest = CrgbInit(57, 255, 20);
static CRGB const ocean = CrgbInit(0, 180, 255);
static CRGB const autumn = CrgbInit(255, 255, 0);


void setup() 
{
	Serial.begin(115200);
	Serial.println("It puts dem black");

	FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

	all1.forEach([](CRGB &led) { led = black; });
	all2.forEach([](CRGB &led) { led = black; });
	FastLED.show();

	int scale = 1;
	while (1) {
		CRGB const blue2 = CrgbInit(0, 0, 100, 20);
		CRGB const autumn2 = CrgbInit(255, 255, 0, 20);
		CRGB const pink1 = CrgbInit(255, 20, 147, scale * 10);
		fillColorTransformation_cw(top1, black, pink1, 0, 30);
		
		// auto it = top1.begin();
		// for (int i=0; i<10; ++i) {
		// 	*it = i >= scale / 10 ? black : (i+1) % 5 == 0 ? autumn2 : blue2;
		// 	++it;
		// }
		fillRange_ccw(top1, blue2, 0, scale);
		fillRange_ccw(top1, black, scale, 10 - scale);

		FastLED.show();

		if (++scale > 10)
			scale = 0;

		delay(300);
	}
}


void loop()
{
	CRGB const allColors[] = {pink, ocean, forest, autumn};
	int constexpr totalColors = sizeof(allColors) / sizeof(allColors[0]);
	unsigned long constexpr recolorSpan = 5000;
	int colorIdx = 1;
	int pos1 = 0;
	CRGB currentColor = allColors[0];
	CRGB nextColor = allColors[1];
	unsigned long nextRecolor = millis() + recolorSpan;
	int const totalRecolorSteps = 50;
	int recolorSteps = totalRecolorSteps;

	ColorDelta delta(currentColor, nextColor, totalRecolorSteps);
	AccurateColor color(currentColor);

	while (1)
	{
		pos1 = all1.normalizedPos(++pos1);
		fillColorTransformation_cw(all1, black, color.toCrgb(), pos1, 130);
		// fillColorTransformation_cw(all2, black, color.toCrgb(), pos1, 130);
		FastLED.show();
		delay(10);
		if (millis() > nextRecolor) {
			color.add(delta);

			if (--recolorSteps == 0) {
				if (++colorIdx >= totalColors)
					colorIdx = 0;
				
				currentColor = nextColor;
				nextColor = allColors[colorIdx];

				color = currentColor;
				recolorSteps = totalRecolorSteps;
				nextRecolor += recolorSpan;

				delta.init(currentColor, nextColor, totalRecolorSteps);
			}
		}
	}
}
