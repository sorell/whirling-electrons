#include <FastLED.h>
#include "LedUtils.h"

#define NUM_LEDS 260
#define DATA_PIN 9
#define MAX_BRIGHT 255

// Facts
// =====
// - There are 260 leds in the table, in two rows.
// - It takes:
//   - 9,4 ms to draw all the 260 leds once.
//   - 5,6 ms to fill leds array with floating point multiplied values
//   - 0,4 ms to fill leds array with integer multiplied and shifted values


// Dimensions
// ==========
//  * * * * * * * * * .. * * * * * * * * *  <-- top1 (42)
//   * * * * * * * * *..* * * * * * * * *   <-- top2 (41)
//  *                                    *
//   *                                  *
//  *                                    *
//   *                                  *
//  *                                    *
//   *                                  *
//  .. <-- left1 (24)  right2 (23) -->  ..
//  ..  <-- left2 (23)                  .. <-- right1 (24)
//   *                                  *
//  *                                    *
//   *                                  *
//  *                                    *
//   *                                  *
//  *                                    *
//   * * * * * * * * *..* * * * * * * * *   <-- btm2 (41)
//  * * * * * * * * * .. * * * * * * * * *  <-- btm1 (42)
//  ^
//  \- wire

static CRGB leds[NUM_LEDS];

static LedUtils::LedArray all1(leds, 132);
static LedUtils::LedArray all2(leds + 132, 128);

static LedUtils::LedArray btm1(leds, 42);
static LedUtils::LedArray right1(leds + 42, 24);
static LedUtils::LedArray top1(leds + 66, 42);
static LedUtils::LedArray left1(leds + 108, 24);
static LedUtils::LedArray btm2(leds + 132, 41);
static LedUtils::LedArray right2(leds + 173, 23);
static LedUtils::LedArray top2(leds + 196, 41);
static LedUtils::LedArray left2(leds + 237, 23);


static LedUtils::SquaredVal const squaredVal;


//
// Library class CRGB initialization helper
//
static CRGB CrgbInit(uint8_t const r, uint8_t const g, uint8_t const b)
{
	return {.red = (uint8_t) ((float) r / 255.0f * (float) MAX_BRIGHT), 
		.green = (uint8_t) ((float) g / 255.0f * (float) MAX_BRIGHT), 
		.blue = (uint8_t) ((float) b / 255.0f * (float) MAX_BRIGHT)};
}

__attribute__((__unused__)) static CRGB CrgbInit(CRGB sample, float percent)
{
	return {.red = (uint8_t) ((float) sample.red * percent), 
		.green = (uint8_t) ((float) sample.green * percent), 
		.blue = (uint8_t) ((float) sample.blue * percent)};
}

static inline CRGB CrgbInit(LedUtils::TwoBytes const &red, LedUtils::TwoBytes const &green, LedUtils::TwoBytes const &blue)
{
	return {.red = red.h,
		.green = green.h,
		.blue = blue.h};
}

struct ColorDelta
{
	int16_t r;
	int16_t g;
	int16_t b;
};

class AccurateColor
{
public:
	AccurateColor(CRGB const &from) : 
		r(LedUtils::TwoBytes::fromColor(from.red)),
		g(LedUtils::TwoBytes::fromColor(from.green)),
		b(LedUtils::TwoBytes::fromColor(from.blue))
		{}

	CRGB toCrgb() const { return CrgbInit(r, g, b); }

	void add(ColorDelta const &delta)
	{
		r.val += delta.r;
		g.val += delta.g;
		b.val += delta.b;
	}

private:
	LedUtils::TwoBytes r;
	LedUtils::TwoBytes g;
	LedUtils::TwoBytes b;
};




// Warning: apparently there is no move ctor defined for CRGB
CRGB squareTo(uint8_t const r, uint8_t const g, uint8_t const b)
{
	return CRGB(squaredVal[r], squaredVal[g], squaredVal[b]);
}

