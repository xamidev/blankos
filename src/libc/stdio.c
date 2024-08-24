// Standard input/output implementation for blankos/libc
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "../kernel/io.h"
#include "stdio.h"
#include "string.h"
#include <stdint.h>
#include "../kernel/system.h"
#include "../drivers/framebuffer.h"
#include "../drivers/serial.h"

extern uint32_t* framebuffer;
extern uint32_t VGA_WIDTH; 
extern uint32_t VGA_HEIGHT;
unsigned int VGA_X = 0, VGA_Y = 0;
extern int scanline;

void draw_cursor(uint32_t color)
{
	for (int y=12; y<CURSOR_HEIGHT; y++)
	{
		for (int x=0; x<CURSOR_WIDTH; x++)
		{
			putpixel(framebuffer, scanline, 32, VGA_X * CURSOR_WIDTH + x, VGA_Y * CURSOR_HEIGHT + y, color);
		}
	}
}

void erase_cursor()
{
	draw_cursor(black);
}

void move_cursor(int x, int y)
{
	erase_cursor();
	VGA_X = x;
	VGA_Y = y;
	draw_cursor(white);
}

// stdio wrapper for draw_char in graphics mode
void putchar(unsigned short int c, int x, int y, uint32_t fg, uint32_t bg)
{
	draw_char(c, x, y, fg, bg);
}

void clear(void)
{
  for (unsigned int y=0; y<VGA_HEIGHT; y++)
  {
    for (unsigned int x=0; x<VGA_WIDTH; x++)
    {
      putchar(' ', x, y, black, black);
    }
  }
  move_cursor(0, 0);
}

void putc(char c)
{
  erase_cursor();
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
      putchar(' ', VGA_X, VGA_Y, white, black);
      break;
    default:
      putchar(c, VGA_X, VGA_Y, white, black);
      VGA_X++;
      break;
  }

  if (VGA_X >= VGA_WIDTH)
  {
    VGA_Y++;
    VGA_X = 0;
  }
  if (VGA_Y >= VGA_HEIGHT) 
  {
	serial_printf(3, "VGA_Y=%d, VGA_HEIGHT=%d: Scrolling...\r", VGA_Y, VGA_HEIGHT);
	scroll();
  	VGA_Y = VGA_HEIGHT - 1;
  }	  

  move_cursor(VGA_X, VGA_Y);
}

void colorputc(char c, uint32_t fg, uint32_t bg)
{
  erase_cursor();
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
      putchar(c, VGA_X, VGA_Y, fg, bg);
      VGA_X++;
      break;
  }

  if (VGA_X >= VGA_WIDTH)
  {
    VGA_Y++;
    VGA_X = 0;
  }

  if (VGA_Y >= VGA_HEIGHT) 
  {
	serial_printf(3, "VGA_Y=%d, VGA_HEIGHT=%d: Scrolling...\r", VGA_Y, VGA_HEIGHT);
	scroll();
  	VGA_Y = VGA_HEIGHT - 1;
  }	

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

void colorputs(const char* str, uint32_t fg, uint32_t bg)
{
  while (*str)
  {
    colorputc(*str, fg, bg);
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
    int* argp = (int*)&fmt;
    int state = PRINTF_STATE_START;
    int length = PRINTF_LENGTH_START;
    int radix = 10;
    bool sign = false;
    int width = 0;
    char pad_char = ' ';

    argp++;
    while (*fmt)
    {
        switch (state)
        {
        case PRINTF_STATE_START:
            if (*fmt == '%')
            {
                state = PRINTF_STATE_LENGTH;
                width = 0;
                pad_char = ' ';
            }
            else
            {
                putc(*fmt);
            }
            break;

        case PRINTF_STATE_LENGTH:
            if (*fmt == '0')
            {
                pad_char = '0';
                state = PRINTF_STATE_WIDTH;
            }
            else if (*fmt >= '1' && *fmt <= '9')
            {
                width = *fmt - '0';
                state = PRINTF_STATE_WIDTH;
            }
            else if (*fmt == 'h')
            {
                length = PRINTF_LENGTH_SHORT;
                state = PRINTF_STATE_SHORT;
            }
            else if (*fmt == 'l')
            {
                length = PRINTF_LENGTH_LONG;
                state = PRINTF_STATE_LONG;
            }
            else
            {
                goto PRINTF_STATE_SPEC_;
            }
            break;

        case PRINTF_STATE_WIDTH:
            if (*fmt >= '0' && *fmt <= '9')
            {
                width = width * 10 + (*fmt - '0');
            }
            else
            {
                goto PRINTF_STATE_SPEC_;
            }
            break;

        case PRINTF_STATE_SHORT:
            if (*fmt == 'h')
            {
                length = PRINTF_LENGTH_SHORT_SHORT;
                state = PRINTF_STATE_SPEC;
            }
            else
            {
                goto PRINTF_STATE_SPEC_;
            }
            break;

        case PRINTF_STATE_LONG:
            if (*fmt == 'l')
            {
                length = PRINTF_LENGTH_LONG_LONG;
                state = PRINTF_STATE_SPEC;
            }
            else
            {
                goto PRINTF_STATE_SPEC_;
            }
            break;

        case PRINTF_STATE_SPEC:
        PRINTF_STATE_SPEC_:
            switch (*fmt)
            {
            case 'c':
                putc((char)*argp);
                argp++;
                break;
            case 's':
                puts(*(const char**)argp);
                argp++;
                break;
            case '%':
                putc('%');
                break;
            case 'd':
            case 'i':
                radix = 10;
                sign = true;
                argp = printf_number(argp, length, sign, radix, width, pad_char);
                break;
            case 'u':
                radix = 10;
                sign = false;
                argp = printf_number(argp, length, sign, radix, width, pad_char);
                break;
            case 'X':
            case 'x':
            case 'p':
                radix = 16;
                sign = false;
                argp = printf_number(argp, length, sign, radix, width, pad_char);
                break;
            case 'o':
                radix = 8;
                sign = false;
                argp = printf_number(argp, length, sign, radix, width, pad_char);
                break;
            case 'f': {
                double* dargp = (double*)argp;
                double d = *(double*)dargp;
                char buffer[64];
                dtostrf(d, buffer, 6);
                puts(buffer);
                argp += 2;
                break;
            }
            default:
                break;
            }
            state = PRINTF_STATE_START;
            length = PRINTF_LENGTH_START;
            radix = 10;
            sign = false;
            width = 0;
            pad_char = ' ';
            break;
        }
        fmt++;
    }
}

const char charset[] = "0123456789abcdef";

int* printf_number(int* argp, int length, bool sign, int radix, int width, char pad_char)
{
    char buffer[32];
    unsigned long long number;
    int number_sign = 1;
    int pos = 0;

    switch (length)
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
            number = (unsigned long long)n;
        }
        else
        {
            number = *(unsigned int*)argp;
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
            number = (unsigned long long)n;
        }
        else
        {
            number = *(unsigned long int*)argp;
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
            number = (unsigned long long)n;
        }
        else
        {
            number = *(unsigned long long int*)argp;
        }
        argp += 4;
        break;
    }

    do
    {
        uint32_t rem;
        x86_div64_32(number, radix, &number, &rem);
        buffer[pos++] = charset[rem];
    } while (number > 0);

    if (sign && number_sign < 0)
    {
        buffer[pos++] = '-';
    }

    int padding = width - pos;

    while (padding-- > 0)
    {
        putc(pad_char);
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
