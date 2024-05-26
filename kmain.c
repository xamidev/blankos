#include "stdio.h"
#include "serial.h"

int kmain(int retvalue)
{
  init_serial();
  log("serial connection established", 3);
  log("Kernel started", 2);

  clear();
  printf("Formatted: %% %c %s %d\n", 'f', "Hello", 77);
  return retvalue;
}
