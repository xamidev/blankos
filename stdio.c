#include "io.h"
#include "stdio.h"
#include "string.h"

char* fb = (char *) 0x000B8000;
const unsigned VGA_WIDTH = 80;
const unsigned VGA_HEIGHT = 25;
const unsigned int COLOR = 0x7;
unsigned int VGA_X = 0, VGA_Y = 0;

void move_cursor(int x, int y)
{
  unsigned short pos = y*VGA_WIDTH+x; 

  outb(FB_CMD_PORT, FB_HIGH_BYTE_CMD);
  outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
  outb(FB_CMD_PORT, FB_LOW_BYTE_CMD);
  outb(FB_DATA_PORT, pos & 0x00FF);
}

void putchar(int x, int y, char c) 
{
  fb[2*(y*VGA_WIDTH+x)] = c;
}

void putcolor(int x, int y, int color)
{
  fb[2*(y*VGA_WIDTH+x)+1] = color;
}

void clear(void)
{
  for (unsigned int y=0; y<VGA_HEIGHT; y++)
  {
    for (unsigned int x=0; x<VGA_WIDTH; x++)
    {
      putchar(x, y, '\0');
      putcolor(x, y, COLOR);
    }
  }
  VGA_X = 0;
  VGA_Y = 0;
  move_cursor(VGA_X, VGA_Y);
}

void putc(char c)
{
  switch(c)
  {
    case '\n':
      VGA_X = 0;
      VGA_Y++;
      break;
    case '\r':
      VGA_X = 0;
      break;
    default:
      putchar(VGA_X, VGA_Y, c);
      VGA_X++;
      break;
  }

  if (VGA_X >= VGA_WIDTH)
  {
    VGA_Y++;
    VGA_X = 0;
  }
  //if (VGA_Y >= VGA_HEIGHT) scroll

  move_cursor(VGA_X, VGA_Y);
}

void puts(const char* str)
{
  while (*str)
  {
    putc(*str);
    str++;
  }
}





