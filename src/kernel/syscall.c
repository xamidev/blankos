#include <stdarg.h>
#include "../libc/stdio.h"
#include "syscall.h"

syscall_t syscalls[] = {
	(syscall_t)printf,
};

int syscall_handler(int syscall_num, ...)
{
	if ((unsigned)syscall_num < sizeof(syscalls)/sizeof(syscall_t))
	{
		va_list args;
		va_start(args, syscall_num);
		syscalls[syscall_num](va_arg(args, const char*));
		va_end(args);
		return 0;
	}
	return -1;
}
