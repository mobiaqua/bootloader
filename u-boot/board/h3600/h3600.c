/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * 2004 (c) MontaVista Software, Inc.
 *
 * Copyright (C) 2014 Pawel Kolodziejski <aquadran at users.sourceforge.net>
 * - Added support for iPaq H3600
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <SA-1100.h>

#include "egpio.h"

DECLARE_GLOBAL_DATA_PTR;

/* ------------------------------------------------------------------------- */

int board_early_init_f(void)
{
	EGPIO = EGPIO_RS232_ON;

	return 0;
}

int board_init(void)
{
	gd->bd->bi_arch_number = MACH_TYPE_H3600;
	gd->bd->bi_boot_params = 0xC0000100;

	return 0;
}

int dram_init(void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	return (0);
}