__attribute__((__unused__)) static void print(CRGB const &rgb, char const prefix[] = "")
{
	Serial.print(prefix);
	Serial.print(rgb.r);
	Serial.print(",");
	Serial.print(rgb.g);
	Serial.print(",");
	Serial.println(rgb.b);
}

__attribute__((__unused__)) static void print(LedUtils::TwoBytes const &tb, char const prefix[] = "")
{
	Serial.print(prefix);
	Serial.print(tb.l);
	Serial.print(",");
	Serial.println(tb.h);
}

__attribute__((__unused__)) static void print(ColorDelta const &delta, char const prefix[] = "")
{
	Serial.print(prefix);
	Serial.print(delta.r);
	Serial.print(",");
	Serial.print(delta.g);
	Serial.print(",");
	Serial.println(delta.b);
}

__attribute__((__unused__)) static void print(int n0, int n1, int n2, char const prefix[] = "")
{
	Serial.print(prefix);
	Serial.print(n0);
	Serial.print(",");
	Serial.print(n1);
	Serial.print(",");
	Serial.println(n2);
}




static struct ColorDelta calculateColorTransformation(CRGB const from, CRGB const to, int const steps)
{
	ColorDelta delta;
	delta.r = ((((int16_t)to.red - (int16_t)from.red) << 7) / steps) << 1;
	delta.g = ((((int16_t)to.green - (int16_t)from.green) << 7) / steps) << 1;
	delta.b = ((((int16_t)to.blue - (int16_t)from.blue) << 7) / steps) << 1;
	return delta;
}


template <typename F>
static void fillColorTransformation(LedUtils::LedArray &array, F const atFunc, CRGB const &beginColor, CRGB const &endColor, int const pos = 0, int amount = -1)
{
	if (amount < 0)
		amount = array.length();

	AccurateColor color(beginColor);
	ColorDelta delta = calculateColorTransformation(beginColor, endColor, amount);

	for (auto it = atFunc(pos); amount > 0; --amount) {
		*it = color.toCrgb();
		it = array.next(it);
		color.add(delta);
	}
}

static inline void fillColorTransformation_ccw(LedUtils::LedArray &array, CRGB const &beginColor, CRGB const &endColor, int const pos = 0, int const amount = -1)
{
	fillColorTransformation(array, [&](int p){ return array.at(p);}, beginColor, endColor, pos, amount);
}

static inline void fillColorTransformation_cw(LedUtils::LedArray &array, CRGB const &beginColor, CRGB const &endColor, int const pos = 0, int const amount = -1)
{
	fillColorTransformation(array, [&](int p){ return array.r_at(p);}, beginColor, endColor, pos, amount);
}



static CRGB const black = {.red = 0, .green = 0, .blue = 0};
static CRGB const pink = CrgbInit(255, 20, 147);
static CRGB const forest = CrgbInit(57, 255, 20);
static CRGB const ocean = CrgbInit(0, 180, 255);
static CRGB const autumn = CrgbInit(255, 255, 0);


void setup() 
{
	Serial.begin(115200);

	FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

	Serial.println("It puts dem black");
	all1.forEach([&](CRGB &led) { led = black; });
	all2.forEach([&](CRGB &led) { led = black; });
	FastLED.show();

	CRGB const allColors[] = {pink, ocean, forest, autumn};
	int constexpr totalColors = sizeof(allColors) / sizeof(allColors[0]);
	unsigned long constexpr recolorSpan = 5000000;
	int colorIdx = 1;
	int pos1 = 0;
	CRGB currentColor = allColors[0];
	CRGB nextColor = allColors[1];
	unsigned long nextRecolor = millis() + recolorSpan;
	int const totalRecolorSteps = 50;
	int recolorSteps = totalRecolorSteps;

	ColorDelta delta = calculateColorTransformation(currentColor, nextColor, totalRecolorSteps);
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

				delta = calculateColorTransformation(currentColor, nextColor, totalRecolorSteps);
			}
		}
	}
}


void loop()
{
}
