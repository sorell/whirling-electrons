/*************************************************** 
  This is a example sketch demonstrating bitmap drawing
  capabilities of the SSD1331 library  for the 0.96" 
  16-bit Color OLED with SSD1331 driver chip

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/684

  These displays use SPI to communicate, 4 or 5 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution

  The Adafruit GFX Graphics core library is also required
  https://github.com/adafruit/Adafruit-GFX-Library
  Be sure to install it!
 ****************************************************/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

// static int const screenWidth = 96;
// static int const screenHeight = 64;


static void toAscii(uint16_t const *const pictureData, int const w, int const h)
{
    uint16_t const *p = pictureData;
    for (int row=0; row<h; row++) {
        for (int col=0; col<w; col++) {
            if (*p != 0xFFFF)
                printf("#");
            else
                printf(" ");
            ++p;
        }
        printf("\n");
    }
}


static void toArduino1bit(uint16_t const *const pictureData, int const w, int const h, char const *const filename)
{
    uint16_t const *p = pictureData;
    printf("#include <stdint.h>\n");
    printf("#include <avr/pgmspace.h>\n\n");
    printf("// 1-bit picture data extracted from file %s\n", filename);
    printf("int constexpr pictureWidth = %d;\n", w);
    printf("int constexpr pictureHeight = %d;\n", h);
    printf("static uint8_t const PROGMEM picturebitData[] = {\n");
    for (int row=0; row<h; row++) {
        printf("    ");
        for (int col=0; col<w; col+=8) {
            uint8_t data = 0;
            for (int word=0; word<8; ++word) {
                if (*p++ != 0) {
                    data |= (1 << word);
                }
            }
            printf("0x%02x, ", data);
        }
        printf("\n");
    }
    printf("};\n");
}


static void toArduinoPalette(uint16_t const *const pictureData, int const w, int const h, int const paletteBits, char const *const filename)
{
    uint16_t const *p = pictureData;
    bool issuePaletteWarning = false;

    printf("#include <stdint.h>\n");
    printf("#include <avr/pgmspace.h>\n\n");
    printf("// %d-bit picture data extracted from file %s\n", paletteBits, filename);
    printf("int constexpr pictureWidth = %d;\n", w);
    printf("int constexpr pictureHeight = %d;\n", h);
    printf("static uint8_t const PROGMEM pictureData[] = {\n");

    int const paletteSize = paletteBits * paletteBits;
    int *const palette = (int *) malloc(sizeof(int) * paletteSize);
    int const colorsPerWord = 8 / paletteBits;

    for (int pIdx=0; pIdx<paletteSize; ++pIdx) {
        palette[pIdx] = -1;
    }

    for (int row=h; row>0; --row) {
        printf("    ");
        for (int col=w; col>0; col-=colorsPerWord) {
            uint8_t data = 0;
            for (int word=0; word<(col>colorsPerWord?colorsPerWord:col); ++word) {
                int colorIdx = -1;
                int availIdx = -1;
                for (int pIdx=0; pIdx<paletteSize; ++pIdx) {
                    if (palette[pIdx] == *p) {
                        colorIdx = pIdx;
                        break;
                    }
                    if (availIdx < 0  &&  palette[pIdx] < 0) {
                        availIdx = pIdx;
                    }
                }
                if (colorIdx < 0) {
                    if (availIdx >= 0) {
                        palette[availIdx] = *p;
                        colorIdx = availIdx;
                    }
                }
                if (colorIdx < 0) {
                    issuePaletteWarning = true;  // There wasn't space in the palette for the color
                    // fprintf(stderr, "Can't fit color: 0x%02x%02x%02x\n", *p >> 11, (*p >> 5) & 0x3f, *p & 0x1f);
                }
                else {
                    data |= colorIdx << (word * paletteBits);
                }
                ++p;
            }
            printf("0x%02x, ", data);
        }
        printf("\n");
    }
    printf("};\n\nstatic uint16_t const picturePalette[%d] = {", paletteSize);
    for (int pIdx=0; pIdx<paletteSize; ++pIdx) {
        if (pIdx) {
            printf(", ");
        }
        printf("0x%04hx", palette[pIdx]);
    }
    printf("};\n");

    if (issuePaletteWarning) {
        fprintf(stderr, "WARNING: all found colors could not fit in the palette\n");
    }

    free(palette);
}

static void toArduino16bit(uint16_t const *const pictureData, int const w, int const h, char const *const filename)
{
    uint16_t const *p = pictureData;
    printf("#include <stdint.h>\n");
    printf("#include <avr/pgmspace.h>\n\n");
    printf("// 16-bit picture data extracted from file %s\n", filename);
    printf("int constexpr pictureWidth = %d;\n", w);
    printf("int constexpr pictureHeight = %d;\n", h);
    printf("static uint16_t const PROGMEM pictureData[] = {\n");
    for (int row=0; row<h; row++) {
        printf("    ");
        for (int col=0; col<w; col++) {
            printf("0x%04x, ", *p);
            ++p;
        }
        printf("\n");
    }
    printf("};\n");
}


static uint16_t read16(FILE *f) 
{
    uint16_t result;
    if (fread(&result, sizeof(result), 1, f) != 1) {
        fprintf(stderr, "%d Can't read: %s\n", __LINE__, strerror(errno));
    }
    return result;
}


static uint32_t read32(FILE *f) 
{
    uint32_t result;
    if (fread(&result, sizeof(result), 1, f) != 1) {
        fprintf(stderr, "%d Can't read: %s\n", __LINE__, strerror(errno));
    }
    return result;
}


