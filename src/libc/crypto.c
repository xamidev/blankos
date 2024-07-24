#include "crypto.h"

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
