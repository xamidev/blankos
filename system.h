#ifndef SYSTEM_H
#define SYSTEM_H

typedef int size_t;

void *memset(void *dest, char val, size_t count);

struct regs
{
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
};

void isr_install();

#endif
