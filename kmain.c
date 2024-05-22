#include "stdio.h"
#include "serial.h"

int kmain(int retvalue)
{
  init_serial();
  log("serial connection established", 3);
  log("Kernel started", 2);

  clear();
  puts("hello\nbrave\nnew\nworld");

  return retvalue;
}
