/*
 * (C) Copyright 2000-2004
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/*
 * The purpose of this code is to signal the operational status of a
 * target which usually boots over the network; while running in
 * PCBoot, a status LED is blinking. As soon as a valid BOOTP reply
 * message has been received, the LED is turned off. The Linux
 * kernel, once it is running, will start blinking the LED again,
 * with another frequency.
 */

#ifndef _STATUS_LED_H_
#define	_STATUS_LED_H_

#ifdef CONFIG_STATUS_LED

#define STATUS_LED_OFF		0
#define STATUS_LED_BLINKING	1
#define STATUS_LED_ON		2

void status_led_tick (unsigned long timestamp);
void status_led_set  (int led, int state);

/*****  TQM8xxL  ********************************************************/
#if defined(CONFIG_TQM8xxL)
# define STATUS_LED_PAR		im_cpm.cp_pbpar
# define STATUS_LED_DIR		im_cpm.cp_pbdir
# define STATUS_LED_ODR		im_cpm.cp_pbodr
# define STATUS_LED_DAT		im_cpm.cp_pbdat

# define STATUS_LED_BIT		0x00000001
# define STATUS_LED_PERIOD	(CONFIG_SYS_HZ / 2)
# define STATUS_LED_STATE	STATUS_LED_BLINKING

# define STATUS_LED_ACTIVE	1		/* LED on for bit == 1	*/

# define STATUS_LED_BOOT	0		/* LED 0 used for boot status */

/*****  MVS v1  **********************************************************/
#elif (defined(CONFIG_MVS) && CONFIG_MVS < 2)
# define STATUS_LED_PAR		im_ioport.iop_pdpar
# define STATUS_LED_DIR		im_ioport.iop_pddir
# undef  STATUS_LED_ODR
# define STATUS_LED_DAT		im_ioport.iop_pddat

# define STATUS_LED_BIT		0x00000001
# define STATUS_LED_PERIOD	(CONFIG_SYS_HZ / 2)
# define STATUS_LED_STATE	STATUS_LED_BLINKING

# define STATUS_LED_ACTIVE	1		/* LED on for bit == 1	*/

# define STATUS_LED_BOOT	0		/* LED 0 used for boot status */

/*****  IVMS8  **********************************************************/
#elif defined(CONFIG_IVMS8)

# define STATUS_LED_PAR		im_cpm.cp_pbpar
# define STATUS_LED_DIR		im_cpm.cp_pbdir
# define STATUS_LED_ODR		im_cpm.cp_pbodr
# define STATUS_LED_DAT		im_cpm.cp_pbdat

# define STATUS_LED_BIT		0x00000010	/* LED 0 is on PB.27	*/
# define STATUS_LED_PERIOD	(1 * CONFIG_SYS_HZ)
# define STATUS_LED_STATE	STATUS_LED_OFF
# define STATUS_LED_BIT1	0x00000020	/* LED 1 is on PB.26	*/
# define STATUS_LED_PERIOD1	(1 * CONFIG_SYS_HZ)
# define STATUS_LED_STATE1	STATUS_LED_OFF
/* IDE LED usable for other purposes, too */
# define STATUS_LED_BIT2	0x00000008	/* LED 2 is on PB.28	*/
# define STATUS_LED_PERIOD2	(1 * CONFIG_SYS_HZ)
# define STATUS_LED_STATE2	STATUS_LED_OFF

# define STATUS_LED_ACTIVE	1		/* LED on for bit == 1	*/

# define STATUS_ILOCK_SWITCH	0x00800000	/* ILOCK switch in IRQ4	*/

# define STATUS_ILOCK_PERIOD	(CONFIG_SYS_HZ / 10)	/* about every 100 ms	*/

# define STATUS_LED_YELLOW	0
# define STATUS_LED_GREEN	1
# define STATUS_LED_BOOT	2		/* IDE LED used for boot status */

/*****  IVML24  *********************************************************/
#elif defined(CONFIG_IVML24)

# define STATUS_LED_PAR		im_cpm.cp_pbpar
# define STATUS_LED_DIR		im_cpm.cp_pbdir
# define STATUS_LED_ODR		im_cpm.cp_pbodr
# define STATUS_LED_DAT		im_cpm.cp_pbdat

# define STATUS_LED_BIT		0x00000010	/* LED 0 is on PB.27	*/
# define STATUS_LED_PERIOD	(1 * CONFIG_SYS_HZ)
# define STATUS_LED_STATE	STATUS_LED_OFF
# define STATUS_LED_BIT1	0x00000020	/* LED 1 is on PB.26	*/
# define STATUS_LED_PERIOD1	(1 * CONFIG_SYS_HZ)
# define STATUS_LED_STATE1	STATUS_LED_OFF
/* IDE LED usable for other purposes, too */
# define STATUS_LED_BIT2	0x00000008	/* LED 2 is on PB.28	*/
# define STATUS_LED_PERIOD2	(1 * CONFIG_SYS_HZ)
# define STATUS_LED_STATE2	STATUS_LED_OFF

# define STATUS_LED_ACTIVE	1		/* LED on for bit == 1	*/

# define STATUS_ILOCK_SWITCH	0x00004000	/* ILOCK is on PB.17	*/

# define STATUS_ILOCK_PERIOD	(CONFIG_SYS_HZ / 10)	/* about every 100 ms	*/

