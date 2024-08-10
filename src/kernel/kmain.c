#include "../libc/stdio.h"
#include "../drivers/serial.h"
#include "gdt.h"
#include "idt.h"
#include "system.h"
//#include <stdarg.h>

char* ascii_title =
"\n"
"   oooooooooo o888                         oooo          ooooooo    oooooooo8\n"
"   888    888 888   ooooooo   oo oooooo    888  ooooo o888   888o 888        \n"
"   888oooo88  888   ooooo888   888   888   888o888    888     888  888oooooo \n"
"   888    888 888 888    888   888   888   8888 88o   888o   o888         888\n"
"   o888ooo888 o888o 88ooo88 8o o888o o888o o888o o888o   88ooo88   o88oooo888\n\n"
"   --------------------------------- v0.3.45 --------------------------------\n\n";

unsigned int g_multiboot_info_address;

void kmain(unsigned int multiboot_info_address)
{
  g_multiboot_info_address = multiboot_info_address;

  init_serial();
  log("serial connection established\n", 3);
  gdt_install();
  log("initialized GDT entries\n", 2);
  idt_install();
  log("initialized IDT\n", 2);
  isr_install();
  log("initialized ISRs\n", 2);
  irq_install();
  __asm__ __volatile__("sti");
  log("initialized IRQs\n", 2),
 
  clear();
  colorputs(ascii_title, 10);
  colorputs("   by @xamidev - star the repo for a cookie!\n\n", 14);

  timer_install();
  serial_printf(2, "%d\tinitialized timer handler", global_ticks); 
  keyboard_install(); 
  serial_printf(2, "%d\tinitialized keyboard handler", global_ticks); 
  shell_install();
  serial_printf(2, "%d\tstarted system shell", global_ticks); 
}
