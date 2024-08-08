#include "../kernel/io.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "../kernel/system.h"

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

void putcolor(int x, int y, unsigned int color)
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

char getchar(int x, int y)
{
  return fb[2*(y*VGA_WIDTH+x)];
}

unsigned int getcolor(int x, int y)
{
  return fb[2*(y*VGA_WIDTH+x)+1];
}

void scroll(int lines)
{
  if (lines <= 0 || (unsigned int)lines >= VGA_HEIGHT) return;

  for (unsigned int y = 0; y < VGA_HEIGHT-lines; y++)
  {
    for (unsigned int x = 0; x < VGA_WIDTH; x++)
    {
      putchar(x, y, getchar(x, y+lines));
      putcolor(x, y, getcolor(x, y+lines));
    }
  }

  for (unsigned int y = VGA_HEIGHT-lines; y<VGA_HEIGHT; y++)
  {
    for (unsigned int x = 0; x < VGA_WIDTH; x++)
    {
      putchar(x, y, ' ');
      putcolor(x, y, COLOR);
    }
  }

  VGA_Y -= lines;
  if ((int)VGA_Y < 0) {
	  VGA_Y = 0;
  }
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
    case '\t':
      VGA_X += 4;
      if (VGA_X >= VGA_WIDTH) {
	      VGA_X -= VGA_WIDTH;
	      VGA_Y++;
      }
      break;
    case '\b':
      if (VGA_X > 0)
      {
	      VGA_X--;
      }
      else if (VGA_Y > 0) {
	      VGA_Y--;
	      VGA_X = VGA_WIDTH-1;
      }
      putchar(VGA_X, VGA_Y, ' ');
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
  if (VGA_Y >= VGA_HEIGHT) scroll(1);

  move_cursor(VGA_X, VGA_Y);
}

void colorputc(char c, unsigned int color)
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
    case '\t':
      VGA_X += 4;
      break;
    default:
      putchar(VGA_X, VGA_Y, c);
      putcolor(VGA_X, VGA_Y, color);
      VGA_X++;
      break;
  }

  if (VGA_X >= VGA_WIDTH)
  {
    VGA_Y++;
    VGA_X = 0;
  }
  if (VGA_Y >= VGA_HEIGHT) scroll(1);
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

void colorputs(const char* str, unsigned int color)
{
  while (*str)
  {
    colorputc(*str, color);
    str++;
  }
}

// double to string for printf
void dtostrf(double val, char *buffer, int precision)
{
  int whole_part = (int)val;
  double fractional_part = val - whole_part;
  if (fractional_part < 0) fractional_part = -fractional_part;

  if (whole_part == 0)
  {
    *buffer++ = '0';
  }
  else
  {
    if (whole_part < 0)
    {
      *buffer++ = '-';
      whole_part = -whole_part;
    }
    char temp[32];
    int pos = 0;

    while (whole_part > 0)
    {
      temp[pos++] = '0' + (whole_part % 10);
      whole_part /= 10;
    }
    while (pos > 0)
    {
      *buffer++ = temp[--pos];
    }
  }

  *buffer++ = '.';
  for (int i = 0; i < precision; i++)
  {
    fractional_part *= 10;
    int digit = (int)fractional_part;
    *buffer++ = '0' + digit;
    fractional_part -= digit;
  }
  *buffer = '\0';
}

