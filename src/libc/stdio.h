// Standard input/output implementation for blankos/libc header
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>
#include <stdbool.h>

#define FB_GREEN      	  2
#define FB_DARK_GREY  	  8

#define FB_CMD_PORT       0x3D4
#define FB_DATA_PORT      0x3D5
#define FB_HIGH_BYTE_CMD  14
#define FB_LOW_BYTE_CMD   15

#define CURSOR_WIDTH  	  8
#define CURSOR_HEIGHT     16

void draw_cursor(uint32_t color);
void erase_cursor();

void move_cursor(int x, int y);
void putchar(unsigned short int c, int x, int y, uint32_t fg, uint32_t bg);
void puts(const char* str);
void clear(void);
void colorputs(const char* str, uint32_t fg, uint32_t bg);
void putcolor(int x, int y, unsigned int color);
char getchar(int x, int y);
unsigned int getcolor(int x, int y);
void putc(char c);
void colorputc(char c, uint32_t fg, uint32_t bg);
void colorprintf(uint32_t fg, uint32_t bg, const char* fmt, ...);
int* colorprintf_number(int* argp, int length, bool sign, int radix, int width, char pad_char, uint32_t fg, uint32_t bg);

#define PRINTF_STATE_START 			0
#define PRINTF_STATE_LENGTH 		1
#define PRINTF_STATE_SHORT 			2
#define PRINTF_STATE_LONG 			3
#define PRINTF_STATE_SPEC 			4
#define PRINTF_STATE_WIDTH 			5

#define PRINTF_LENGTH_START 		0
#define PRINTF_LENGTH_SHORT_SHORT 	1
#define PRINTF_LENGTH_SHORT 		2
#define PRINTF_LENGTH_LONG 			3
#define PRINTF_LENGTH_LONG_LONG 	4

void printf(const char* fmt, ...);
int* printf_number(int* argp, int length, bool sign, int radix, int width, char pad_char);
int getch();
void get_input(char *buffer, int size);
void dtostrf(double val, char *buffer, int precision);

enum Colors
{
	// AARRGGBB?
	white       = 0xFFFFFFFF,
	black       = 0x00000000,
	red         = 0x00FF0000,
	green       = 0x0000FF00,
	blue        = 0x000000FF,
	yellow      = 0x00FFFF00,
	cyan   	    = 0x0000FFFF,
    	magenta     = 0x00FF00FF,
    	orange      = 0x00FFA500,
    	purple      = 0x00800080,
    	brown       = 0x00A52A2A,
    	gray        = 0x00808080,
    	pink        = 0x00FFC0CB,
    	lime        = 0x00BFFF00,
    	navy        = 0x00000080,
    	teal        = 0x00008080,
    	maroon      = 0x00800000,
    	olive       = 0x00808000,
    	silver      = 0x00C0C0C0,
    	gold        = 0x00FFD700,
    	indigo      = 0x004B0082,
    	violet      = 0x00EE82EE,
    	coral       = 0x00FF7F50,
    	turquoise   = 0x0040E0D0,
    	salmon      = 0x00FA8072,
    	chocolate   = 0x00D2691E,
    	khaki       = 0x00F0E68C,
    	lavender    = 0x00E6E6FA,
    	beige       = 0x00F5F5DC
};

int get_cursor_x();
int get_cursor_y();

#endif
