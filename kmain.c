#include "stdio.h"
#include "serial.h"

int kmain(int retvalue)
{

  // serial testing

  init_serial();
  log("serial connection established", 3);
  log("Kernel started", 2);

  clear();

  // printf testing

  int age = 34;
  int problems = 124;
  char* name = "xamidev"; 
  
  printf("Hello %s, you are %d years old and have %d problems. wow %%\n", name, age, problems);
  
  long suchwow = 2934342;
  char character = 65;
  printf("such number %u\nsuch character %c", suchwow, character);
  
  printf("wow negative %d\n", -3742);
  printf("such hex %x %X\n", 0xcafe, 0xdeadbeef);
  
  printf("such pointer %p\n", (void*)0xcafe1234);
  
  return retvalue;
}
