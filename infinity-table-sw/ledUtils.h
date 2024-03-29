#ifndef _SS_LED_ITER_H
#define _SS_LED_ITER_H

struct CRGB;


/*----- Class -----------------------------------------------------------------
 * Accurate delta values for R,G,B calculated from difference of two colors and
 * divided for equal steps.
 * The delta accuracy is 1/128 of a pixel color accuracy.
 *----------------------------------------------------------------------------*/
class ColorDelta
{
public:
	ColorDelta() : r_(0), g_(0), b_(0)
	{}
	
	ColorDelta(CRGB const from, CRGB const to, int const steps)
	{
		init(from, to, steps);
	}
	
	void init(CRGB const beginColor, CRGB const endColor, int const steps);

	int16_t r() const { return r_; }
	int16_t g() const { return g_; }
	int16_t b() const { return b_; }

private:
	int16_t r_;
	int16_t g_;
	int16_t b_;
};


union TwoBytes
{
	TwoBytes(uint16_t value) : raw(value) {}

	static TwoBytes fromColor(uint8_t value) { return TwoBytes((uint16_t)value << 8); }

	uint16_t raw;
	struct
	{
#if __BYTE_ORDER == __BIG_ENDIAN
		uint8_t l;
		uint8_t h;
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		uint8_t h;
		uint8_t l;
#endif
	};
};


/*----- Class -----------------------------------------------------------------
 * R,G,B values of a color containing also fractions part. The upper byte is
 * used as CRGB value and lower byte is fractions used for accurate increments.
 *----------------------------------------------------------------------------*/
class AccurateColor
{
public:
	AccurateColor() : r_(0), g_(0), b_(0)
	{}

	AccurateColor(CRGB const &from) : 
		r_(TwoBytes::fromColor(from.red)),
		g_(TwoBytes::fromColor(from.green)),
		b_(TwoBytes::fromColor(from.blue))
	{}

	CRGB toCrgb() const { return { .r = r_.h, .g = g_.h, .b = b_.h }; }

	/*----- Function --------------------------------------------------------------
	 * Does:
	 *   Add delta to the fraction part of R,G,B values.
	 *----------------------------------------------------------------------------*/
	void add(ColorDelta const &delta)
	{
		r_.raw += delta.r();
		g_.raw += delta.g();
		b_.raw += delta.b();
	}

	AccurateColor &scale(int const fractions)
	{
		r_.raw = (((unsigned long) r_.raw) * fractions / 0xFF);
		g_.raw = (((unsigned long) g_.raw) * fractions / 0xFF);
		b_.raw = (((unsigned long) b_.raw) * fractions / 0xFF);
		return *this;
	}

	TwoBytes const &r() const { return r_; }
	TwoBytes const &g() const { return g_; }
	TwoBytes const &b() const { return b_; }

private:
	TwoBytes r_;
	TwoBytes g_;
	TwoBytes b_;
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

	// Call function f for each item between begin_ and end_.
	template <typename F>
	void forEachIdx(F f) const
	{ 
		int idx = 0;
		for (ptr_type p = begin_; p != end_; ++p, ++idx) { f(*p, idx); }
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

#endif  // _SS_LED_ITER_H
