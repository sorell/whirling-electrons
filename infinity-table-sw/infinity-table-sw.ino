#include <FastLED.h>
#include "LedUtils.h"

#define NUM_LEDS 260
#define DATA_PIN 9
#define MAX_BRIGHT 30

// Facts
// =====
// - There are 260 leds in the table, in two rows.
// - It takes 94 ms to draw all the 260 leds once.


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
static LedUtils::SquaredVal const squaredVal;

// Warning: apparently there is no move ctor defined for CRGB
CRGB squareTo(uint8_t const r, uint8_t const g, uint8_t const b)
{
	return CRGB(squaredVal[r], squaredVal[g], squaredVal[b]);
}


//
// Library class CRGB initialization helper
//
static CRGB CrbgInit(uint8_t const r, uint8_t const g, uint8_t const b)
{
	return {.red = (uint8_t) ((float) r / 255.0f * (float) MAX_BRIGHT), 
		.green = (uint8_t) ((float) g / 255.0f * (float) MAX_BRIGHT), 
		.blue = (uint8_t) ((float) b / 255.0f * (float) MAX_BRIGHT)};
}


class ColorRange {
public:
	ColorRange(CRGB const &high, CRGB const &low) : 
		low_(low),
		redInc_((float) (high.red - low.red) / 100.0f), 
		greenInc_((float) (high.green - low.green) / 100.0f),
		blueInc_((float) (high.blue - low.blue) / 100.0f) {}

	CRGB percent(float const pc) const {
		return {(uint8_t) (low_.red + (uint8_t) (redInc_ * pc)), (uint8_t) (low_.green + (uint8_t) (greenInc_ * pc)), (uint8_t) (low_.blue + (uint8_t) (blueInc_ * pc))};
	}

private:
	CRGB const low_;
	float const redInc_;
	float const greenInc_;
	float const blueInc_;
};


#if 0
class Hilight {
public:
		Hilight() : diff_({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 90, 80, 70, 60, 50, 40, 30, 20, 10}), size_(sizeof(diff_)/sizeof(diff_[0])) {
			// diff_[0] = 15; diff_[1] = 30; diff_[2] = 45; diff_[3] = 60; diff_[4] = 45; diff_[5] = 30; diff_[6] = 15;
		}
public:
	int8_t const diff_[19];
	int const size_;
};
#endif

static CRGB const black = {.red = 0, .green = 0, .blue = 0};
static CRGB const pink = CrbgInit(255, 110, 199);
static ColorRange const pinkRange = {CrbgInit(255, 110, 199), CrbgInit(26, 11, 20)};
// static ColorRange const forest = {CrbgInit(57, 255, 20), CrbgInit(6, 26, 2)};
static ColorRange const forest = {CrbgInit(0x49, 0xE2, 0x0E), CrbgInit(0x55, 0x10, 0x33)};
static ColorRange const ocean = {CrbgInit(0, 180, 255), CrbgInit(0, 18, 26)};
static ColorRange const autumn = {CrbgInit(255, 0, 0), CrbgInit(255, 255, 0)};

static int8_t const colorInc = 2;



class LedState {
public:
	LedState() : percent_(0), direction_(0) {}
	LedState(int8_t const percent, int8_t const direction) : percent_(percent), direction_(direction) {}

	void copy(CRGB &rgb, ColorRange const &range) const {
		rgb = range.percent(percent_);
	}
	void advance(void) {
		int8_t const res = percent_ + colorInc * direction_;
		if (res < 0) {
			direction_ = 1;
		}
		else if (res > 100) {
			direction_ = -1;
		}
		else {
			percent_ = res;
			return;
		}
		advance();
	}

private:
	int8_t percent_;
	int8_t direction_;
};

// static LedState ledState[NUM_LEDS];
static unsigned long constexpr changeWindow = 5000;
static unsigned long nextChange;
// static Hilight hilight;


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

static LedUtils::LedArray *upperRowPtrs[] = {&btm1, &right1, &top1, &left1};
static LedUtils::LoopingMultiLedArray upperRow(upperRowPtrs, sizeof(upperRowPtrs)/sizeof(upperRowPtrs[0]));




