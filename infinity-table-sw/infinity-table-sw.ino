#include <FastLED.h>
#include "ledUtils.h"
#include "algorithms.h"
#include "time.h"
#include "debug.h"

#define LED_DATA_OUT 2
#define SWITCH1_IN 3
#define SWITCH2_IN 4
#define POTENTIOMETER_IN 7


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


// static SquaredVal const squaredVal;


/*----- Function --------------------------------------------------------------
 * Does:
 *   Read the status of switch 1.
 *
 * Gives:
 *   != 0 when a switch press was detected.
 *----------------------------------------------------------------------------*/
static inline int switch1Pressed(void)
{
	static uint8_t prevState = 1;
	uint8_t const state = digitalRead(SWITCH1_IN);
	int const ret = prevState && !state;

	prevState = state;
	return ret;
}


/*----- Function --------------------------------------------------------------
 * Does:
 *   Read the status of switch 1.
 *
 * Gives:
 *   != 0 when a switch press was detected.
 *----------------------------------------------------------------------------*/
static inline int switch2Pressed(void)
{
	static uint8_t prevState = 1;
	uint8_t const state = digitalRead(SWITCH2_IN);
	int const ret = prevState && !state;

	prevState = state;
	return ret;
}


/*----- Function --------------------------------------------------------------
 * Does:
 *   Read the position of the dial (potentiometer).
 *
 * Gives:
 *   A value from 0 to 255.
 *----------------------------------------------------------------------------*/
static inline int readDialPosition(void)
{
	return analogRead(POTENTIOMETER_IN) >> 2;
}



// CRGB squareTo(uint8_t const r, uint8_t const g, uint8_t const b)
// {
// 	// Warning: apparently there is no move ctor defined for CRGB
// 	return CRGB(squaredVal[r], squaredVal[g], squaredVal[b]);
// }


//----- Predetermined colors --------------------------------------------------
static CRGB const black = CRGB(0x00, 0x00, 0x00);
static CRGB const red = CRGB(0xFF, 0x00, 0x00);
static CRGB const orange = CRGB(0xFF, 0x2E, 0x00);
static CRGB const green = CRGB(0x00, 0x80, 0x00);
static CRGB const blue = CRGB(0x00, 0x00, 0xFF);
static CRGB const pink = CRGB(0xFF, 0x14, 0x93);
static CRGB const forest = CRGB(0x39, 0xFF, 0x14);
// static CRGB const indigo = CRGB(0x4B, 0x00, 0x82);
static CRGB const indigo = CRGB(0x2A, 0x0D, 0x5D);
static CRGB const ocean = CRGB(0x00, 0xB4, 0xFF);
static CRGB const yellow = CRGB(0xFF, 0xD7, 0x00);
static CRGB const violet = CRGB(0xEE, 0x82, 0xEE);


void setup() 
{
	Serial.begin(115200);

	pinMode(SWITCH1_IN, INPUT_PULLUP);
	pinMode(SWITCH2_IN, INPUT_PULLUP);

	FastLED.addLeds<WS2812, LED_DATA_OUT, GRB>(leds, NUM_LEDS);

	Serial.println("It puts dem black");
	all1.forEach([](CRGB &led) { led = black; });
	all2.forEach([](CRGB &led) { led = black; });
	FastLED.show();
}


static void ledTrain(void)
{
	CRGB const allColors[] = {
		red,
		pink,
		forest,
		ocean,
		yellow
	};

	int constexpr totalColors = sizeof(allColors) / sizeof(allColors[0]);
	unsigned long constexpr drawInterval = 40;
	unsigned long constexpr recolorInterval = 5000;
	int constexpr totalRecolorSteps = 50;

	int colorIdx = 0;
	int drawStartPos1 = 0;
	CRGB currentColor = allColors[colorIdx];
	CRGB nextColor;
	unsigned long nextDraw = millis();
	unsigned long nextRecolor = millis() + recolorInterval;
	int recolorSteps;
	ColorDelta delta;
	AccurateColor drawColor = allColors[colorIdx];
	int automaticSwitchingEnabled = 1;
	int colorSwitchingInProgress = 0;

	while (!switch1Pressed()) {
		unsigned long const now = millis();

		if (!automaticSwitchingEnabled) {
			nextRecolor = now + 1;
		}

		// if (switch1Pressed()) {
		// 	nextRecolor = !automaticSwitchingEnabled ? now : now + recolorInterval;
		// 	automaticSwitchingEnabled = 0;
		// }
		// if (switch2Pressed()) {
		// 	automaticSwitchingEnabled = 1;
		// 	nextRecolor = now;
		// }

		if (!timeIsAfterEq(now, nextDraw))
			continue;

		nextDraw += drawInterval;

		AccurateColor dimmedColor(drawColor);
		int const fractions = readDialPosition();
		dimmedColor.scale(fractions);

		drawStartPos1 = all1.normalizedPos(++drawStartPos1);
		fillColorTransformation_cw(all1, black, dimmedColor.toCrgb(), drawStartPos1, 130);
		// fillColorTransformation_cw(all2, black, dimmedColor.toCrgb(), pos1, 127);
		FastLED.show();
		
		if (!colorSwitchingInProgress && timeIsAfterEq(now, nextRecolor)) {
			nextRecolor += recolorInterval;
			colorSwitchingInProgress = 1;

			recolorSteps = totalRecolorSteps;
			currentColor = drawColor.toCrgb();

			if (++colorIdx >= totalColors)
				colorIdx = 0;
				
			nextColor = allColors[colorIdx];
			delta.init(currentColor, nextColor, totalRecolorSteps);
		}

		if (colorSwitchingInProgress) {
			drawColor.add(delta);

			if (--recolorSteps == 0)
				colorSwitchingInProgress = 0;
		}
	}
}


