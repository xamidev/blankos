#include "stdio.h"
#include "serial.h"

int kmain(int retvalue)
{
  clear();
  puts("hello\nbrave\nnew\nworld");
  serial_write("hello", 1);
  return retvalue;
}
