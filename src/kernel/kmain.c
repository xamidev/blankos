#include "../libc/stdio.h"
#include "serial.h"
#include "gdt.h"
#include "idt.h"
#include "system.h"

char* ascii_title =
"\n"
"   oooooooooo o888                         oooo          ooooooo    oooooooo8\n"
"   888    888 888   ooooooo   oo oooooo    888  ooooo o888   888o 888        \n"
"   888oooo88  888   ooooo888   888   888   888o888    888     888  888oooooo \n"
"   888    888 888 888    888   888   888   8888 88o   888o   o888         888\n"
"   o888ooo888 o888o 88ooo88 8o o888o o888o o888o o888o   88ooo88   o88oooo888\n\n"
"   --------------------------------- v0.3.31 --------------------------------\n\n";

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

  colorputs(ascii_title, 10);

  // TODO: Grub modules to load programs
  
  //timer_install();
  keyboard_install();

  shell_install();

  return retvalue;
}
