// Real-time clock driver implementation for better PRNG
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include <stdint.h>
#include "rtc.h"
#include "../kernel/io.h"
#include "../libc/stdio.h"

uint8_t rtc_read_register(uint8_t reg)
{
	outb(0x70, reg);
	return inb(0x71);
}

uint8_t bcd_to_bin(uint8_t bcd)
{
	return ((bcd/16)*10) + (bcd%16);
}

int rtc_is_updating()
{
	outb(0x70, 0x0A);
	return (inb(0x71) & 0x80);
}

void rtc_read_time(rtc_time_t *time)
{
	while (rtc_is_updating());

	time->seconds = rtc_read_register(0x00);
	time->minutes = rtc_read_register(0x02);
	time->hours = rtc_read_register(0x04);
	time->day = rtc_read_register(0x06);
	time->month = rtc_read_register(0x07);
	time->year = rtc_read_register(0x08);

	outb(0x70, 0x0B);
	uint8_t registerB = inb(0x71);

	if (!(registerB & 0x04))
	{
		time->seconds = bcd_to_bin(time->seconds);
		time->minutes = bcd_to_bin(time->minutes);
		time->hours = bcd_to_bin(time->hours);
		time->day = bcd_to_bin(time->day);
		time->month = bcd_to_bin(time->month);
		time->year = bcd_to_bin(time->year);
	}
}

void print_time(const rtc_time_t *time)
{
	printf("%02d/%02d/%02d %02d:%02d:%02d\n", time->day, time->month, time->year, time->hours, time->minutes, time->seconds);
}

long time_seed()
{
	rtc_time_t* time = {0};
	rtc_read_time(time);
	
	return time->day + time->month + time->year + time->hours + time->minutes + time->seconds;	
}
