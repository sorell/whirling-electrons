#ifndef _SS_DEBUG_H
#define _SS_DEBUG_H

#include <FastLED.h>
#include "LedUtils.h"

void print(CRGB const &rgb, char const prefix[] = "");
void print(TwoBytes const &tb, char const prefix[] = "");
void print(ColorDelta const &delta, char const prefix[] = "");
void print(int n0, int n1, int n2, char const prefix[] = "");

#endif  // _SS_DEBUG_H
