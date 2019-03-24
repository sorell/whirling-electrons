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
#include <avr/pgmspace.h>
#include <SPI.h>
#include "softTimer.h"
#include "btnDebounce.h"
#include "notes.h"


#define SCLK_PIN 13
#define MOSI_PIN 11
#define CS_PIN   10
#define RST_PIN  9
#define DC_PIN   8

#define BTNUP_PIN 2
#define BTNDN_PIN 3
#define BUZZER_PIN 6


// ****************************************************************************
// *** Stuff for music                                                      ***
// ****************************************************************************

typedef struct {
	int f;  // Frequence
	int t;  // Time
} Note;

struct SongPart {
	Note const *notes;
	uint8_t size;
	// SongPart *next;
};

static Note constexpr vader1[] = {
	{A4, 500}, {A4, 500}, {A4, 500}, {F4, 350}, {C5, 150}, {A4, 500}, {F4, 350}, {C5, 150}, {A4, 650}, {0, 500}, 
	{E5, 500}, {E5, 500}, {E5, 500}, {F5, 350}, {C5, 150}, {A4, 500}, {F4, 350}, {C5, 150}, {A4, 650}, {0, 500}
};
static Note constexpr vader2[] = {
	{A5, 500}, {A4, 300}, {A4, 150}, {A5, 500}, {GS5, 325}, {G5, 175}, {FS5, 125}, {F5, 125}, {FS5, 250}, {0, 325},
	{AS4, 250}, {DS5, 500}, {D5, 325}, {CS5, 175}, {C5, 125}, {B4, 125}, {C5, 250}, {0, 350}
};
static Note constexpr vader3[] = {
	{F4, 250}, {GS4, 500}, {F4, 350}, {A4, 125}, {C5, 500}, {A4, 375}, {C5, 125}, {E5, 650}, {0, 500}
};
static Note constexpr vader4[] = {
	{F4, 250}, {GS4, 500}, {F4, 350}, {C5, 125}, {A4, 500}, {F4, 375}, {C5, 125}, {A4, 650}
};
static SongPart constexpr song[] = {
	{vader1, sizeof(vader1)/sizeof(vader1[0])}, 
	{vader2, sizeof(vader2)/sizeof(vader2[0])}, 
	{vader3, sizeof(vader3)/sizeof(vader3[0])}, 
	{vader2, sizeof(vader2)/sizeof(vader2[0])}, 
	{vader4, sizeof(vader4)/sizeof(vader4[0])}
};


void playNotes(Note const *const notes, int const size)
{
	for (Note const *note=notes; note<notes+size; ++note) {
		tone(BUZZER_PIN, note->f, note->t);
		delay(note->t + 10);
	}
}


void playNextNote(SongPart const *const songParts, int const parts, SongPart const **const pSongPart, Note const **const pNote, SoftTimer *const timer)
{
	int const freq = (*pNote)->f;
	int const time = (*pNote)->t;
	tone(BUZZER_PIN, freq, time);

	SongPart const *part = *pSongPart;
	if (++(*pNote) >= part->notes + part->size) {
		if (++(*pSongPart) >= songParts + parts) {
			return;
		}
		part = *pSongPart;
		*pNote = part->notes;
	}

	timer->init(time + 10, SoftTimer::ONESHOT);
}


// ****************************************************************************
// *** Stuff for display                                                    ***
// ****************************************************************************

static Adafruit_SSD1331 display = Adafruit_SSD1331(CS_PIN, DC_PIN, RST_PIN);
static uint8_t const width = display.width();
static uint8_t const height = display.height();
static uint8_t const radius = (int) width * 5 / 8;


// SSD1331 takes in 16-bit (5, 6, 5) RBG pixels.
//
//  -----------------------------------------------------------------
// | RED                 | GREEN               | BLUE                |
// |-----------------------------------------------------------------|
// | 5 bits              | 6 bits              | 5 bits              |
// | (0-31) << 11        | (0-63) << 6         | (0-31) << 0         |
// | 0b11111000 00000000 | 0b00000111 11100000 | 0b00000000 00011111 |
// | 0xF8000             | 0x07E0              | 0x001F              |
//  -----------------------------------------------------------------