void printf(const char* fmt, ...)
{
  int* argp = (int*) &fmt;
  int state = PRINTF_STATE_START;
  int length = PRINTF_LENGTH_START;
  int radix = 10;
  bool sign = false;

  argp++;
  while (*fmt)
  {
    switch(state) {
      case PRINTF_STATE_START:
        if (*fmt == '%')
        {
          state = PRINTF_STATE_LENGTH;
        }
        else {
          putc(*fmt);
        }
        break;
      case PRINTF_STATE_LENGTH:
        if (*fmt == 'h')
        {
          length = PRINTF_LENGTH_SHORT;
          state = PRINTF_STATE_SHORT;
        }
        else if (*fmt == 'l')
        {
          length = PRINTF_LENGTH_LONG;
          state = PRINTF_STATE_LONG;
        }
        else {
          goto PRINTF_STATE_SPEC_;
        }
        break;
      case PRINTF_STATE_SHORT:
        if (*fmt == 'h')
        {
          length = PRINTF_LENGTH_SHORT_SHORT;
          state = PRINTF_STATE_SPEC;
        }
        else {
          goto PRINTF_STATE_SPEC_;
        }
        break;
      case PRINTF_STATE_LONG:
        if (*fmt == 'l')
        {
          length = PRINTF_LENGTH_LONG_LONG;
          state = PRINTF_STATE_SPEC;
        }
        else {
          goto PRINTF_STATE_SPEC_;
        }
        break;
      case PRINTF_STATE_SPEC:
        PRINTF_STATE_SPEC_:
        switch(*fmt)
        {
          case 'c':
            putc((char)*argp);
            argp++;
            break;
          case 's':
            puts(*(const char **)argp);
            argp++;
            break;
          case '%':
            putc('%');
            break;
          case 'd':
          case 'i':
            radix = 10;
            sign = true;
            argp = printf_number(argp, length, sign, radix);
            break;
          case 'u':
            radix = 10;
            sign = false;
            argp = printf_number(argp, length, sign, radix);
            break;
          case 'X':
          case 'x':
          case 'p':
            radix = 16;
            sign = false;
            argp = printf_number(argp, length, sign, radix);
            break;
          case 'o':
            radix = 8;
            sign = false;
            argp = printf_number(argp, length, sign, radix);
            break;
          case 'f': {
            // Handle floating-point numbers
            double* dargp = (double*)argp;
            double d = *(double*)dargp;
            char buffer[64];
            dtostrf(d, buffer, 6); // Default precision: 6
            puts(buffer);
            argp += 2; // Incrementing by 2 to move past the double argument
            break;
          }
          default:
            break;
        }
        state = PRINTF_STATE_START;
        length = PRINTF_LENGTH_START;
        radix = 10;
        sign = false;
        break;
    }
    fmt++;
  }
}

const char charset[] = "0123456789abcdef";

int* printf_number(int* argp, int length, bool sign, int radix)
{
  char buffer[32];
  unsigned long long number;
  int number_sign = 1;
  int pos = 0;

  switch(length)
  {
    case PRINTF_LENGTH_SHORT_SHORT:
    case PRINTF_LENGTH_SHORT:
    case PRINTF_LENGTH_START:
      if (sign)
      {
        int n = *argp;
        if (n < 0)
        {
          n = -n;
          number_sign = -1;
        }
        number = (unsigned long long) n;
      }
      else {
        number = *(unsigned int*) argp;
      }
      argp++;
      break;
    case PRINTF_LENGTH_LONG:
      if (sign)
      {
        long int n = *(long int*)argp;
        if (n < 0)
        {
          n = -n;
          number_sign = -1;
        }
        number = (unsigned long long) n;
      }
      else {
        number = *(unsigned long int*) argp;
      }
      argp += 2;
      break;
    case PRINTF_LENGTH_LONG_LONG:
      if (sign)
      {
        long long int n = *(long long int*)argp;
        if (n < 0)
        {
          n = -n;
          number_sign = -1;
        }
        number = (unsigned long long) n;
      }
      else {
        number = *(unsigned long long int*) argp;
      }
      argp += 4;
      break;
  }

  do {
    uint32_t rem;
    x86_div64_32(number, radix, &number, &rem);
    buffer[pos++] = charset[rem];
  } while (number > 0);

  if (sign && number_sign < 0)
  {
    buffer[pos++] = '-';
  }

  while (--pos >= 0)
  {
    putc(buffer[pos]);
  }

  return argp;
}

int getch()
{
	return keyboard_getchar();
}

void get_input(char *buffer, int size) {
	int index = 0;
	char c;

	while (index < size-1)
	{
		c = getch();
		if (c == '\n') {
			break;
		} else if (c == '\b') {
			if (index > 0) {
				index--;
				putc('\b');
				putc(' ');
				putc('\b');
			}
		} else {
			buffer[index++] = c;
			putc(c);
		}
	}
	buffer[index] = '\0';
}
