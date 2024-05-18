#include "io.h"
#include "stdio.h"

char* fb = (char *) 0x000B8000;

void move_cursor(unsigned short pos)
{
  outb(FB_CMD_PORT, FB_HIGH_BYTE_CMD);
  outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
  outb(FB_CMD_PORT, FB_LOW_BYTE_CMD);
  outb(FB_DATA_PORT, pos & 0x00FF);
}

void putchar(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
  fb[i] = c;
  fb [i+1] = ((fg & 0x0F) << 4 | (bg & 0x0F));
}

int write(char *buf, unsigned int len)
{
  return 42;
}
