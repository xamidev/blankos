#include "../kernel/system.h"
#include "../libc/stdio.h"

volatile unsigned long global_ticks = 0;

void timer_handler()
{
	global_ticks++;
	if (global_ticks % 20 == 0)
	{
		draw_cursor(white);
	} else if (global_ticks % 20 == 10) {
		erase_cursor();
	}
}

void timer_install()
{
	irq_install_handler(0, timer_handler);
}

void delay(int ticks)
{
	unsigned long eticks;
	eticks = global_ticks + ticks;
	while (global_ticks < eticks);
}

int uptime()
{
	return global_ticks;
}
