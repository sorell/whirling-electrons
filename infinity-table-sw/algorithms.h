#ifndef _SS_ALGORITHMS_H
#define _SS_ALGORITHMS_H

struct CRGB;

#include <FastLED.h>
#include "ledUtils.h"


/*----- Function --------------------------------------------------------------
 * Does:
 *   Set a color to a number of leds.
 *
 * Wants:
 *   array: The LedArray to apply the color shift on.
 *   atFunc: The LedArray at() function used to determine starting position.
 *   color: The color to set.
 *   pos: The position to start the trail from.
 *   amount: Number of leds to cover.
 *----------------------------------------------------------------------------*/
template <typename F>
void fillRange(LedArray &array, F const atFunc, CRGB const &color, int const pos = 0, int amount = -1)
{
	if (amount < 0)
		amount = array.length();

	for (auto it = atFunc(pos); amount > 0; --amount) {
		*it = color;
		it = array.next(it);
	}
}


/*----- Function --------------------------------------------------------------
 * Does:
 *   Call fillRange() with LedArray::at(), giving an iterator proceeding 
 *   clockwise.
 *
 * Wants:
 *   See fillRange().
 *----------------------------------------------------------------------------*/
inline void fillRange_ccw(LedArray &array, CRGB const &color, int pos = 0, int amount = -1)
{
	fillRange(array, [&](int p){ return array.at(p);}, color, pos, amount);
}


/*----- Function --------------------------------------------------------------
 * Does:
 *   Call fillRange() with LedArray::at(), giving an iterator proceeding 
 *   counter-clockwise.
 *
 * Wants:
 *   See fillRange().
 *----------------------------------------------------------------------------*/
inline void fillRange_cw(LedArray &array, CRGB const &color, int pos = 0, int amount = -1)
{
	fillRange(array, [&](int p){ return array.r_at(p);}, color, pos, amount);
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
void fillColorTransformation(LedArray &array, F const atFunc, CRGB const &beginColor, CRGB const &endColor, int const pos = 0, int amount = -1)
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
 *   Call fillColorTransformation() with LedArray::at(), giving an iterator 
 *   proceeding counter-clockwise.
 *
 * Wants:
 *   See fillColorTransformation().
 *----------------------------------------------------------------------------*/
inline void fillColorTransformation_ccw(LedArray &array, CRGB const &beginColor, CRGB const &endColor, int pos = 0, int amount = -1)
{
	fillColorTransformation(array, [&](int p){ return array.at(p);}, beginColor, endColor, pos, amount);
}


/*----- Function --------------------------------------------------------------
 * Does:
 *   Call fillColorTransformation() with LedArray::at(), giving an iterator 
 *   proceeding clockwise.
 *
 * Wants:
 *   See fillColorTransformation().
 *----------------------------------------------------------------------------*/
inline void fillColorTransformation_cw(LedArray &array, CRGB const &beginColor, CRGB const &endColor, int pos = 0, int amount = -1)
{
	fillColorTransformation(array, [&](int p){ return array.r_at(p);}, beginColor, endColor, pos, amount);
}

#endif  // _SS_ALGORITHMS_H
