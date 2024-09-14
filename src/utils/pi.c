// Program for Pi computation using Leibniz series
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "../libc/stdio.h"
#include "../libc/string.h"

void program_pi(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s <terms>\n", argv[0]);
		return;
	}

	double pi = 0.0;
	int terms = atoi(argv[1]);
	
	for (int i=0; i<terms; i++)
	{
		double term = 1.0/(2*i+1);
		if (i%2 == 0)
		{
			pi += term;
		} else {
			pi -= term;
		}
	}

	pi *= 4;

	printf("%f\n", pi);
}
