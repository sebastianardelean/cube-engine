#pragma once


struct Color
{
    Color(){
	red = 0xFFu;
	green = 0xFFu;
	blue = 0xFFu;
	alpha = 0xFFu;
    }
    
    Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a=0xFFu) {
	red = r;
	green = g;
	blue = b;
	alpha = a;
    }
     
    Color(uint32_t p) {
	red = (uint8_t)(p>>24);
	green = (uint8_t)(p>>16);
	blue = (uint8_t)(p>>8);
	alpha = (uint8_t)p;

    }
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    bool operator == (const Color& c) const {
	return (
		red==c.red && 
		green == c.green && 
		blue == c.blue && 
		alpha==c.alpha
		);
    }
    bool operator != (const Color& c) const {
	return !(*this == c);
    }
    [[nodiscard]]uint32_t GetColor() const {
	return ((red<<24) | green<<16 | blue<<8 | alpha);
    }
};

struct Pixel
{
    Pixel() {
	color = Color();
	posX = 0;
	posY = 0;
    }

    Pixel(Color c, int32_t x, int32_t y):color(c),posX(x),posY(y) {
    }
    
    bool operator==(const Pixel& p) const {
	return (color == p.color && posX == p.posX && posY==p.posY);
    }

    bool operator!=(const Pixel& p) const {
	return !(*this == p);
    }

    Color color;
    int32_t posX;
    int32_t posY;

};

static const Color GREY(192, 192, 192), DARK_GREY(128, 128, 128), VERY_DARK_GREY(64, 64, 64),
RED(255, 0, 0), DARK_RED(128, 0, 0), VERY_DARK_RED(64, 0, 0),
YELLOW(255, 255, 0), DARK_YELLOW(128, 128, 0), VERY_DARK_YELLOW(64, 64, 0),
GREEN(0, 255, 0), DARK_GREEN(0, 128, 0), VERY_DARK_GREEN(0, 64, 0),
CYAN(0, 255, 255), DARK_CYAN(0, 128, 128), VERY_DARK_CYAN(0, 64, 64),
BLUE(0, 0, 255), DARK_BLUE(0, 0, 128), VERY_DARK_BLUE(0, 0, 64),
MAGENTA(255, 0, 255), DARK_MAGENTA(128, 0, 128), VERY_DARK_MAGENTA(64, 0, 64),
WHITE(255, 255, 255), BLACK(0, 0, 0), BLANK(0, 0, 0, 0);

