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
#define WHITE           0xFFFF

// Option 1: use any pins but a little slower
//Adafruit_SSD1331 display = Adafruit_SSD1331(CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  

// Option 2: must use the hardware SPI pins 
// (for UNO thats SCLK_PIN = 13 and sid = 11) and pin 10 must be 
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_SSD1331 display = Adafruit_SSD1331(CS_PIN, DC_PIN, RST_PIN);


volatile int irqFired = 0;
int const ledPin = 13;

void pin2Irq()
{
	digitalWrite(ledPin, HIGH);
	Serial.println("2");
}

void pin3Irq()
{
	digitalWrite(ledPin, HIGH);
	Serial.println("3");
}


void setup() {
	Serial.begin(115200);
	Serial.print("hello!");
	display.begin();

	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);
	pinMode(2, INPUT_PULLUP);
	pinMode(3, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(2), pin2Irq, FALLING);
	attachInterrupt(digitalPinToInterrupt(3), pin3Irq, FALLING);
}

static int timeLeft = 75;

void loop() {
	display.fillScreen(BLACK);	
	display.setTextSize(4);
	display.setCursor(0, 20);

	switch (timeLeft % 7) {
	case 0: display.setTextColor(BLUE); break;
	case 1: display.setTextColor(RED); break;
	case 2: display.setTextColor(GREEN); break;
	case 3: display.setTextColor(CYAN); break;
	case 4: display.setTextColor(MAGENTA); break;
	case 5: display.setTextColor(YELLOW); break;
	case 6: display.setTextColor(WHITE); break;
		
	}

	int time = timeLeft;
	int const minutes = time / 60;
	time %= 60;
	int const secondTens = time / 10;
	time %= 10;
	int const secondUnits = time;

	display.print(minutes);
	display.print(':');
	display.print(secondTens);
	display.print(secondUnits);

	delay(1000);
	timeLeft--;

	digitalWrite(ledPin, LOW);
	// if (irqFired) {
	// 	Serial.print("IRQ!");
	// 	irqFired = 0;
	// 	digitalWrite(ledPin, HIGH);
	// 	delay(500);
	// }

	if (timeLeft < 0) {
		while (1);
	}
}
