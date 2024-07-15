#include "stdio.h"
#include "serial.h"
#include "gdt.h"
#include "idt.h"
#include "system.h"

int kmain(int retvalue)
{
  
  init_serial();
  log("serial connection established", 3);
  gdt_install();
  log("initialized GDT entries", 2);
  idt_install();
  log("initialized IDT", 2);
  isr_install();
  log("initialized ISRs", 3);
 
  log("kernel started", 2);

  clear();

  // printf testing

  // TODO: Framebuffer upgrade: color output
  // TODO: Serial printf to dump registers on kernel panic
  // TODO: Fix scrolling bug (framebuffer driver)

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

  for (int i=0; i<10; i++)
  {
    colorputs("hello colorful world!!\n", i);
  }
  // Div by zero exception
  
  //printf("Lalala, what a beautiful day! %d", 4/0);

  return retvalue;
}
