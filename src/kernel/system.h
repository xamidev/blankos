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
void irq_install();
void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(int irq);
void timer_install();
void delay(int ticks);
void keyboard_install();
char keyboard_getchar();
void shell_install();
#endif

