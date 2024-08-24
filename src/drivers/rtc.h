// Real-time clock driver implementation header for better PRNG
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#ifndef RTC_H
#define RTC_H

typedef struct
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t day;
	uint8_t month;
	uint8_t year;
} rtc_time_t;

void rtc_read_time(rtc_time_t *time);
long time_seed();
void print_time(const rtc_time_t *time);

#endif
