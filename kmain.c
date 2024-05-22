#include "stdio.h"
#include "serial.h"

int kmain(int retvalue)
{
  clear();
  puts("hello\nbrave\nnew\nworld");

  init_serial();
  serial_puts("Hello, brave new world. This is a message to let you know that the kernel has started.\n");
  serial_puts("This is a second message.\n");
  return retvalue;
}
