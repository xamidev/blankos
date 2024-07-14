#include "stdio.h"
#include "serial.h"
#include "gdt.h"
#include "idt.h"
#include "system.h"

int kmain(int retvalue)
{
  
  gdt_install();
  idt_install();
  isr_install();

  // serial testing

  init_serial();
  
  log("serial connection established", 3);
  log("initialized GDT entries", 2);
  log("kernel started", 2);
  log("initialized IDT", 2);
  log("initialized ISRs", 3);

  clear();

  // printf testing

  // TODO: Framebuffer upgrade: color output

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
 
  // Div by zero exception
  
  printf("Lalala, what a beautiful day! %d", 4/0);

  return retvalue;
}
