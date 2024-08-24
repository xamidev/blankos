// Raw CPU port I/O kernel module header 
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#ifndef IO_H
#define IO_H

#include <stdint.h>

void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);
void x86_div64_32(uint64_t dividend, uint32_t divisor, uint64_t* quotientOut, uint32_t* remainderOut);

#endif
