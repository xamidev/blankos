// System information kernel module
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "../libc/stdio.h"
#include "../libc/string.h"

void cpuid(int code, unsigned int* a, unsigned int* d)
{
	asm volatile("cpuid"
			: "=a"(*a), "=d"(*d)
			: "a"(code)
			: "ecx", "ebx");
}

