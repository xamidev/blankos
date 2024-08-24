#include "crypto.h"
#include <stdint.h>

int lcg(int seed)
{
	int x = seed;

	// Constants (ZX81 LCG)
	int a = 75;
	int c = 74;
	long m = 65537;

	for (int i=0; i<10; i++)
	{
		x = (a*x + c) % m;
	}

	return x;
}

int randint(int seed)
{
	int x = lcg(seed);
	return x;
}

static uint32_t next = 1;

uint32_t rand()
{
	next = next * 1103515245 + 12345;
	return (next/65536) % 32768;
}

float rand_float()
{
	return rand() / 32767.0f;
}

void srand(uint32_t seed)
{
	next = seed;
}
