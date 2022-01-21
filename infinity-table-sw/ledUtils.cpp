#include <FastLED.h>
#include "ledUtils.h"

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
void ColorDelta::init(CRGB const beginColor, CRGB const endColor, int const steps)
{
	r_ = ((((int16_t)endColor.red - (int16_t)beginColor.red) << 7) / steps) << 1;
	g_ = ((((int16_t)endColor.green - (int16_t)beginColor.green) << 7) / steps) << 1;
	b_ = ((((int16_t)endColor.blue - (int16_t)beginColor.blue) << 7) / steps) << 1;
}
