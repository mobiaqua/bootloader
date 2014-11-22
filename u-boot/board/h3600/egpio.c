/*
 * Copyright (C) 2014 Pawel Kolodziejski <aquadran at users.sourceforge.net>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <SA-1100.h>

#include "egpio.h"

DECLARE_GLOBAL_DATA_PTR;

static unsigned int h3600_egpio;

void set_h3600_egpio(unsigned int bits)
{
	h3600_egpio |= bits;
	EGPIO = h3600_egpio;
}


void clear_h3600_egpio(unsigned int bits)
{
	h3600_egpio &= ~bits;
	EGPIO = h3600_egpio;
}
