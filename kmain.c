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
  log("initialized ISRs", 2);
  irq_install();
  __asm__ __volatile__("sti");
  log("initialized IRQs", 2),
 
  log("kernel started", 2);

  clear();

  colorputs("Blank OS version 1 iteration 3 minor 20\n", 10);

  // TODO: Framebuffer upgrade: color output
  // TODO: Serial printf to dump registers on kernel panic
  // TODO: Fix scrolling bug (framebuffer driver)

  timer_install();

  return retvalue;
}
