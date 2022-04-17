#ifndef _SS_DEBUG_H
#define _SS_DEBUG_H

#include <FastLED.h>
#include "LedUtils.h"

void print(char const prefix[], CRGB const &rgb, int format = DEC);
void print(char const prefix[], TwoBytes const &tb, int format = DEC);
void print(char const prefix[], ColorDelta const &delta, int format = DEC);
void print(char const prefix[], AccurateColor const &delta, int format = DEC);
void print(char const prefix[], int n0, int n1, int n2, int format = DEC);

#endif  // _SS_DEBUG_H
