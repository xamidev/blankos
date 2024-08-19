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

void draw_char(uint32_t* fb, int pitch, int bpp, int x, int y, char c, uint32_t fg_color, uint32_t bg_color)
{
	const unsigned char* glyph = font[(unsigned char)c];
	//serial_printf(3, "glyph= %c\r\n", glyph);
	int glyph_width = 16;
	int glyph_height = 32;

	for (int py=0; py < glyph_height; py++)
	{
		for (int px=0; px < glyph_width; px++)
		{
			if (glyph[py] & (0x80 >> px)) {
				putpixel(fb, pitch, bpp, x+px, y+py, fg_color);
			} else {
				putpixel(fb, pitch, bpp, x+px, y+py, bg_color);
			}
		}	
	}
}