uint8_t toRed(uint16_t const color) { return (color >> 11) & 0x1f; }
uint8_t toGreen(uint16_t const color) { return (color >> 5) & 0x3f; }
uint8_t toBlue(uint16_t const color) { return color & 0x1f; }
uint16_t toColor(uint16_t const r, uint16_t const g, uint16_t const b) { return (r << 11) | (g << 5) | b; }

#define	BLACK      0x0000
#define	BLUE       0x001F
#define	RED        0xF800
#define	GREEN      0x07E0
#define CYAN       0x07FF
#define MAGENTA    0xF81F
#define YELLOW     0xFFE0
#define ORANGE     0xFA40
#define WHITE      0xFFFF


//
// Routines to draw monochrome, 2-bit, 4-bit and 16-bit picture data on screen
//
void draw1bitData(uint8_t const *data, int w, int h)
{
	int const loops = w * h / 8;

	for(int i=loops; i; --i) {
		uint8_t byte = pgm_read_byte_near(data);
		for (int bit=8; bit; --bit) {
			display.writeColor((byte & 1) ? WHITE : BLACK, 1);
			byte >>= 1;
		}
		++data;
	}
}


void draw2bitData(uint8_t const *data, uint16_t const *palette, int w, int h)
{
	for (int row=h; row; --row) {
		for (int col=w; col>0; col-=4) {
			uint8_t byte = pgm_read_byte_near(data);
			switch(col) {
			default:
				display.writeColor(palette[byte & 0x3], 1);
				byte >>= 2;
			case 3:
				display.writeColor(palette[byte & 0x3], 1);
				byte >>= 2;
			case 2:
				display.writeColor(palette[byte & 0x3], 1);
				byte >>= 2;
			case 1:
				display.writeColor(palette[byte & 0x3], 1);
				break;
			}
			++data;
		}
	}
}


void draw4bitData(uint8_t const *data, uint16_t const *palette, int w, int h)
{
	for (int row=h; row; --row) {
		for (int col=w; col>0; col-=2) {
			uint8_t byte = pgm_read_byte_near(data);
			display.writeColor(palette[byte & 0xF], 1);
			if (col > 1) {
				display.writeColor(palette[byte >> 4], 1);
			}
			++data;
		}
	}
}


void draw16bitData(uint16_t const *data, int w, int h)
{
	int const loops = w * h;

	for (int i=0; i<loops; ++i) {
		display.writeColor(pgm_read_word_near(data), 1);
		data++;
	}
}


// ****************************************************************************
// *** Images created with bmp2arduino (in the same repo)                   ***
// ****************************************************************************

#include <stdint.h>
#include <avr/pgmspace.h>

// 2-bit picture data extracted from file teacup.bmp
int constexpr teacupPicWidth = 46;
int constexpr teacupPicHeight = 27;
static uint8_t const PROGMEM teacupPicData[] = {
    0x00, 0x00, 0x00, 0x55, 0x55, 0x55, 0x55, 0x55, 0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x56, 0x01, 0x00, 0x00, 
    0x00, 0x40, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x06, 0x00, 0x00, 
    0x00, 0x90, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x1a, 0x00, 0x00, 
    0x00, 0x50, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x16, 0x00, 0x00, 
    0x00, 0x10, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x56, 0x1d, 0x00, 0x00, 
    0x00, 0x10, 0x00, 0x55, 0x55, 0x55, 0x55, 0x55, 0x01, 0x5c, 0x15, 0x00, 
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x40, 0x00, 
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x05, 0x01, 
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x10, 0x04, 
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x10, 0x04, 
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x10, 0x04, 
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x10, 0x04, 
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0xf5, 0x01, 
    0x00, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0x7f, 0x00, 
    0x40, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5f, 0x15, 0x00, 
    0x10, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x70, 0x00, 
    0x04, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x1f, 0xf0, 0x01, 
    0x04, 0x40, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x07, 0xc0, 0x01, 
    0x01, 0x00, 0xf5, 0x03, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x01, 0xc0, 0x07, 
    0x01, 0x00, 0x50, 0xff, 0xff, 0xff, 0xff, 0xff, 0x17, 0x00, 0xc0, 0x07, 
    0x04, 0x00, 0x00, 0x55, 0x55, 0x55, 0x55, 0x55, 0x01, 0x00, 0xc0, 0x01, 
    0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x01, 
    0xd0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x7f, 0x00, 
    0x40, 0xd5, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x7f, 0x15, 0x00, 
    0x00, 0x40, 0xd5, 0xff, 0xff, 0xff, 0xff, 0xff, 0x5f, 0x15, 0x00, 0x00, 
    0x00, 0x00, 0x40, 0x55, 0x55, 0x55, 0x55, 0x55, 0x05, 0x00, 0x00, 0x00, 
};

