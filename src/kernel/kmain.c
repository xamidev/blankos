#include "../libc/stdio.h"
#include "serial.h"
#include "gdt.h"
#include "idt.h"
#include "system.h"

#define BUFFER_SIZE 256

int kmain(int retvalue)
{
  
  init_serial();
  log("serial connection established", 3);
  gdt_install();
  log("initialized GDT entries", 2);
  idt_install();
  log("initialized IDT", 2);
  isr_install();
  log("initialized ISRs", 2);
  irq_install();
  __asm__ __volatile__("sti");
  log("initialized IRQs", 2),
 
  log("kernel started", 2);

  clear();

  colorputs("Blank OS version 1 iteration 3 minor 20\n", 10);

  // TODO: Serial printf to dump registers on kernel panic
  // TODO: Fix scrolling bug (framebuffer driver)
  // TODO: Fix keyboard driver bug (some keys mapped weirdly) + add suport for SHIFT and backspace (deleting character)
  // TODO: Grub modules to load programs
  //timer_install();
  keyboard_install();

  char input_buffer[BUFFER_SIZE];
  colorputs("Enter something: ", 9);
  get_input(input_buffer, BUFFER_SIZE);
  printf("\nYou entered: %s\n", input_buffer);

  return retvalue;
}