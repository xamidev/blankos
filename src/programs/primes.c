// Prime number computation program
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https//github.com/xamidev/blankos

#include <stdint.h>
#include "../libc/stdio.h"
#include "../kernel/system.h"

#define PRIMES_MAX 1000000

bool isPrime(int n)
{
	if (n == 1 || n == 0) return false;
	for (int i=2; i<= n/2; i++) if (n%i == 0) return false;
	return true;
}

void program_primes()
{
	for (long long x=0; x<PRIMES_MAX; x++)
	{	
		if (isPrime(x))
		{
				printf("%d ", x);	
		}
		delay(2);
	}
	puts("\n");
}
