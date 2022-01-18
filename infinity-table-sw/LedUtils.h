#ifndef _SS_LED_ITER_H
#define _SS_LED_ITER_H


//
// Led type defined in FastLED library.
//
class CRBG;


namespace LedUtils {

union TwoBytes
{
	TwoBytes(uint16_t i) : val(i) {}

	static TwoBytes fromColor(uint8_t i) { return TwoBytes((uint16_t)i << 8); }

	uint16_t val;
	struct
	{
		uint8_t l;
		uint8_t h;
	};
};


//
// An abstract base class for Iterator traversing (f.ex) CRGBs in LedArray.
//
template <typename T>
class IteratorBase {
public:
	typename T::value_type &operator * () { return *p_; }
	typename T::value_type const &operator * () const { return *p_; }
	typename T::value_type *operator -> () { return p_; }
	typename T::value_type const *operator -> () const { return p_; }

	bool operator == (IteratorBase const &rhs) const { return p_ == rhs.p_; }
	bool operator != (IteratorBase const &rhs) const { return p_ != rhs.p_; }

protected:
	IteratorBase(typename T::ptr_type p) : p_(p) {};
	typename T::ptr_type p_;
};

//
// A forward advancing Iterator for LedArray.
//
template <typename T>
class ForwardIterator : public IteratorBase<T> {
public:
	ForwardIterator(typename T::ptr_type p) : IteratorBase<T>(p) {}

	ForwardIterator &operator = (ForwardIterator const &rhs) { IteratorBase<T>::p_ = rhs.p_; return *this; }

	ForwardIterator &operator ++ () { IteratorBase<T>::p_++; return *this; }
	ForwardIterator &operator -- () { IteratorBase<T>::p_--; return *this; }
};

//
// A backward advancing Iterator for LedArray.
//
template <typename T>
class ReverseIterator : public IteratorBase<T> {
public:
	ReverseIterator(typename T::ptr_type p) : IteratorBase<T>(p) {}
	ReverseIterator &operator ++ () { IteratorBase<T>::p_--; return *this; }
	ReverseIterator &operator -- () { IteratorBase<T>::p_++; return *this; }
};


//
// An abstract base class containing common members of various LedArray classes.
//
// This is a virtual array of CRGB that is projected onto a continuous, actual array of CRGB allocated 
// in the sw, holding only the begin and end points, whose inheriting classes provide means to iterate
// between them.
//


//
// A continuous array of leds, traversed to forward direction by default Iterator.
//
// For a strip of LEDs that is physically placed so that the control signal enters from left hand side,
// (meaning that index 0 of the LEDs in the sw starts from left and increments to right) this class' default
// iterator's ++-operator advances from left to right.
//
template <typename T>
class Array
{
public:
	typedef T value_type;
	typedef T *ptr_type;
	typedef ForwardIterator<Array<T>> iterator;
	typedef ReverseIterator<Array<T>> r_iterator;

	Array(ptr_type begin, int amount) : begin_(begin), end_(begin + amount) {}

	int length() const { return end_ - begin_; }
	int tailRoom(int const from) const { return length() - from; }

	int normalizedPos(int pos) const { return pos % length(); }

	iterator begin() { return iterator(begin_); }
	iterator end() { return iterator(end_); }
	r_iterator r_begin() { return r_iterator(end_-1); }
	r_iterator r_end() { return r_iterator(begin_-1); }

	iterator at(int pos) { return iterator(begin_ + pos); }
	r_iterator r_at(int pos) { return r_iterator(end_ - pos - 1); }

	iterator next(iterator it) { return ++it != end() ? it : begin(); }
	iterator prev(iterator it) { return it == begin() ? --end() : --it; }
	r_iterator next(r_iterator it) { return ++it != r_end() ? it : r_begin(); }
	r_iterator prev(r_iterator it) { return it == r_begin() ? --r_end() : --it; }

