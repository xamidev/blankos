#include "../libc/stdint.h"
#include "../libc/stdio.h"

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
	}
	puts("\n");
}