union SplitShort {
	typedef struct {
		unsigned char lb;
		unsigned char hb;
	} TwoBytes;
	short s;
	unsigned short us;
	TwoBytes b;
};


class LedSlide {
public:
	LedSlide() {}
	LedSlide(CRGB const &start, CRGB const &end, int steps) { init(start, end, steps); }
	LedSlide(LedSlide const &rhs) : r(rhs.r), g(rhs.g), b(rhs.b), d_r(rhs.d_r), d_g(rhs.d_g), d_b(rhs.d_b)
		{}
	void init(CRGB const &start, CRGB const &end, int steps) {
		r.us = start.r<<8; g.us = start.g<<8; b.us = start.b<<8; 
		d_r = (float)(( ((long)end.r - (long)start.r) << 8) ) / (float)steps;
		d_g = (float)(( ((long)end.g - (long)start.g) << 8) ) / (float)steps;
		d_b = (float)(( ((long)end.b - (long)start.b) << 8) ) / (float)steps;
	}
	LedSlide &operator ++ () { r.us+=d_r; g.us+=d_g; b.us+=d_b; return *this; }
	// LedSlide operator ++ (int) { LedSlide tmp(*this); r+=d_r; g+=d_g; b+=d_b; return tmp; }
	void toCrgbRaw(CRGB &col) const { col.r = r.b.hb; col.g = g.b.hb; col.b = b.b.hb; }
	CRGB toCrgbRaw() const { CRGB col(r.b.hb, g.b.hb, b.b.hb); return col; }
	void toCrgbSq(CRGB &col) const { col.r = squaredVal[r.b.hb]; col.g = squaredVal[g.b.hb]; col.b = squaredVal[b.b.hb]; }
	CRGB toCrgbSq() const { CRGB col(squaredVal[r.b.hb], squaredVal[g.b.hb], squaredVal[b.b.hb]); return col; }
// private:
	SplitShort r, g, b;
	short d_r, d_g, d_b;
};


unsigned long constexpr SemiMagenta = 0x100010;

void setup() 
{
	Serial.begin(115200);

	FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

	// for (int i=0; i<NUM_LEDS; ++i) {
	// 	ledState[i] = {0, 1};
	// }
	// for (int i=0; i<min(NUM_LEDS, 8); ++i) {
	// 	ledState[i] = {(int8_t) (i * 10), 1};
	// }

	nextChange = millis() + changeWindow;

	Serial.println("It puts dem black");
	for (int i=0; i<NUM_LEDS; ++i) {
		leds[i] = CRGB::Black;
	}
	// for (auto iter = btm1.begin(); iter != btm1.end(); ++iter) {
	// 	**iter = CRGB::Blue;
	// }
	// for (auto iter = top1.begin(); iter != top1.end(); ++iter) {
	// 	**iter = CRGB::Red;
	// }
	FastLED.show();
// delay(100000);
	// for (int i=0; i<255; ++i) {
	// 	Serial.print(squaredVal[i]);
	// }

	int idx = 0;
	while (1)
	{
		for (auto it = top1.begin(); it != top1.end(); ++it)
		{
			*it = pink;
			FastLED.show();
			*it = black;
		}
	}

	delay(1000);
}

#if 0
void fadeAllEven(CRGB const &startingColor, CRGB const &endingColor, uint8_t steps)
{
	CRGB col = startingColor;
	float const deltaRF = (float) (endingColor.r - startingColor.r) / steps;
	float const deltaGF = (float) (endingColor.g - startingColor.g) / steps;
	float const deltaBF = (float) (endingColor.b - startingColor.b) / steps;
	float step = 0.0f;

	while (steps--) {
		step += 1.0f;

		for (auto iter = top1.begin(); iter != top1.end(); ++iter) {
			**iter = col;
		}
		FastLED.show();
		col.r = (float) startingColor.r + deltaRF * step;
		col.g = (float) startingColor.g + deltaGF * step;
		col.b = (float) startingColor.b + deltaBF * step;

		for (auto iter = top2.begin(); iter != top2.end(); ++iter) {
			**iter = col;
		}
		FastLED.show();
		col.r = (float) startingColor.r + deltaRF * step;
		col.g = (float) startingColor.g + deltaGF * step;
		col.b = (float) startingColor.b + deltaBF * step;
	}
}
#endif