# define STATUS_LED_YELLOW	0
# define STATUS_LED_GREEN	1
# define STATUS_LED_BOOT	2		/* IDE LED used for boot status */

/*****  Someone else defines these  *************************************/
#elif defined(STATUS_LED_PAR)

  /*
   * ADVICE: Define in your board configuration file rather than
   * filling this file up with lots of custom board stuff.
   */

/*****  NetVia   ********************************************************/
#elif defined(CONFIG_NETVIA)

#if !defined(CONFIG_NETVIA_VERSION) || CONFIG_NETVIA_VERSION == 1

#define STATUS_LED_PAR		im_ioport.iop_pdpar
#define STATUS_LED_DIR		im_ioport.iop_pddir
#undef  STATUS_LED_ODR
#define STATUS_LED_DAT		im_ioport.iop_pddat

# define STATUS_LED_BIT		0x0080			/* PD.8 */
# define STATUS_LED_PERIOD	(CONFIG_SYS_HZ / 2)
# define STATUS_LED_STATE	STATUS_LED_BLINKING

# define STATUS_LED_BIT1	0x0040			/* PD.9 */
# define STATUS_LED_PERIOD1	(CONFIG_SYS_HZ / 2)
# define STATUS_LED_STATE1	STATUS_LED_OFF

# define STATUS_LED_ACTIVE	0		/* LED on for bit == 0	*/
# define STATUS_LED_BOOT	0		/* LED 0 used for boot status */

#endif

/*****  CMI   ********************************************************/
#elif defined(CONFIG_CMI)
# define STATUS_LED_DIR		im_mios.mios_mpiosm32ddr
# define STATUS_LED_DAT		im_mios.mios_mpiosm32dr

# define STATUS_LED_BIT		0x2000		/* Select one of the 16 possible*/
						/* MIOS outputs */
# define STATUS_LED_PERIOD	(CONFIG_SYS_HZ / 2)	/* Blinking periode is 500 ms */
# define STATUS_LED_STATE	STATUS_LED_BLINKING

# define STATUS_LED_ACTIVE	1		/* LED on for bit == 0	*/
# define STATUS_LED_BOOT	0		/* LED 0 used for boot status */

/*****  KUP4K, KUP4X  ****************************************************/
#elif defined(CONFIG_KUP4K) || defined(CONFIG_KUP4X)

# define STATUS_LED_PAR		im_ioport.iop_papar
# define STATUS_LED_DIR		im_ioport.iop_padir
# define STATUS_LED_ODR		im_ioport.iop_paodr
# define STATUS_LED_DAT		im_ioport.iop_padat

# define STATUS_LED_BIT		0x00000300  /*  green + red    PA[8]=yellow,  PA[7]=red,  PA[6]=green */
# define STATUS_LED_PERIOD	(CONFIG_SYS_HZ / 2)
# define STATUS_LED_STATE	STATUS_LED_BLINKING

# define STATUS_LED_ACTIVE	1		/* LED on for bit == 1	*/

# define STATUS_LED_BOOT	0		/* LED 0 used for boot status */

#elif defined(CONFIG_V38B)

# define STATUS_LED_BIT		0x0010			/* Timer7 GPIO */
# define STATUS_LED_PERIOD	(CONFIG_SYS_HZ / 2)
# define STATUS_LED_STATE	STATUS_LED_BLINKING

# define STATUS_LED_ACTIVE	0		/* LED on for bit == 0 */
# define STATUS_LED_BOOT	0		/* LED 0 used for boot status */

#elif defined(CONFIG_MOTIONPRO)

#define STATUS_LED_BIT		((vu_long *) MPC5XXX_GPT6_ENABLE)
#define STATUS_LED_PERIOD	(CONFIG_SYS_HZ / 10)
#define STATUS_LED_STATE	STATUS_LED_BLINKING

#define STATUS_LED_BIT1		((vu_long *) MPC5XXX_GPT7_ENABLE)
#define STATUS_LED_PERIOD1	(CONFIG_SYS_HZ / 10)
#define STATUS_LED_STATE1	STATUS_LED_OFF

#define STATUS_LED_BOOT		0	/* LED 0 used for boot status */

#elif defined(CONFIG_BOARD_SPECIFIC_LED)
/* led_id_t is unsigned long mask */
typedef unsigned long led_id_t;

extern void __led_toggle (led_id_t mask);
extern void __led_init (led_id_t mask, int state);
extern void __led_set (led_id_t mask, int state);
#else
# error Status LED configuration missing
#endif
/************************************************************************/

#ifndef CONFIG_BOARD_SPECIFIC_LED
# include <asm/status_led.h>
#endif

#endif	/* CONFIG_STATUS_LED	*/

/*
 * Coloured LEDs API
 */
#ifndef	__ASSEMBLY__
void coloured_LED_init(void);
void red_led_on(void);
void red_led_off(void);
void green_led_on(void);
void green_led_off(void);
void yellow_led_on(void);
void yellow_led_off(void);
void blue_led_on(void);
void blue_led_off(void);
#else
	.extern LED_init
	.extern red_led_on
	.extern red_led_off
	.extern yellow_led_on
	.extern yellow_led_off
	.extern green_led_on
	.extern green_led_off
	.extern blue_led_on
	.extern blue_led_off
#endif

#endif	/* _STATUS_LED_H_	*/