static uint16_t const teacupPicPalette[4] = {0x0000, 0xffff, 0xaaa0, 0x8430};


// 2-bit picture data extracted from file steam.bmp
int constexpr steamPicWidth = 19;
int constexpr steamPicHeight = 12;
static uint8_t const PROGMEM steamPicData[] = {
    0x90, 0x00, 0x25, 0x40, 0x02, 
    0x24, 0x40, 0x02, 0x90, 0x00, 
    0x08, 0x90, 0x00, 0x24, 0x00, 
    0x08, 0x90, 0x00, 0x24, 0x00, 
    0x08, 0x90, 0x00, 0x24, 0x00, 
    0x24, 0x40, 0x02, 0x90, 0x00, 
    0x90, 0x00, 0x29, 0x40, 0x02, 
    0x40, 0x02, 0x90, 0x00, 0x09, 
    0x00, 0x09, 0x40, 0x02, 0x24, 
    0x00, 0x09, 0x40, 0x02, 0x24, 
    0x00, 0x09, 0x40, 0x02, 0x24, 
    0x40, 0x02, 0x90, 0x00, 0x09, 
};

static uint16_t const steamPicPalette[4] = {0x0000, 0xffff, 0x8430, 0xffff};


// ****************************************************************************
// *** Images created with bmp2arduino (in the same repo)                   ***
// ****************************************************************************

static SoftTimer clockTimer(1000, 15);
static BtnDebounce upBtn(BTNUP_PIN, LOW, 20);
static BtnDebounce dnBtn(BTNDN_PIN, LOW, 20);


static bool checkButtons(void)
{
	if (upBtn.isPressed()) {
		int const toMax = 60 * 9 - clockTimer.shotsLeft();
		int const addMax15 = toMax > 15 ? 15 : toMax;
		clockTimer.reinit(clockTimer.shotsLeft() + addMax15);
		return true;
	}
	if (dnBtn.isPressed()) {
		clockTimer.reinit(clockTimer.shotsLeft() > 15 ? clockTimer.shotsLeft() - 15 : 0);
		return true;
	}
	return false;
}