static void ledBreathing(void)
{
	CRGB const allColors[] = {
		red,
		pink,
		forest,
		ocean,
		yellow
	};

	int constexpr totalColors = sizeof(allColors) / sizeof(allColors[0]);
	unsigned long constexpr drawInterval = 25;
	int constexpr totalRecolorSteps = 100;

	CRGB selectedColors[2] = {operator / (allColors[0], 10), allColors[0]};
	int selectedColorIdx = 0;
	unsigned long nextDraw = millis();
	int drawIdx = 0;
	int recolorSteps = 0;
	AccurateColor drawColor;
	ColorDelta delta;


	while (!switch1Pressed()) {
		unsigned long const now = millis();

		if (switch2Pressed()) {
			if (++selectedColorIdx >= totalColors)
				selectedColorIdx = 0;

			selectedColors[0] = operator / (allColors[selectedColorIdx], 10);
			selectedColors[1] = allColors[selectedColorIdx];
			recolorSteps = 0;
			drawIdx = 0;
		}

		if (!timeIsAfterEq(now, nextDraw))
			continue;

		nextDraw += drawInterval;

		if (!recolorSteps) {
			drawColor = selectedColors[drawIdx];
			delta.init(selectedColors[drawIdx], selectedColors[(drawIdx+1) & 0x1], totalRecolorSteps);
			drawIdx = (drawIdx + 1) & 0x1;
			recolorSteps = totalRecolorSteps;
		}

		int const fractions = readDialPosition();
		AccurateColor dimmedColor(drawColor);
		CRGB crgb = dimmedColor.scale(fractions).toCrgb();

		all1.forEach([crgb](CRGB &led) { led = crgb; });
		all2.forEach([crgb](CRGB &led) { led = crgb; });
		FastLED.show();

		drawColor.add(delta);
		--recolorSteps;
	}
}


static void ledRainbow(void)
{
	CRGB const allColors[] = {
		red,
		orange,
		yellow,
		green,
		blue,
		indigo,
		// violet
	};

	int constexpr totalColors = sizeof(allColors) / sizeof(allColors[0]);
	unsigned long constexpr drawInterval = 60;

	unsigned long nextDraw = millis();
	int constexpr animateMax = 255;
	int constexpr animateMin = 100;
	int animationScaling[2] = {255, 255};
	int animateStep[2] = {11, 13};
	int animateIdx[2];

	while (!switch1Pressed()) {
		unsigned long const now = millis();

		if (!timeIsAfterEq(now, nextDraw))
			continue;

		nextDraw += drawInterval;

		for (int i = 0; i < 2; ++i) {
			animationScaling[i] += animateStep[i];
			if (animationScaling[i] < animateMin) {
				animationScaling[i] = animateMin;
				animateStep[i] *= -1;
			}
			else if (animationScaling[i] > animateMax) {
				animationScaling[i] = animateMax;
				animateStep[i] *= -1;
				animateIdx[i] = random(-1, totalColors - 1);
			}
		}

		for (int ledArrayIdx = 0; ledArrayIdx < 2; ++ledArrayIdx) {
			LedArray &topArray = !ledArrayIdx ? top1 : top2;
			LedArray &btmArray = !ledArrayIdx ? btm1 : btm2;
			float const ledsPerColor = (float) topArray.length() / (totalColors - 1);
			float fIdx = 0;

			for (int colorIdx = 0; colorIdx < totalColors - 1; ++colorIdx) {
				int const beginIdx = (int)fIdx;
				fIdx += ledsPerColor;
				int const endIdx = (int)(fIdx + 0.5f);

				AccurateColor beginColor = allColors[colorIdx];
				AccurateColor endColor = allColors[colorIdx+1];
				
				if (colorIdx == animateIdx[ledArrayIdx]) {
					endColor.scale(animationScaling[ledArrayIdx]);
				}
				else if (colorIdx == animateIdx[ledArrayIdx] + 1) {
					beginColor.scale(animationScaling[ledArrayIdx]);
				}


				fillColorTransformation_cw(topArray, beginColor.toCrgb(), endColor.toCrgb(), beginIdx, endIdx - beginIdx);
				fillColorTransformation_ccw(btmArray, beginColor.toCrgb(), endColor.toCrgb(), beginIdx, endIdx - beginIdx);
			}
		}

		FastLED.show();
	}
}


void loop()
{
	static int mode = 2;

	switch (mode) {
		default:
			mode = 0;
			// Fall through
		case 0:
			ledBreathing();
			break;
		case 1:
			ledTrain();
			break;
		case 2:
			ledRainbow();
			break;
	}

	++mode;
	all1.forEach([](CRGB &led) { led = black; });
	all2.forEach([](CRGB &led) { led = black; });
}
