#include "io.h"
#include "serial.h"

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
