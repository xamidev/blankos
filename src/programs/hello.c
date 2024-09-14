#include "../libc/stdio.h"
#include "../drivers/serial.h"

void main()
{
	serial_printf(3, "Hello, world, from a PROGRAM!\n");
	return;
}
