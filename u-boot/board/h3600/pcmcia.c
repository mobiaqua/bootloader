/*
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <config.h>
#include <pcmcia.h>
#include <asm/io.h>

#include <SA-1100.h>

#include "egpio.h"

#if defined(CONFIG_IDE_RESET)

void ide_set_reset(int idereset)
{
	if (idereset)
		set_h3600_egpio(EGPIO_CARD_RESET);
	else
		clear_h3600_egpio(EGPIO_CARD_RESET);
}

#endif

#if defined(CONFIG_PCMCIA)

#define GPIO_PCMCIA_CD0	GPIO_GPIO17

int pcmcia_on(void)
{
	printf("Enable PCMCIA " PCMCIA_SLOT_MSG "\n");

	if (!(GPLR & GPIO_PCMCIA_CD0)) {
		printf("Card detect\n");
	}

	set_h3600_egpio(EGPIO_OPT_NVRAM_ON);
	udelay(250000); // 250ms
	set_h3600_egpio(EGPIO_OPT_ON);
	udelay(200000); // 200ms

	if (check_ide_device(0) != 0) {
		printf("CF card doesn't support IDE\n");
		return 1;
	}

	return 0;
}

int pcmcia_off(void)
{
	printf ("Disable PCMCIA " PCMCIA_SLOT_MSG "\n");

	clear_h3600_egpio(EGPIO_OPT_ON);
	clear_h3600_egpio(EGPIO_OPT_NVRAM_ON);

	return 0;
}

#endif /* CONFIG_PCMCIA */
