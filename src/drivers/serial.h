// Serial I/O driver header
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#ifndef SERIAL_H
#define SERIAL_H

#define PORT 0x3f8 //COM1

int init_serial();
int is_transmit_empty();
void write_serial(const char a);
void serial_puts(const char* str);
void log(const char* str, const int errlevel);
void serial_printf(int errlevel, const char* fmt, ...);

#endif