void slideAll(CRGB const &start, CRGB const &end, int steps)
{
	LedSlide slide(start, end, steps);

	while (--steps) {
		for (auto it = all1.begin(); it != all2.end(); ++it) {
			slide.toCrgbSq(*it);
		}
		++slide;
		FastLED.show();
	}
}

void risingColor(CRGB const &headColor, CRGB const &tailColor, int steps)
{
	LedSlide nose[42];
	LedSlide endColor(tailColor, headColor, sizeof(nose)/sizeof(nose[0]));
	
	auto it = top1.begin();
	for (unsigned int i=0; i<sizeof(nose)/sizeof(nose[0]); ++i) {
		nose[i].init(*it, endColor.toCrgbRaw(), steps);
		++endColor;
		++it;
	}

	while (--steps) {
		auto it = top1.begin();
		for (unsigned int i=0; i<sizeof(nose)/sizeof(nose[0]); ++i) {
			nose[i].toCrgbSq(*it);
			++(nose[i]);
			++it;
		}
		FastLED.show();

	}
}

void raiseNose(CRGB const &start, CRGB const &end, int steps)
{
	LedSlide nose[42];
	LedSlide endColor(start, end, sizeof(nose)/sizeof(nose[0]));
	
	auto it = top1.begin();
	for (unsigned int i=0; i<sizeof(nose)/sizeof(nose[0]); ++i, ++it) {
		nose[i].init(*it, endColor.toCrgbRaw(), steps);
		++endColor;
	}

	while (--steps) {
		auto it = top1.begin();
		for (unsigned int i=0; i<sizeof(nose)/sizeof(nose[0]); ++i) {
			nose[i].toCrgbRaw(*it);
			++(nose[i]);
			++it;
		}
		FastLED.show();
	}
}

void toFlat(CRGB const &end, int steps)
{
	LedSlide nose[42];
	
	auto it = top1.begin();
	for (unsigned int i=0; i<sizeof(nose)/sizeof(nose[0]); ++i, ++it) {
		nose[i].init(*it, end, steps);
	}

	while (--steps) {
		auto it = top1.begin();
		for (unsigned int i=0; i<sizeof(nose)/sizeof(nose[0]); ++i) {
			nose[i].toCrgbRaw(*it);
			++(nose[i]);
			++it;
		}
		FastLED.show();
	}
}

void raiseNose2(CRGB const &start, CRGB const &end, int steps)
{
	LedSlide nose[42];
	LedSlide endColor(start, end, sizeof(nose)/sizeof(nose[0]));
	
	auto it = top1.begin();
	for (unsigned int i=0; i<sizeof(nose)/sizeof(nose[0]); ++i, ++it) {
		nose[i].init(*it, endColor.toCrgbRaw(), steps);
		++endColor;
	}

	while (--steps) {
		auto it = top1.begin();
		// for (unsigned int i=0; i<22; ++i) ++it;
		for (unsigned int i=0; i<sizeof(nose)/sizeof(nose[0]); ++i) {
			nose[i].toCrgbSq(*it);
			++(nose[i]);
			++it;
		}
		FastLED.show();

		Serial.print(nose[19].d_r);
		Serial.print(", ");
		Serial.print(nose[19].d_g);
		Serial.print(", ");
		Serial.println(nose[19].d_b);
	}
}


