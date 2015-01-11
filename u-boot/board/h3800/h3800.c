/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * 2004 (c) MontaVista Software, Inc.
 *
 * Copyright (C) 2015 Pawel Kolodziejski <aquadran at users.sourceforge.net>
 * - Added support for iPAQ H3800
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <SA-1100.h>

#include "asic.h"

DECLARE_GLOBAL_DATA_PTR;

int board_early_init_f(void)
{
	GPCR = 0x0fffffff;
	GPDR = 0;

	ASIC1_GPIO_BASE(ASIC1_GPIO_MASK_REG) = ASIC1_GPIO_MASK_DEFAULT;
	ASIC1_GPIO_BASE(ASIC1_GPIO_DIR_REG) = ASIC1_GPIO_DIR_DEFAULT;
	ASIC1_GPIO_BASE(ASIC1_GPIO_OUT_REG) = ASIC1_GPIO_OUT_DEFAULT;

	ASIC2_GPIO_BASE(ASIC2_GPIO_DIR_REG) = ASIC2_GPIO_DIR_DEFAULT;
	ASIC2_GPIO_BASE(ASIC2_GPIO_OUT_REG) = ASIC2_GPIO_OUT_DEFAULT;

	ASIC2_FLASH_BASE(ASIC2_FLASH_WP_REG) = 1;

	return 0;
}

int board_init(void)
{
	gd->bd->bi_arch_number = MACH_TYPE_H3800;
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;

	return 0;
}

int dram_init(void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
	gd->ram_size = PHYS_SDRAM_1_SIZE;

	return (0);
}
