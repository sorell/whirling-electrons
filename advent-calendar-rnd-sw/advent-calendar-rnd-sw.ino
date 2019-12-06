#include <EEPROM.h>

#define SWITCH_PIN 2
#define BUZZER_PIN 13
static uint8_t const ledRow[] = {9, 10, 11, 12};
static uint8_t const ledCol[] = {3, 4, 5, 6, 7, 8};
static uint8_t const ledRows = sizeof(ledRow) / sizeof(ledRow[0]);
static uint8_t const ledCols = sizeof(ledCol) / sizeof(ledCol[0]);


struct Nonvolatile
{
	unsigned long seed;
	unsigned long availNumbers;
};
static Nonvolatile nonvolatile;


static inline int ledNumToRow(int const num)
{
	return num / ledCols;
}

static inline int ledNumToCol(int const num)
{
	return num % ledCols;
}


static char buf[100];

static void ledWrite(int const num, int const on)
{
	int const col = ledNumToCol(num);
	int const row = ledNumToRow(num);
	int const colIO = ledCol[col];
	int const rowIO = ledRow[row];

	// snprintf(buf, sizeof(buf), "\nLed %d => col %d, row %d => IO %d %s, %d %s", num, col, row, colIO, on ? "HIGH" : "LOW", rowIO, on ? "LOW" : "HIGH");
	// Serial.println(buf);

	if (col >= ledCols) {
		Serial.println("Broken columns");
		while (1);
	}
	if (row >= ledRows) {
		Serial.println("Broken rows");
		while (1);
	}

	digitalWrite(colIO, on ? HIGH : LOW);
	digitalWrite(rowIO, on ? LOW : HIGH);
}


static unsigned long generateSeed(void)
{
	unsigned long seed = 0;

	for (int i=0; i<4; ++i) {
		seed <<= 8;
		seed |= analogRead(i) & 0xFF;
	}

	return seed;
}


static void clearEeprom(unsigned long seed)
{
	nonvolatile.seed = seed;
	// Intentionally leave seed unassigned. RAM noise is a good seed.
	nonvolatile.availNumbers = 0xFFFFFF;
	EEPROM.put(0, nonvolatile);
}


static int countRemainingWindows(void)
{
	// Count unopened calendar windows
	int remainingWindows = 0;
	for (long i=1; i<0xFFFFFF; i<<=1) {
		if (nonvolatile.availNumbers & i) {
			++remainingWindows;
		}
	}

	// snprintf(buf, sizeof(buf), "Numbers remaining: %2d. ", remainingWindows);
	// Serial.print(buf);

	return remainingWindows;
}


static int randomizeWindow(int const remainingWindows)
{
	// Randomize one from the set of unopened windows
	int cntr = random() % remainingWindows;

	// Find out the nth unopened window's number
	int windowNum = 0;
	long mask = 1;
	while (mask < 0xFFFFFF) {
		if (nonvolatile.availNumbers & mask) {
			if (--cntr < 0) {
				break;
			}
		}
		mask <<= 1;
		++windowNum;
	}

	// SW bug guard
	if (mask > 0xFFFFFF) {
		Serial.println("Whooops!");
		while (1);
	}

	return windowNum;
}


void setup()
{
	Serial.begin(115200);

	pinMode(SWITCH_PIN, INPUT_PULLUP);
	digitalWrite(BUZZER_PIN, HIGH);
	pinMode(BUZZER_PIN, OUTPUT);

	for (int i=0; i<ledRows; ++i) {
		pinMode(ledRow[i], OUTPUT);
		digitalWrite(ledRow[i], HIGH);
	}

	for (int i=0; i<ledCols; ++i) {
		pinMode(ledCol[i], OUTPUT);
		digitalWrite(ledCol[i], LOW);
	}

	EEPROM.get(0, nonvolatile);

	if (nonvolatile.availNumbers == 0xFFFFFFFF) {
		Serial.println("Clear eeprom");
		clearEeprom(generateSeed());
	}

	randomSeed(nonvolatile.seed);

	Serial.println("Start");
	snprintf(buf, sizeof(buf), "Available numbers: %06lx, seed %lx", nonvolatile.availNumbers, nonvolatile.seed);
	Serial.println(buf);
}


__attribute__((always_inline)) inline int
timeIsAfter(unsigned long const a, unsigned long const b)
{
	return (long) (a - b) > 0;
}


void loop() 
{
	if (digitalRead(SWITCH_PIN) == LOW) {
		unsigned long const now = millis();

		Serial.println("BTN");

		// Button debouncer
		while (!timeIsAfter(millis(), now + 100));

		int noTurningBack = 0;
		// Detect holding button for 7 seconds to erase eeprom contents
		while (digitalRead(SWITCH_PIN) == LOW) {
			int const held = millis() - now;

			if (held > 7000) {
				Serial.println("Clean eeprom");
				clearEeprom(random());
				while (digitalRead(SWITCH_PIN) == LOW);
				break;
			}
			else if (held > 2000) {
				noTurningBack = 1;
				int const ledOn = (held - 1500) / 500 % 2;
				ledWrite(0, ledOn);
			}
		}

		if (noTurningBack) {
			ledWrite(0, 0);
			delay(100);
			return;
		}

		snprintf(buf, sizeof(buf), "Available numbers: %06lx, seed %lx", nonvolatile.availNumbers, nonvolatile.seed);
		Serial.println(buf);
		Serial.print("Next window is: ");

		int const remainingWindows = countRemainingWindows();
		int lightShow = remainingWindows * 4;
		if (lightShow < 1) {
			Serial.println("we're all out");
			return;
		}

		int showWindow = 0;

		while (lightShow) {
			ledWrite(showWindow, 0);
			delay(50);
			showWindow = randomizeWindow(remainingWindows);
			--lightShow;

			ledWrite(showWindow, 1);
			delay(150);
		}

		Serial.println(showWindow);

		nonvolatile.seed = random();
		nonvolatile.availNumbers &= ~(1UL << showWindow);
snprintf(buf, sizeof(buf), "Put to eeprom: %06lx, seed %lx", nonvolatile.availNumbers, nonvolatile.seed);
Serial.println(buf);
		EEPROM.put(0, nonvolatile);

		delay(5000);

		// Nice 'dying light' effect
		int delayMs = 120;
		while (delayMs > 0) {
			ledWrite(showWindow, 1);
			delay(delayMs);
			delayMs -= 10;
			ledWrite(showWindow, 0);
			delay(delayMs / 2);
		}
	}
}
