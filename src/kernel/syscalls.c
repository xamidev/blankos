// System calls
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "../libc/stdio.h"

void handle_syscall(int syscall_number)
{
	switch(syscall_number)
	{
		case 1:
			puts("Here's the syscall 1\n");
			break;
		default:
			printf("[error] Invalid syscall number '%d'!\n", syscall_number);
			break;
	}
}

void syscall_handler()
{
	int syscall_number;
	void* arg;
	// mov eax, syscall_number
	// mov ebx, arg
	asm volatile("mov %%eax, %0" : "=r"(syscall_number));
	asm volatile("mov %%ebx, %0" : "=r"(arg));

	printf("[syscall] syscall_number=%d, arg=%p\n", syscall_number, arg);

	handle_syscall(syscall_number);
}
