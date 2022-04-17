#include "debug.h"

/*----- Debugging functions ---------------------------------------------------
 * Does:
 *   Print various data types to Arduino Serial.
 *----------------------------------------------------------------------------*/
void print(char const prefix[], CRGB const &rgb, int format)
{
	Serial.print(prefix);
	Serial.print(rgb.r, format);
	Serial.print(",");
	Serial.print(rgb.g, format);
	Serial.print(",");
	Serial.println(rgb.b, format);
}

void print(char const prefix[], TwoBytes const &tb, int format)
{
	Serial.print(prefix);
	Serial.print(tb.l, format);
	Serial.print(",");
	Serial.println(tb.h, format);
}

void print(char const prefix[], ColorDelta const &delta, int format)
{
	Serial.print(prefix);
	Serial.print(delta.r(), format);
	Serial.print(",");
	Serial.print(delta.g(), format);
	Serial.print(",");
	Serial.println(delta.b(), format);
}

void print(char const prefix[], AccurateColor const &color, int format)
{
	Serial.print(prefix);
	Serial.print(color.r().raw, format);
	Serial.print(",");
	Serial.print(color.g().raw, format);
	Serial.print(",");
	Serial.println(color.b().raw, format);
}

void print(char const prefix[], int n0, int n1, int n2, int format)
{
	Serial.print(prefix);
	Serial.print(n0, format);
	Serial.print(",");
	Serial.print(n1, format);
	Serial.print(",");
	Serial.println(n2, format);
}
