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
#include "softTimer.h"
#include "btnDebounce.h"


// You can use any (4 or) 5 pins 
#define SCLK_PIN 13
#define MOSI_PIN 11
#define CS_PIN   10
#define RST_PIN  9
#define DC_PIN   8


// Color definitions
//
//  --------------------------
// | RED    | GREEN  | BLUE   |
// |--------------------------
// | 5 bits | 6 bits | 5 bits |
//  --------------------------

#define	BLACK      0x0000
#define	BLUE       0x001F
#define	RED        0xF800
#define	GREEN      0x07E0
#define CYAN       0x07FF
#define MAGENTA    0xF81F
#define YELLOW     0xFFE0
#define ORANGE     0xFA40
#define WHITE      0xFFFF

// Option 1: use any pins but a little slower
//Adafruit_SSD1331 display = Adafruit_SSD1331(CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  

// Option 2: must use the hardware SPI pins 
// (for UNO thats SCLK_PIN = 13 and sid = 11) and pin 10 must be 
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
static Adafruit_SSD1331 display = Adafruit_SSD1331(CS_PIN, DC_PIN, RST_PIN);

static SoftTimer clockTimer(1000, 15);
static BtnDebounce upBtn(2, LOW);
static BtnDebounce dnBtn(3, LOW);
static uint8_t const width = display.width();
static uint8_t const height = display.height();
static uint8_t const radius = (int) width * 5 / 8;


void setup() {
	Serial.begin(115200);
	display.begin();

	Serial.println("Hello World! Tea timer (c) Sami Sorell.");
	Serial.print("Display SSD1331 16-bit color OLED, resolution ");
	Serial.print(width);
	Serial.print("x");
	Serial.println(height);

	pinMode(2, INPUT_PULLUP);
	pinMode(3, INPUT_PULLUP);
}



void loop() {

	while (!clockTimer.hasExpired()) {
		if (upBtn.isPressed()) {
			int const toMax = 60 * 9 - clockTimer.shotsLeft();
			int const addMax15 = toMax > 15 ? 15 : toMax;
			clockTimer.reinit(clockTimer.shotsLeft() + addMax15);
			break;
		}
		if (dnBtn.isPressed()) {
			clockTimer.reinit(clockTimer.shotsLeft() > 15 ? clockTimer.shotsLeft() - 15 : 0);
			break;
		}
	}

	if (clockTimer.shotsLeft() < 5) {
		for (uint8_t i=0; i<radius; i+=5) {
			display.fillCircle(width / 2, height / 2, i, RED);
		}
	}

	display.fillScreen(BLACK);

	if (clockTimer.shotsLeft() < 6) { 
		display.setTextColor(RED); 
	}
	else if (clockTimer.shotsLeft() < 16) { 
		display.setTextColor(ORANGE); 
	}
	else { 
		display.setTextColor(GREEN); 
	}

	int time = clockTimer.shotsLeft();
	if (clockTimer.shotsLeft() < 6  &&  clockTimer.shotsLeft() > 0) {
	display.setTextSize(4);
		display.setCursor(40, 20);
		display.print(clockTimer.shotsLeft());
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

	if (clockTimer.shotsLeft() == 0) {
		for (uint8_t i=5; i; --i) {
			delay(500);
			display.fillScreen(BLACK);
			delay(500);
			display.setTextSize(4);
			display.setCursor(0, 20);
			display.setTextColor(RED);
			display.print("0:00");
		}
		clockTimer.reinit(0);
	}
}