	// Call function f for each item between begin_ and end_.
	template <typename F>
	void forEach(F f) const
	{ 
		for (ptr_type p = begin_; p != end_; ++p) { f(*p); }
	}

protected:
	ptr_type const begin_;
	ptr_type const end_;
};


typedef Array<CRGB> LedArray;



class SquaredVal {
public:
	SquaredVal() {
		for (uint32_t i=0; i<sizeof(values)/sizeof(values[0]); ++i) {
			float f = (float) i / 255.0f;
			values[i] = (uint8_t) (f * f * 255.0f);
		}
	}
	// uint8_t operator [] (unsigned int const idx) const {
	// 	if (idx > sizeof(values)/sizeof(values[0])) {
	// 		Serial.print("SquaredVal["); Serial.print(idx); Serial.println("] called\n");
	// 		while (1);
	// 	}
	// 	return values[idx];
	// }
	uint8_t operator [] (unsigned int const idx) const { return idx; }

private:
	uint8_t values[256];
};


}  // namespace LedUtils

#if 0

static CRGB CrbgInit(uint8_t const r, uint8_t const g, uint8_t const b)
{
	return {.red = (uint8_t) ((float) r / 255.0f * (float) MAX_BRIGHT), 
		.green = (uint8_t) ((float) g / 255.0f * (float) MAX_BRIGHT), 
		.blue = (uint8_t) ((float) b / 255.0f * (float) MAX_BRIGHT)};
}


class ColorRange {
public:
	ColorRange(CRGB const &high, CRGB const &low) : 
		high_(high), low_(low),
		redInc_((float) (high.red - low.red) / 100.0f), 
		greenInc_((float) (high.green - low.green) / 100.0f),
		blueInc_((float) (high.blue - low.blue) / 100.0f) {}

	CRGB percent(float const pc) const {
		return {(uint8_t) (low_.red + (uint8_t) (redInc_ * pc)), (uint8_t) (low_.green + (uint8_t) (greenInc_ * pc)), (uint8_t) (low_.blue + (uint8_t) (blueInc_ * pc))};
	}

private:
	CRGB const high_;
	CRGB const low_;
	float const redInc_;
	float const greenInc_;
	float const blueInc_;
};


class Hilight {
public:
		Hilight() : diff_({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 90, 80, 70, 60, 50, 40, 30, 20, 10}), size_(sizeof(diff_)/sizeof(diff_[0])) {
			// diff_[0] = 15; diff_[1] = 30; diff_[2] = 45; diff_[3] = 60; diff_[4] = 45; diff_[5] = 30; diff_[6] = 15;
		}
public:
	int8_t const diff_[19];
	int const size_;
};

static SquaredVal const squaredVal;

static CRGB const black = {.red = 0, .green = 0, .blue = 0};
static ColorRange const pink = {CrbgInit(255, 110, 199), CrbgInit(26, 11, 20)};
// static ColorRange const forest = {CrbgInit(57, 255, 20), CrbgInit(6, 26, 2)};
static ColorRange const forest = {CrbgInit(0x49, 0xE2, 0x0E), CrbgInit(0x55, 0x10, 0x33)};
static ColorRange const ocean = {CrbgInit(0, 180, 255), CrbgInit(0, 18, 26)};
static ColorRange const autumn = {CrbgInit(255, 0, 0), CrbgInit(255, 255, 0)};

static int8_t const colorInc = 2;


static bool stop = false;


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
static unsigned long const changeWindow = 5000;
static unsigned long nextChange;
static Hilight hilight;

void setup() {
	Serial.begin(115200);

	FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

	// for (int i=0; i<NUM_LEDS; ++i) {
	// 	ledState[i] = {0, 1};
	// }
	// for (int i=0; i<min(NUM_LEDS, 8); ++i) {
	// 	ledState[i] = {(int8_t) (i * 10), 1};
	// }

	nextChange = millis() + changeWindow;
}


void loop() {
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
#endif

#endif  // _SS_LED_ITER_H