// Draw time on screen. Last 5 secods are one digit only and with circle animation
static void drawTime(int time)
{
	static uint16_t const firstColor = GREEN;
	static uint16_t const lastColor = RED;
	static float const deltaRed = (float) (toRed(firstColor) - toRed(lastColor)) / 60.0f;
	static float const deltaGreen = (float) (toGreen(firstColor) - toGreen(lastColor)) / 60.0f;
	static float const deltaBlue = (float) (toBlue(firstColor) - toBlue(lastColor)) / 60.0f;

	// Determine sliding color from firstColor to lastColor using remaining time as a factor
	float const factor = time > 60 ? 60 : time;
	uint16_t const color = toColor(toRed(lastColor) + (deltaRed * factor + 0.5f), toGreen(lastColor) + (deltaGreen * factor + 0.5f), toBlue(lastColor) + (deltaBlue * factor + 0.5f));

	// Circle animation
	if (time < 6) {
		for (uint8_t i=0; i<radius; i+=5) {
			display.fillCircle(width / 2, height / 2, i, color);
		}
	}

	display.fillScreen(BLACK);
	display.setTextColor(color);

	// One digit only
	if (time < 6) {
		display.setTextSize(4);
		display.setCursor(40, 20);
		display.print(time);
	}
	// Minutes and seconds
	else if (time > 0) {
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
}


void animateSteam(int offset, int x, int y)
{
	int const rowBytes = (steamPicWidth + 3) / 4;

	display.setAddrWindow(x, y, steamPicWidth, steamPicHeight);
	display.startWrite();
	draw2bitData(steamPicData + offset * rowBytes, steamPicPalette, steamPicWidth, steamPicHeight - offset);
	draw2bitData(steamPicData, steamPicPalette, steamPicWidth, offset);
	display.endWrite();
}


void teacupAnimation(void)
{
	display.fillScreen(BLACK);

	// Draw teacup
	display.setAddrWindow(26, 25, teacupPicWidth, teacupPicHeight);
	display.startWrite();
	draw2bitData(teacupPicData, teacupPicPalette, teacupPicWidth, teacupPicHeight);
	display.endWrite();

	// Animate steam
	int heightOffset = 0;
	int cont = 1200;
	SoftTimer delayTimer;

	while (cont) {
		animateSteam(heightOffset, 39, 13);
		if (++heightOffset >= steamPicHeight) {
			heightOffset = 0;
		}
		--cont;
		delayTimer.init(100, SoftTimer::ONESHOT);
		while (!delayTimer.hasExpired()) {
			if (checkButtons()) {
				cont = 0;
				break;
			}
		}
	}

	display.fillScreen(BLACK);
}


void teacupAnimationWithSong(SongPart const *const songParts, int const parts)
{
	display.fillScreen(BLACK);

	// Draw teacup
	display.setAddrWindow(26, 25, teacupPicWidth, teacupPicHeight);
	display.startWrite();
	draw2bitData(teacupPicData, teacupPicPalette, teacupPicWidth, teacupPicHeight);
	display.endWrite();

	// Animate steam
	int const rowBytes = (steamPicWidth + 3) / 4;
	int heightOffset = 0;
	int cont = 1200;
	SoftTimer animationDelay;

	SoftTimer musicDelay(0, SoftTimer::ONESHOT);  // Immediately
	SongPart const *songPart = songParts;
	Note const *note = songPart->notes;


	while (cont) {
		display.setAddrWindow(39, 13, steamPicWidth, steamPicHeight);
		display.startWrite();

		// int const lastRow = heightOffset - 1 < 0 : steamPicHeight
		int row = heightOffset;
		do {
			if (musicDelay.hasExpired()) {
				playNextNote(songParts, parts, &songPart, &note, &musicDelay);
			}
			draw2bitData(steamPicData + row * rowBytes, steamPicPalette, steamPicWidth, 1);
			if (++row >= steamPicHeight) {
				row = 0;
			}
		} while (row != heightOffset);

		display.endWrite();

		if (++heightOffset >= steamPicHeight) {
			heightOffset = 0;
		}
		--cont;
		animationDelay.init(100, SoftTimer::ONESHOT);
		while (!animationDelay.hasExpired()) {
			if (musicDelay.hasExpired()) {
				playNextNote(songParts, parts, &songPart, &note, &musicDelay);
			}
			if (checkButtons()) {
				if (musicDelay.shotsLeft()) {
					musicDelay.stop();
				}
				else {
					cont = 0;
				}
				break;
			}
		}
	}

	display.fillScreen(BLACK);
}


void setup() {
	Serial.begin(115200);
	display.begin();
	display.fillScreen(BLACK);

	Serial.println("Hello World! Tea timer (c) Sami Sorell.");
	Serial.print("Display SSD1331 16-bit color OLED, resolution ");
	Serial.print(width);
	Serial.print("x");
	Serial.print(height);
	Serial.println(".");

	pinMode(BTNUP_PIN, INPUT_PULLUP);
	pinMode(BTNDN_PIN, INPUT_PULLUP);

	pinMode(BUZZER_PIN, OUTPUT);
}


void loop() {
	while (!clockTimer.hasExpired()) {
		if (checkButtons()) {
			break;
		}
	}

	// When shotsLeft() == 0 no number is drawn, but the red circle effect is
	drawTime(clockTimer.shotsLeft());
	
	// Tea is served!
	if (clockTimer.shotsLeft() == 0) {
		clockTimer.reinit(0);
		teacupAnimationWithSong(song, sizeof(song)/sizeof(song[0]));

		// If clockTimer was changed by up button during teacupAnimation()
		if (clockTimer.shotsLeft() > 0) {
			drawTime(clockTimer.shotsLeft());
		}
	}
}
