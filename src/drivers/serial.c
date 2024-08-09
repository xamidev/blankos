#include "../kernel/io.h"
#include "serial.h"
#include "../libc/stdio.h"

int init_serial()
{
  outb(PORT+1, 0x00);
  outb(PORT+3, 0x80);
  outb(PORT+0, 0x03);
  outb(PORT+1, 0x00);

  outb(PORT+3, 0x03);
  outb(PORT+2, 0xC7);
  outb(PORT+4, 0x0B);
  outb(PORT+4, 0x1E);
  outb(PORT+0, 0xAE);

  if (inb(PORT+0) != 0xAE) {
    return 1;
  }

  outb(PORT+4, 0x0F);
  return 0;
}

int is_transmit_empty()
{
  return inb(PORT+5) & 0x20;
}

void write_serial(const char a)
{
  while (is_transmit_empty() == 0);
  outb(PORT, a);
}

void serial_puts(const char* str)
{
  unsigned int i = 0;
  write_serial(str[0]); // Transmit first byte 2 times
  while (*str++)
  {
    write_serial(str[i]);
  }
}

void log(const char* str, const int errlevel)
{
  switch (errlevel)
  {
    case 0:
      serial_puts("[ERROR] ");
      break;
    case 1:
      serial_puts("[WARNING] ");
      break;
    case 2:
      serial_puts("[INFO] ");
      break;
    case 3:
      serial_puts("[DEBUG] ");
      break;
  }
  serial_puts(str);
}

const char serial_charset[] = "0123456789abcdef";

int* serial_printf_number(int* argp, int length, bool sign, int radix)
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
    buffer[pos++] = serial_charset[rem];
  } while (number > 0);

  if (sign && number_sign < 0)
  {
    buffer[pos++] = '-';
  }

  while (--pos >= 0)
  {
	  write_serial(buffer[pos]);
  }

  return argp;
}
void serial_printf(int errlevel, const char* fmt, ...)
{
  switch (errlevel)
  {
    case 0:
      serial_puts("[ERROR] ");
      break;
    case 1:
      serial_puts("[WARNING] ");
      break;
    case 2:
      serial_puts("[INFO] ");
      break;
    case 3:
      serial_puts("[DEBUG] ");
      break;
  }

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
          write_serial(*fmt);
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
            serial_puts(*(const char **)argp);
            argp++;
            break;
          case 's':
            serial_puts(*(const char **)argp);
            argp++;
            break;
          case '%':
            putc('%');
            break;
          case 'd':
          case 'i':
            radix = 10;
            sign = true;
            argp = serial_printf_number(argp, length, sign, radix);
            break;
          case 'u':
            radix = 10;
            sign = false;
            argp = serial_printf_number(argp, length, sign, radix);
            break;
          case 'X':
          case 'x':
          case 'p':
            radix = 16;
            sign = false;
            argp = serial_printf_number(argp, length, sign, radix);
            break;
          case 'o':
            radix = 8;
            sign = false;
            argp = serial_printf_number(argp, length, sign, radix);
            break;
          case 'f': {
            // Handle floating-point numbers
            double* dargp = (double*)argp;
            double d = *(double*)dargp;
            char buffer[64];
            dtostrf(d, buffer, 6); // Default precision: 6
            serial_puts(buffer);
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
  serial_puts("\n");
}

