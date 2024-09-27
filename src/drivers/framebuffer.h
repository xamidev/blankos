// Framebuffer driver header
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

extern int scanline;
extern char _binary_include_fonts_UniCyrExt_8x16_psf_start;
uint16_t* unicode;

#define PIXEL uint32_t

#define PSF1_FONT_MAGIC 0x0436

typedef struct {
    uint16_t magic; // Magic bytes for identification.
    uint8_t fontMode; // PSF font mode.
    uint8_t characterSize; // PSF character size.
} PSF1_Header;

#define PSF_FONT_MAGIC 0x864ab572

typedef struct {
    uint32_t magic;         /* magic bytes to identify PSF */
    uint32_t version;       /* zero */
    uint32_t headersize;    /* offset of bitmaps in file, 32 */
    uint32_t flags;         /* 0 if there's no unicode table */
    uint32_t numglyph;      /* number of glyphs */
    uint32_t bytesperglyph; /* size of each glyph */
    uint32_t height;        /* height in pixels */
    uint32_t width;         /* width in pixels */
} PSF_font;

void putpixel(uint32_t* fb, int pitch, int bpp, int x, int y, uint32_t color); 
void draw_char(unsigned short int c, int cx, int cy, uint32_t fg, uint32_t bg);
void scroll();

#endif
