// SSD1331 | ARDUINO NANO
//     GDN | GDN
//     VCC | 3V3
//     SCL | D13 (sclk)
//     SDA | D11 (mosi)
//     RES | D8
//      DC | D9
//      CS | D10


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include "SoftTimer.h"


// You can use any (4 or) 5 pins 
#define SCLK_PIN 13
#define MOSI_PIN 11
#define CS_PIN   10
#define RST_PIN  9
#define DC_PIN   8


// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define ORANGE          0xFF70
#define WHITE           0xFFFF

// Option 1: use any pins but a little slower
//Adafruit_SSD1331 display = Adafruit_SSD1331(CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  

// Option 2: must use the hardware SPI pins 
// (for UNO thats SCLK_PIN = 13 and sid = 11) and pin 10 must be 
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
static Adafruit_SSD1331 display = Adafruit_SSD1331(CS_PIN, DC_PIN, RST_PIN);

static volatile uint8_t irqFired = 0;
static uint8_t const ledPin = 13;
static SoftTimer timer;
static uint8_t const width = display.width();
static uint8_t const height = display.height();
static uint8_t const radius = (int) width * 5 / 8;


void pin2Irq()
{
	static SoftTimer debounceTimer(100, SoftTimer::ONESHOT);

	if (!debounceTimer.hasExpired()) {
		return;
	}
	debounceTimer.reinit(SoftTimer::ONESHOT);

	Serial.println("2");
	if (!timer.shotsLeft()) {
		timer.reinit(15);
	}
	else if (timer.shotsLeft() < 60 * 9) {
		timer.addShots(15);
	}
	else {
		timer.reinit(60 * 9);
	}

	irqFired = 1;
}

void pin3Irq()
{
	// digitalWrite(ledPin, HIGH);
	Serial.println("3");
}

void setup() {
	Serial.begin(115200);
	display.begin();

	timer.init(1000, SoftTimer::STOPPED);
	timer.init(1000, 7);

	Serial.println("Hello World! Tea timer (c) Sami Sorell.");
	Serial.print("Display SSD1331 16-bit color OLED, resolution ");
	Serial.print(width);
	Serial.print("x");
	Serial.println(height);

	// pinMode(ledPin, OUTPUT);
	// digitalWrite(ledPin, LOW);
	pinMode(2, INPUT_PULLUP);
	pinMode(3, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(2), pin2Irq, FALLING);
	attachInterrupt(digitalPinToInterrupt(3), pin3Irq, FALLING);
	irqFired = 0;
}


void loop() {
	while (!timer.hasExpired()  &&  !irqFired);
	irqFired = 0;

	if (timer.shotsLeft() < 5) {
		for (uint8_t i=0; i<radius; i+=5) {
			display.fillCircle(width / 2, height / 2, i, RED);
		}
	}

	display.fillScreen(BLACK);

	if (timer.shotsLeft() < 6) { 
		display.setTextColor(RED); 
	}
	else if (timer.shotsLeft() < 16) { 
		display.setTextColor(ORANGE); 
	}
	else { 
		display.setTextColor(GREEN); 
	}

	int time = timer.shotsLeft();
	if (timer.shotsLeft() < 6) {
	display.setTextSize(4);
		display.setCursor(40, 20);
		display.print(timer.shotsLeft());
	}
	else {
		int const minutes = time / 60;
		time %= 60;
		int const secondTens = time / 10;
		time %= 10;
		int const secondUnits = time;

		display.setTextSize(4);
		display.setCursor(0, 20);
		display.print(minutes);
		display.print(':');
		display.print(secondTens);
		display.print(secondUnits);
	}

	if (timer.shotsLeft() == 0) {
		for (uint8_t i=5; i; --i) {
			delay(500);
			display.fillScreen(BLACK);
			delay(500);
			display.setTextSize(4);
			display.setCursor(0, 20);
			display.setTextColor(RED);
			display.print("0:00");
		}
		irqFired = 0;
		timer.reinit(0);
	}
}
