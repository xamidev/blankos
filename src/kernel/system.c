#include "system.h"
#include "../libc/stdint.h"

void *memset(void *dest, char val, size_t count)
{
	char *temp = (char *)dest;
	for(; count != 0; count--) *temp++ = val;
	return dest;
}

void panic()
{
	for (;;);	
}
