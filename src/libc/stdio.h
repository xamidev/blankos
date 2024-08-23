#ifndef INCLUDE_STDIO_H
#define INCLUDE_STDIO_H

#include "stdint.h"

#define FB_GREEN      2
#define FB_DARK_GREY  8

#define FB_CMD_PORT       0x3D4
#define FB_DATA_PORT      0x3D5
#define FB_HIGH_BYTE_CMD  14
#define FB_LOW_BYTE_CMD   15


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

#define PRINTF_STATE_START 		0
#define PRINTF_STATE_LENGTH 		1
#define PRINTF_STATE_SHORT 		2
#define PRINTF_STATE_LONG 		3
#define PRINTF_STATE_SPEC 		4
#define PRINTF_STATE_WIDTH 		5

#define PRINTF_LENGTH_START 		0
#define PRINTF_LENGTH_SHORT_SHORT 	1
#define PRINTF_LENGTH_SHORT 		2
#define PRINTF_LENGTH_LONG 		3
#define PRINTF_LENGTH_LONG_LONG 	4

void printf(const char* fmt, ...);
int* printf_number(int* argp, int length, bool sign, int radix, int width, char pad_char);
int getch();
void get_input(char *buffer, int size);

void dtostrf(double val, char *buffer, int precision);

enum Colors
{
	// AARRGGBB?
	white  = 0xFFFFFFFF,
	black  = 0x00000000,
	red    = 0x00FF0000,
	green  = 0x0000FF00,
	blue   = 0x000000FF,
	yellow = 0x00FFFF00,
};

#endif
