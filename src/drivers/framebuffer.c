#include "../libc/stdint.h"
#include "framebuffer.h"
#include "serial.h"

//extern uint32_t *g_framebuffer;

void putpixel(uint32_t* fb, int pitch, int bpp, int x, int y, uint32_t color) // framebuffer pointer, x, y, color
{
	if (bpp == 32) {
		uint32_t* pixel_addr = (uint32_t*)((uint8_t*)fb + y * pitch + x *(bpp / 8));
		*pixel_addr = color;
	}
}

extern char* framebuffer;
extern int scanline;
extern char _binary_include_fonts_UniCyr_8x16_psf_start;
uint16_t* unicode;

#define PIXEL uint32_t

// Character, cursor X, cursor Y, foreground, background
void draw_char(unsigned short int c, int cx, int cy, uint32_t fg, uint32_t bg)
{
	PSF_font *font = (PSF_font*)&_binary_include_fonts_UniCyr_8x16_psf_start;
	int bytesperline=(font->width+7)/8;
	if (unicode != NULL) {
		c = unicode[c];
	}

	unsigned char* glyph = (unsigned char*)&_binary_include_fonts_UniCyr_8x16_psf_start + font->headersize + (c>0&&c<font->numglyph?c:0)*font->bytesperglyph;

	int offs =
		(cy * font->height * scanline) +
		(cx * (font->width + 1) * sizeof(PIXEL));

	unsigned int x, y;
	int line, mask;

	for (y=0; y<font->height; y++)
	{
		line=offs;
		mask=1<<(font->width-1);

		for (x=0; x<font->width; x++)
		{
			*((PIXEL*)(framebuffer + line)) = *((unsigned int*)glyph) & mask ? fg : bg;
			mask >>= 1;
			line += sizeof(PIXEL);
		}

		glyph += bytesperline;
		offs += scanline;
	}
}
