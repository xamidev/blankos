// System utilities and routines kernel module header
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https//github.com/xamidev/blankos

#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

typedef int size_t;
#define NULL ((void*)0)

void *memset(void *dest, char val, size_t count);
void *memmove(void* dest, const void* src, size_t n);

struct regs
{
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
};

void panic();
void isr_install();
void irq_install();
void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(int irq);
void timer_install();
void delay(int ticks);
void keyboard_install();
char keyboard_getchar();
void shell_install();
int uptime();

extern volatile unsigned long global_ticks;

extern unsigned int g_multiboot_info_address;

#endif

