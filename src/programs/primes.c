// Prime number computation program
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include <stdint.h>
#include "../libc/stdio.h"
#include "../kernel/system.h"
#include "../libc/string.h"

#define PRIMES_MAX 1000000

bool isPrime(int n)
{
	if (n == 1 || n == 0) return false;
	for (int i=2; i<= n/2; i++) if (n%i == 0) return false;
	return true;
}

void program_primes(int argc, char* argv[])
{
	int primes_max;
	
	if (argc == 1)
	{
		primes_max = PRIMES_MAX;
	} else if (argc == 2)
	{
		primes_max = atoi(argv[1]);
	}

	for (long long x=0; x<primes_max; x++)
	{	
		if (isPrime(x))
		{
				printf("%d ", x);	
		}
		delay(1);
	}
	puts("\n");
}
