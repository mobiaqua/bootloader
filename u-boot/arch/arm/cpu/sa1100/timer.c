/*
 * Copyright (C) 2011 Marek Vasut <marek.vasut@gmail.com>
 *
 * Based on PXA timer.c code
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <SA-1100.h>
#include <div64.h>

#define TIMER_LOAD_VAL	0xffffffff
#define TIMER_FREQ_HZ	3686400

static unsigned long long tick_to_time(unsigned long long tick)
{
	return lldiv(tick * CONFIG_SYS_HZ, TIMER_FREQ_HZ);
}

static unsigned long long us_to_tick(unsigned long long us)
{
	return lldiv(us * TIMER_FREQ_HZ, 1000000);
}

int timer_init (void)
{
	OSCR = 0;
	return 0;
}

ulong get_timer (ulong base)
{
	return tick_to_time(get_ticks()) - base;
}

void __udelay (unsigned long usec)
{
	unsigned long long tmp;
	ulong tmo;

	tmo = us_to_tick(usec);
	tmp = get_ticks() + tmo;	/* get current timestamp */

	while (get_ticks() < tmp)	/* loop till event */
		/*NOP*/;
}

unsigned long long get_ticks(void)
{
	return OSCR;
}

ulong get_tbclk (void)
{
	return TIMER_FREQ_HZ;
}
