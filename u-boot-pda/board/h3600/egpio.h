/*
 * Copyright (C) 2014 Pawel Kolodziejski <aquadran at users.sourceforge.net>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>

#ifndef EGPIO_H
#define EGPIO_H

#define EGPIO	*(volatile unsigned int *)0x49000000

#define EGPIO_VPP_ON		(1 << 0)   /* high - enable write access to flash */
#define EGPIO_CARD_RESET	(1 << 1)   /* high - reset CF card */
#define EGPIO_OPT_RESET		(1 << 2)   /* high - reset expansion pack */
#define EGPIO_CODEC_NRESET	(1 << 3)   /* low - reset UDA1341 */
#define EGPIO_OPT_NVRAM_ON	(1 << 4)   /* high - power on expansion  pack nvram */
#define EGPIO_OPT_ON		(1 << 5)   /* high - power on option pack */
#define EGPIO_LCD_ON		(1 << 6)   /* high - power on 3.3V to LCD */
#define EGPIO_RS232_ON		(1 << 7)   /* high - power on UART3 transceiver */
#define EGPIO_LCD_PCI		(1 << 8)   /* high - power on LCD */
#define EGPIO_IR_ON		(1 << 9)   /* high - power on IRDA */
#define EGPIO_AUD_AMP_ON	(1 << 10)  /* high - power on audio amp */
#define EGPIO_AUD_PWR_ON	(1 << 11)  /* high - power on audio circuit */
#define EGPIO_QMUTE		(1 << 12)  /* high - mute UDA1341 */
#define EGPIO_IR_FSEL		(1 << 13)  /* high - FIR IRDA, low - SIR IRDA */
#define EGPIO_LCD_5V_ON		(1 << 14)  /* high - power 5V to LCD */
#define EGPIO_LVDD_ON		(1 << 15)  /* high - power 9V and -6.5V to LCD */

void set_h3600_egpio(unsigned int bits);
void clear_h3600_egpio(unsigned int bits);

#endif

