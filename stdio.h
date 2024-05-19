#ifndef INCLUDE_STDIO_H
#define INCLUDE_STDIO_H

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
void putcolor(int x, int y, int color);

#endif
