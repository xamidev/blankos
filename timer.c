#include "system.h"
#include "stdio.h"

int timer_ticks = 0;

void timer_handler()
{
	timer_ticks++;

	if(timer_ticks % 18 == 0)
	{
		puts("One second has passed\n");
	}
}

void timer_install()
{
	irq_install_handler(0, timer_handler);
}

void delay(int ticks)
{
	unsigned long eticks;
	eticks = timer_ticks + ticks;
	while ((unsigned long)timer_ticks < eticks);
}
