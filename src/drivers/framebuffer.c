// Framebuffer driver
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include <stdint.h>
#include "framebuffer.h"
#include "serial.h"
#include "../kernel/system.h"

extern char* framebuffer;

void putpixel(uint32_t* fb, int pitch, int bpp, int x, int y, uint32_t color)
{
	if (bpp == 32) {
		uint32_t* pixel_addr = (uint32_t*)((uint8_t*)fb + y * pitch + x *(bpp / 8));
		*pixel_addr = color;
	}
}

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
		(cx * (font->width) * sizeof(PIXEL));

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

void scroll()
{
	serial_printf(3, "Scrolling...\r");
	uint32_t bg_color = 0x00000000;
	PSF_font *font = (PSF_font*)&_binary_include_fonts_UniCyr_8x16_psf_start;
	
	int line_size = font->height * scanline;
	int framebuffer_size = scanline * font->height * (1080/font->height);

	// Erasing first line
	for (uint32_t y=0; y<font->height; y++)
	{
		for (uint32_t x=0; x<scanline/sizeof(PIXEL); x++)
		{
			*((PIXEL*)(framebuffer + y * scanline + x * sizeof(PIXEL))) = bg_color;
		}
	}

	// Moving all lines up by 1 line
	for (int y=1; y<(framebuffer_size/line_size); y++)
	{
		void* src = framebuffer + y*line_size;
		void* dst = framebuffer + (y-1)*line_size;
		memmove(dst, src, line_size);
	}

	// Erasing last line
	int last_line_start = (framebuffer_size/line_size-1) * line_size;
	for (uint32_t y=0; y<font->height; y++)
	{
		for (uint32_t x=0; x<scanline/sizeof(PIXEL); x++)
		{
			*((PIXEL*)(framebuffer + last_line_start + y * scanline + x * sizeof(PIXEL))) = bg_color;
		}
	}
}

