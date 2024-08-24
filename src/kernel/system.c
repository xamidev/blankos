#include "system.h"
#include <stdint.h>

void *memset(void *dest, char val, size_t count)
{
	char *temp = (char *)dest;
	for(; count != 0; count--) *temp++ = val;
	return dest;
}

void *memmove(void* dest, const void* src, size_t n)
{
	unsigned char* d = (unsigned char*)dest;
	const unsigned char* s = (const unsigned char*)src;

	if (d < s)
	{
		for (size_t i=0; i<n; i++)
		{
			d[i] = s[i];
		}
	} else {
		for (size_t i=n; i>0; i--)
		{
			d[i-1] = s[i-1];
		}
	}

	return dest;
}

void panic()
{
	for (;;);	
}