static uint16_t readPixel(FILE *f)
{
    uint32_t result;
    if (fread(&result, 3, 1, f) != 1) {
        fprintf(stderr, "%d Can't read: %s\n", __LINE__, strerror(errno));
    }
    uint32_t b = result & 0xFF;
    uint32_t g = (result >> 8) & 0xFF;
    uint32_t r = (result >> 16) & 0xFF;
    uint16_t res = ((b >> 3) & 0x001F) | ((g << 3) & 0x07E0) | ((r << 8) & 0xF800);
    return res;
}


static void bmpDraw(char const *const filename, char const *const convert)
{
    FILE *bmpFile;

    fprintf(stderr, "Loading image %s\n", filename);

    // Open requested file on SD card
    if ((bmpFile = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "Can't open: %s\n", strerror(errno));
        exit(1);
    }

    // Parse BMP header
    int const bmpSignature = read16(bmpFile);
    if(bmpSignature != 0x4D42) { // BMP signature
        fprintf(stderr, "BMP signature read %x. Can't continue\n", bmpSignature);
        exit(1);
    }

    fprintf(stderr, "File size: %d\n", read32(bmpFile));
    read32(bmpFile); // Read & ignore creator bytes
    int const bmpImageoffset = read32(bmpFile); // Start of image data
    fprintf(stderr, "Image Offset: %d\n", bmpImageoffset);
    // Read DIB header
    fprintf(stderr, "Header size: %d\n", read32(bmpFile));
    int w = read32(bmpFile);
    int h = read32(bmpFile);
    fprintf(stderr, "Image geometry: %dx%d\n", w, h);
    int const bmpPlanes = read16(bmpFile);
    if(bmpPlanes != 1) { // # planes -- must be '1'
        fprintf(stderr, "BMP planes %d. Can't continue\n", bmpPlanes);
        exit(1);
    }

    int const bmpDepth = read16(bmpFile);
    int const bmpCompr = read32(bmpFile);
    fprintf(stderr, "Bit Depth: %d\n", bmpDepth);
    fprintf(stderr, "Compressed: %s\n", bmpCompr ? "yes" : "no");
    if (bmpDepth != 24  ||  bmpCompr != 0) {
        fprintf(stderr, "Must be an uncompressed 24-bit bmp image. F.ex. use ImageMagick to convert:\nconvert in.bmp -define bmp:subtype=RGB565 -compress none out.bmp\n");
        exit(1);
    }

    // If bmpHeight is negative, image is in top-down order.
    // This is not canon but has been observed in the wild.
    bool flip = true;
    if(h < 0) {
        h = -h;
        flip = false;
    }

    uint16_t *const pictureData = (uint16_t *) malloc(sizeof(pictureData[0]) * w * h);
    uint16_t *p = pictureData;

    fprintf(stderr, "Reading %d rows with %d columns\n", h, w);
    fseek(bmpFile, bmpImageoffset, SEEK_SET);

    unsigned int const zeroFillBytes = (4 - (w * 3 % 4)) & 3;  // Rows are aligned to 4 bytes
    char extra[3];
    for (int row=0; row<h; row++) {
        if (flip) {
            p = pictureData + (h - row - 1) * w;
        }

        for (int col=0; col<w; col++) {
            *p++ = readPixel(bmpFile);
        }

        if (fread(extra, 1, zeroFillBytes, bmpFile) != zeroFillBytes) {
            fprintf(stderr, "Read error: %s\n", strerror(errno));
            exit(1);
        }
    }

    fprintf(stderr, "Loaded %s\n", filename);

    if (!strcmp(convert, "arduino1bit")) {
        toArduino1bit(pictureData, w, h, filename);
    }
    else if (!strcmp(convert, "arduino2bit")) {
        toArduinoPalette(pictureData, w, h, 2, filename);
    }
    else if (!strcmp(convert, "arduino4bit")) {
        toArduinoPalette(pictureData, w, h, 4, filename);
    }
    else if (!strcmp(convert, "arduino16bit")) {
        toArduino16bit(pictureData, w, h, filename);
    }
    else if (!strcmp(convert, "ascii")) {
        toAscii(pictureData, w, h);
    }

    free(pictureData);
    fclose(bmpFile);
}

int main(int argc, char **argv)
{
    char const *to = NULL;
    char const *src = NULL;

    static struct option const longOpts[] = {
        {"to", required_argument, 0, 0},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    bool cont = true;
    while (cont) {
        int optIdx = 0;
        char const c = getopt_long(argc, argv, "h", longOpts, &optIdx);
        switch (c) {
        case 0:
            fprintf(stderr, "Got %s\n", longOpts[optIdx].name);
            if (!strcmp(longOpts[optIdx].name, "to")) {
                if (!optarg) {
                    fprintf(stderr, "Conversion format required: arduino or ascii\n");
                    exit(1);
                }
                to = optarg;
            }
            else {
                fprintf(stderr, "Wtf? Internal error\n");
                exit(1);
            }
            break;

        case 'h':
        case '?':
            fprintf(stderr, "Usage: bmp2teatimer --to=arduino1bit|arduino2bit|arduino4bit|arduino16bit|ascii BMPFILE\n");
            exit(1);
            break;

        default:
            cont = false;
            break;
        }
    }

    if (optind < argc) {
        src = argv[optind];
    }

    fprintf(stderr, "remaining: %s\n", optarg);
    if (!src) {
        fprintf(stderr, "Source file required\n");
        exit(1);
    }
    if (!to  ||  (strcmp(to, "ascii")  &&
        strcmp(to, "arduino1bit")  &&
        strcmp(to, "arduino2bit")  &&
        strcmp(to, "arduino4bit")  &&
        strcmp(to, "arduino16bit"))) 
    {
        fprintf(stderr, "Conversion format required: arduino1bit, arduino2bit, arduino4bit, arduino16bit or ascii\n");
        exit(1);
    }

    bmpDraw(src, to);

    return 0;
}
