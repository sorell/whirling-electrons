#include "debug.h"

/*----- Debugging functions ---------------------------------------------------
 * Does:
 *   Print various data types to Arduino Serial.
 *----------------------------------------------------------------------------*/
void print(CRGB const &rgb, char const prefix[])
{
	Serial.print(prefix);
	Serial.print(rgb.r);
	Serial.print(",");
	Serial.print(rgb.g);
	Serial.print(",");
	Serial.println(rgb.b);
}

void print(TwoBytes const &tb, char const prefix[])
{
	Serial.print(prefix);
	Serial.print(tb.l);
	Serial.print(",");
	Serial.println(tb.h);
}

void print(ColorDelta const &delta, char const prefix[])
{
	Serial.print(prefix);
	Serial.print(delta.r());
	Serial.print(",");
	Serial.print(delta.g());
	Serial.print(",");
	Serial.println(delta.b());
}

void print(int n0, int n1, int n2, char const prefix[])
{
	Serial.print(prefix);
	Serial.print(n0);
	Serial.print(",");
	Serial.print(n1);
	Serial.print(",");
	Serial.println(n2);
}
