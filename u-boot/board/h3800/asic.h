/*
 * Copyright (C) 2015 Pawel Kolodziejski <aquadran at users.sourceforge.net>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>

#ifndef ASIC_H
#define ASIC_H

#define ASIC2_BASE                 0x49000000

#define ASIC2_ACCESS(offset)       *((volatile unsigned short *)(ASIC2_BASE + offset))

#define ASIC2_FLASH_OFFSET         0x1f00
#define ASIC2_FLASH_WP_REG         0x00

#define ASIC2_FLASH_BASE(reg)      ASIC2_ACCESS(ASIC2_FLASH_OFFSET + reg)

#define ASIC1_GPIO_OFFSET          0x1e00
#define ASIC1_GPIO_MASK_REG        0x60
#define ASIC1_GPIO_DIR_REG         0x64
#define ASIC1_GPIO_OUT_REG         0x68

#define ASIC1_GPIO_MASK_DEFAULT    0x7fff
#define ASIC1_GPIO_DIR_DEFAULT     0x7fff
#define ASIC1_GPIO_OUT_DEFAULT     0x2004

#define ASIC1_GPIO_SD_PWR_ON       (1 << 1)
#define ASIC1_GPIO_RS232_ON        (1 << 2)

#define ASIC1_GPIO_BASE(reg)       ASIC2_ACCESS(ASIC1_GPIO_OFFSET + reg)


#define ASIC2_GPIO_OFFSET          0x0000
#define ASIC2_GPIO_DIR_REG         0x00
#define ASIC2_GPIO_OUT_REG         0x14

#define ASIC2_GPIO_DIR_DEFAULT     0x0ce0
#define ASIC2_GPIO_OUT_DEFAULT     0x0000

#define ASIC2_GPIO_CARD_RESET      (1 << 8)
#define ASIC2_GPIO_OPT_ON          (1 << 12)
#define ASIC2_GPIO_OPT_NVRAM_ON    (1 << 13)

#define ASIC2_GPIO_BASE(reg)       ASIC2_ACCESS(ASIC2_GPIO_OFFSET + reg)

#endif
