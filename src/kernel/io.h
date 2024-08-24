#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

#include <stdint.h>

void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);
void x86_div64_32(uint64_t dividend, uint32_t divisor, uint64_t* quotientOut, uint32_t* remainderOut);

#endif
