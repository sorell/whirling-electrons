#include "LedUtils.h"

#define DATA_PIN 9
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


/*----- Helper function -------------------------------------------------------
 * Does:
 *   Library CRGB class initialization helper to set TwoBytes upper bytes to
 *   the actual color.
 *----------------------------------------------------------------------------*/
static inline CRGB CrgbInit(LedUtils::TwoBytes const &red, LedUtils::TwoBytes const &green, LedUtils::TwoBytes const &blue)
{
	return {.red = red.h,
		.green = green.h,
		.blue = blue.h};
}


/*----- Class -----------------------------------------------------------------
 * Accurate delta values for R,G,B calculated from difference of two colors and
 * divided for equal steps.
 * The delta accuracy is 1/128 of a pixel color accuracy.
 *----------------------------------------------------------------------------*/
class ColorDelta
{
public:
	ColorDelta(CRGB const from, CRGB const to, int const steps)
	{
		init(from, to, steps);
	}
	
	/*----- Function --------------------------------------------------------------
	 * Does:
	 *   Calculates accurate R,G,B delta values.
	 *   The accuracy can't be calculated with all 8 bits' value, because then the
	 *   number sign information would be lost on <<8 op.
	 *
	 * Wants:
	 *   beginColor: The starting color.
	 *   endColor: The end color.
	 *   steps: The number of increments of delta required to reach endColor from
	 *     beginColor.
	 *----------------------------------------------------------------------------*/
	void init(CRGB const beginColor, CRGB const endColor, int const steps)
	{
		r_ = ((((int16_t)endColor.red - (int16_t)beginColor.red) << 7) / steps) << 1;
		g_ = ((((int16_t)endColor.green - (int16_t)beginColor.green) << 7) / steps) << 1;
		b_ = ((((int16_t)endColor.blue - (int16_t)beginColor.blue) << 7) / steps) << 1;
	}

	int16_t r() const { return r_; }
	int16_t g() const { return g_; }
	int16_t b() const { return b_; }

private:
	int16_t r_;
	int16_t g_;
	int16_t b_;
};


/*----- Class -----------------------------------------------------------------
 * R,G,B values of a color containing also fractions part. The upper byte is
 * used as CRGB value and lower byte is fractions used for accurate increments.
 *----------------------------------------------------------------------------*/
class AccurateColor
{
public:
	AccurateColor(CRGB const &from) : 
		r_(LedUtils::TwoBytes::fromColor(from.red)),
		g_(LedUtils::TwoBytes::fromColor(from.green)),
		b_(LedUtils::TwoBytes::fromColor(from.blue))
		{}

	CRGB toCrgb() const { return CrgbInit(r_, g_, b_); }

	/*----- Function --------------------------------------------------------------
	 * Does:
	 *   Add delta to the fraction part of R,G,B values.
	 *----------------------------------------------------------------------------*/
	void add(ColorDelta const &delta)
	{
		r_.val += delta.r();
		g_.val += delta.g();
		b_.val += delta.b();
	}

private:
	LedUtils::TwoBytes r_;
	LedUtils::TwoBytes g_;
	LedUtils::TwoBytes b_;
};




// Warning: apparently there is no move ctor defined for CRGB
CRGB squareTo(uint8_t const r, uint8_t const g, uint8_t const b)
{
	return CRGB(squaredVal[r], squaredVal[g], squaredVal[b]);
}


/*----- Debugging functions ---------------------------------------------------
 * Does:
 *   Print various data types to Arduino Serial.
 *----------------------------------------------------------------------------*/
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
	Serial.print(delta.r());
	Serial.print(",");
	Serial.print(delta.g());
	Serial.print(",");
	Serial.println(delta.b());
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


/*----- Function --------------------------------------------------------------
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
template <typename F>
static void fillColorTransformation(LedUtils::LedArray &array, F const atFunc, CRGB const &beginColor, CRGB const &endColor, int const pos = 0, int amount = -1)
{
	if (amount < 0)
		amount = array.length();

	AccurateColor color(beginColor);
	ColorDelta delta(beginColor, endColor, amount);

	for (auto it = atFunc(pos); amount > 0; --amount) {
		*it = color.toCrgb();
		it = array.next(it);
		color.add(delta);
	}
}

/*----- Function --------------------------------------------------------------
 * Does:
 *   This calls fillColorTransformation() with LedArray::at(), giving an
 *   iterator proceeding counter-clockwise.
 *
 * Wants:
 *   See fillColorTransformation().
 *----------------------------------------------------------------------------*/
static inline void fillColorTransformation_ccw(LedUtils::LedArray &array, CRGB const &beginColor, CRGB const &endColor, int const pos = 0, int const amount = -1)
{
	fillColorTransformation(array, [&](int p){ return array.at(p);}, beginColor, endColor, pos, amount);
}

/*----- Function --------------------------------------------------------------
 * Does:
 *   This calls fillColorTransformation() with LedArray::at(), giving an
 *   iterator proceeding clockwise.
 *
 * Wants:
 *   See fillColorTransformation().
 *----------------------------------------------------------------------------*/
static inline void fillColorTransformation_cw(LedUtils::LedArray &array, CRGB const &beginColor, CRGB const &endColor, int const pos = 0, int const amount = -1)
{
	fillColorTransformation(array, [&](int p){ return array.r_at(p);}, beginColor, endColor, pos, amount);
}


//----- Predetermined colors --------------------------------------------------
static CRGB const black = {.red = 0, .green = 0, .blue = 0};
static CRGB const pink = CrgbInit(255, 20, 147);
static CRGB const forest = CrgbInit(57, 255, 20);
static CRGB const ocean = CrgbInit(0, 180, 255);
static CRGB const autumn = CrgbInit(255, 255, 0);


void setup() 
{
	Serial.begin(115200);
	Serial.println("It puts dem black");

	FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

	all1.forEach([&](CRGB &led) { led = black; });
	all2.forEach([&](CRGB &led) { led = black; });
	FastLED.show();
}


void loop()
{
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
