#ifndef INCLUDE_STDIO_H
#define INCLUDE_STDIO_H

#include "stdint.h"

#define FB_GREEN      2
#define FB_DARK_GREY  8

#define FB_CMD_PORT       0x3D4
#define FB_DATA_PORT      0x3D5
#define FB_HIGH_BYTE_CMD  14
#define FB_LOW_BYTE_CMD   15

void move_cursor(int x, int y);
void putchar(int x, int y, char c);
void puts(const char* str);
void clear(void);
void putcolor(int x, int y, unsigned int color);
char getchar(int x, int y);
unsigned int getcolor(int x, int y);
void scroll(int lines);
void putc(char c);

#define PRINTF_STATE_START 0
#define PRINTF_STATE_LENGTH 1
#define PRINTF_STATE_SHORT 2
#define PRINTF_STATE_LONG 3
#define PRINTF_STATE_SPEC 4

#define PRINTF_LENGTH_START 0
#define PRINTF_LENGTH_SHORT_SHORT 1
#define PRINTF_LENGTH_SHORT 2
#define PRINTF_LENGTH_LONG 3
#define PRINTF_LENGTH_LONG_LONG 4

void printf(const char* fmt, ...);
int* printf_number(int* argp, int length, bool sign, int radix);

#endif
