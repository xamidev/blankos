#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H


extern const unsigned char font[512][64];
void putpixel(uint32_t* fb, int pitch, int bpp, int x, int y, uint32_t color); 
void draw_char(uint32_t* fb, int pitch, int bpp, int x, int y, char c, uint32_t fg_color, uint32_t bg_color);

#endif
