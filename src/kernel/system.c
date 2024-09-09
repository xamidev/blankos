// System utilities and routines kernel module
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

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

void *memcpy(void* dest, const void* src, uint32_t n)
{
	uint8_t* d = (uint8_t*)dest;
	const uint8_t* s = (const uint8_t*)src;

	for (uint32_t i=0; i<n; i++)
	{
		d[i] = s[i];
	}
	return dest;
}

void panic()
{
	for (;;);	
}