// template <typename IT>
// class GlowWorm {
// public:
// 	GlowWorm(uint8_t size, CRGB const &startCol, CRGB const &endCol, IT const &startPos, IT const &endPos) : 
// 		size_(size), startCol_(startCol), endCol_(endCol), startPos_(startPos), endPos_(endPos), currPos_(startPos)
// 	{}
// 	void placement() {
// 		IT it = currPos_;
// 		slide_.init(startCol_, endCol_, size_);
// 		for (uint8_t i=0; i<size_; ++i) {
// 			slide_.toCrgbRaw(*it);
// 			++slide_;
// 			if (++it == endPos_) {
// 				break;
// 			}
// 		}
// 	}
// 	bool advance() {
// 		bool const ret = ++currPos_ != endPos_;
// 		if (!ret) {
// 			currPos_ = startPos_;
// 		}
// 		return ret;
// 	}
// private:
// 	uint8_t const size_;
// 	LedSlide slide_;
// 	CRGB const startCol_;
// 	CRGB const endCol_;
// 	IT const startPos_;
// 	IT const endPos_;
// 	IT currPos_;
// };



void loop()
{
	// slideAll(&pink, &black, 20);
	// while (1) {
	// 	GlowWorm<LedUtils::ForwardIterator<CRGB>> glowWorms[4] = {{12, SemiMagenta, CRGB::Magenta, all1.begin(), all1.end()},
	// 		{12, SemiMagenta, CRGB::Magenta, all1.begin(), all1.end()},
	// 		{12, SemiMagenta, CRGB::Magenta, all1.begin(), all1.end()},
	// 		{12, SemiMagenta, CRGB::Magenta, all1.begin(), all1.end()}};
	// 	for (uint8_t i=0; i<33; ++i) glowWorms[1].advance();
	// 	for (uint8_t i=0; i<66; ++i) glowWorms[2].advance();
	// 	for (uint8_t i=0; i<99; ++i) glowWorms[3].advance();
	// 	do {
	// 		for (uint8_t i=0; i<sizeof(glowWorms)/sizeof(glowWorms[0]); ++i) {
	// 			glowWorms[i].placement();
	// 			glowWorms[i].advance();
	// 		}
	// 		FastLED.show();
	// 		delay(5);
	// 	} while (1);
	// }
	// {
	// 	GlowWorm<LedUtils::ForwardIterator<CRGB>> glowWorm(12, SemiMagenta, CRGB::Magenta, all1.begin(), all1.end());

	// 	do {
	// 		glowWorm.placement();
	// 		FastLED.show();
	// 	} while (glowWorm.advance());
	// }
	// {
	// 	GlowWorm<LedUtils::ReverseIterator<CRGB>> glowWorm(12, SemiMagenta, CRGB::Magenta, all1.r_begin(), all1.r_end());

	// 	do {
	// 		glowWorm.placement();
	// 		FastLED.show();
	// 	} while (glowWorm.advance());
	// }
#if 0
	while (startPoint != all1.end()) {
		auto it = startPoint;
		glowWorm.init(SemiMagenta, CRGB::Magenta, 12);
		for (unsigned int i=0; i<12; ++i) {
			glowWorm.toCrgbRaw(*it);
			++glowWorm;
			if (++it == all1.end()) {
				break;
			}
		}
		FastLED.show();
		++startPoint;
	}
#endif
	return;

	while (1) {
		risingColor(CRGB::Magenta, SemiMagenta, 30);
		// delay(1000);
		toFlat(SemiMagenta, 30);
		risingColor(SemiMagenta, CRGB::Magenta, 30);
		// delay(1000);
		toFlat(SemiMagenta, 30);
	}

#if 0
// pyramid
	uint8_t b = 40;
	int8_t delta = 10;
	// for (auto iter = top1.begin(); iter != top1.end(); ++iter) {
	// 	iter->b = squaredVal[squaredVal[b]];
	// 	iter->r = squaredVal[squaredVal[b]];
	// 	if (b + delta > 250) {
	// 		delta = -delta;
	// 	}
	// 	b += delta;
	// }

	// b = 210;
	// delta = -10;
	// auto iter2 = btm1.begin();
	// for (auto iter = top1.begin(); iter != top1.end(); ++iter, ++iter2) {
	// 	iter->b = squaredVal[b];
	// 	iter->r = squaredVal[b];
	// 	(*iter2)->b = squaredVal[b];
	// 	(*iter2)->r = squaredVal[b];
	// 	if (b + delta < 10) {
	// 		delta = -delta;
	// 	}
	// 	b += delta;
	// }
	FastLED.show();
	while (1);
#endif

#if 1
// wave patterns!
	uint8_t b0 = 100;
	uint8_t b1 = 140;
	int8_t delta0 = 1;
	int8_t delta1 = 1;
	while (1) {
		all1.forEach( [=](CRGB &led) { led.b = squaredVal[b0]; led.r = squaredVal[b0]; } );
		all2.forEach( [=](CRGB &led) { led.b = squaredVal[b1]; led.r = squaredVal[b1]; } );
		FastLED.show();
		if (b0 + delta0 > 150  ||  b0 + delta0 < 80) {
			delta0 = -delta0;
		}
		if (b1 + delta1 > 150  ||  b1 + delta1 < 80) {
			delta1 = -delta1;
		}
		b0 += delta0;
		b1 += delta1;
		// delay(1);
	}
#endif

#if 0
	while (1) {
		fadeAllEven(CRGB::Black, CRGB::Blue, 100);
	}
	CRGB actual = {0, 0, 0};
	uint8_t delta = 2;
	while (1) {
		// CRGB const colors[] = {CRGB::Blue, CRGB::Red, CRGB::Black};
		// i = (i+1)%(sizeof(colors)/sizeof(colors[0]));
		actual.b += delta;

		for (auto iter = top1.begin(); iter != top1.end(); ++iter) {
			**iter = actual;
		}
		FastLED.show();

		actual.b += delta;
		for (auto iter = top2.begin(); iter != top2.end(); ++iter) {
			**iter = actual;
		}
		FastLED.show();
	}
#endif

#if 0
// full blue and twice blinking full white
	for (auto iter = all2.begin(); iter != all2.end(); ++iter) {
		*iter = CRGB::Blue;
	}

	FastLED.show();

	while (1) {
		for (int times = 2; times; --times) {
			uint8_t intensity = 255;
			for (int i=18; i; --i) {
				uint8_t const c = squaredVal[intensity];
				for (auto iter = all1.begin(); iter != all1.end(); ++iter) {
					*iter = CRGB(c, c, c);
				}
				FastLED.show();
				intensity -= 15;
				delay(5);
			}
			delay(30);
		}

		delay(2000);
	}
#endif


	return;
#if 0
	static int hilightPos = -hilight.size_;
	static uint8_t c = 0;
	static ColorRange const *colors[] = {&forest, &autumn, &ocean, &pink};

	for (int i=0; i<NUM_LEDS; ++i) {
		// ledState[i].advance();
		// ledState[i].copy(leds[i], *colors[c]);
		leds[i] = colors[c]->percent(0);
	}

	for (int i=0; i<hilight.size_; ++i) {
		int const pos = hilightPos + i;
		if (pos >= 0  &&  pos < NUM_LEDS) {
			leds[pos] = colors[c]->percent(hilight.diff_[i]);
		}
	}
	if (++hilightPos == 40) {
		hilightPos = -hilight.size_;
		if (++c >= (uint8_t) (sizeof(colors) / sizeof(colors[0]))) {
			c = 0;
		}
	}

	FastLED.show();
	delay(30);
#endif

#if 0
	if ((int) (nextChange - millis()) <= 0) {
	Serial.println("Change");
		nextChange += changeWindow;
		if (++c >= (uint8_t) (sizeof(colors) / sizeof(colors[0]))) {
			c = 0;
		}
	}

	if (0) {
		for (int i=0; i<NUM_LEDS; ++i) {
			Serial.print(i);
			Serial.print(": ");
			Serial.print(leds[i].red);
			Serial.print(", ");
			Serial.print(leds[i].green);
			Serial.print(", ");
			Serial.println(leds[i].blue);
		}
		while (1);
	}
#endif
}
