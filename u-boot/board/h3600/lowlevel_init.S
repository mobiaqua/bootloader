/*
 * Memory Setup stuff - based on code from jornada board file: setup.S
 *
 * Copyright (C) 1999 2000 2001 Erik Mouw (J.A.K.Mouw@its.tudelft.nl) and
 *		       Jan-Derk Bakker (J.D.Bakker@its.tudelft.nl)
 * 2004 (c) MontaVista Software, Inc.
 *
 * Copyright (C) 2014 Pawel Kolodziejski <aquadran at users.sourceforge.net>
 * - Added support for iPaq H3600
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */


#include "config.h"
#include "version.h"


#define MDCNFG      0x00
#define MDCAS00     0x04
#define MDCAS01     0x08
#define MDCAS02     0x0C
#define MSC0        0x10
#define MSC1        0x14
#define MSC2        0x2C
#define MECR        0x18
#define MDREFR      0x1C
#define SMCNFG      0x30

#define MDCNFG_DE0          (1 << 0)
#define MDCNFG_DE1          (1 << 1)
#define MDCNFG_DTIM0        (1 << 2)
#define MDCNFG_DWID0        (1 << 3)
#define MDCNFG_DRAC0(v)     ((v & 7) << 4)
#define MDCNFG_CDB20        (1 << 7)
#define MDCNFG_TRP0(v)      ((v & 0xf) << 8)
#define MDCNFG_TDL0(v)      ((v & 3) << 12)
#define MDCNFG_TWR0(v)      ((v & 3) << 14)

#define MDREFR_TRASR(v)     (v & 0xf)
#define MDREFR_DRI(v)       ((v & 0xfff) << 4)
#define MDREFR_E0PIN        (1 << 16)
#define MDREFR_K0RUN        (1 << 17)
#define MDREFR_K0DB2        (1 << 18)
#define MDREFR_E1PIN        (1 << 20)
#define MDREFR_K1RUN        (1 << 21)
#define MDREFR_K1DB2        (1 << 22)
#define MDREFR_K2RUN        (1 << 25)
#define MDREFR_K2DB2        (1 << 26)
#define MDREFR_EAPD         (1 << 28)
#define MDREFR_KAPD         (1 << 29)
#define MDREFR_SLFRSH       (1 << 31)

#define MSC_RT_ROMFLASH     0
#define MSC_RT_SRAM_012     1
#define MSC_RT_BURST4       2
#define MSC_RT_BURST8       3
#define MSC_RBW32           (0 << 2)
#define MSC_RBW16           (1 << 2)
#define MSC_RDF(v)          ((v & 0x1f) << 3)
#define MSC_RDN(v)          ((v & 0x1f) << 8)
#define MSC_RRR(v)          ((v & 0x07) << 13)

#define MECR_BSIO0(v)       ((v & 0x1f) << 0)
#define MECR_BSA0(v)        ((v & 0x1f) << 5)
#define MECR_BSM0(v)        ((v & 0x1f) << 10)
#define MECR_FAST0          (1 << 15)
#define MECR_BSIO1(v)       ((v & 0x1f) << 16)
#define MECR_BSA1(v)        ((v & 0x1f) << 21)
#define MECR_BSM1(v)        ((v & 0x1f) << 26)
#define MECR_FAST1          (1 << 31)

MEM_BASE:     .long   0xa0000000
MEM_START:    .long   0xc0000000
mdcas00:      .long   0xaaaaaaa7
mdcas01:      .long   0xaaaaaaaa
mdcas02:      .long   0xaaaaaaaa
mdrefr:       .long   (MDREFR_TRASR(1) | MDREFR_DRI(512) | MDREFR_E1PIN | MDREFR_K1RUN)
mdcnfg:       .long   (MDCNFG_DE0 | MDCNFG_DTIM0 | MDCNFG_DWID0 | MDCNFG_DRAC0(5) \
                      | MDCNFG_TRP0(3) | MDCNFG_TDL0(3) | MDCNFG_TWR0(3))
msc0:         .long   ( ( (MSC_RT_ROMFLASH | MSC_RBW32 | MSC_RDF(14) | MSC_RDN(3)  | MSC_RRR(2)) <<  0 ) \
                      | ( (MSC_RT_ROMFLASH | MSC_RBW32 | MSC_RDF(31) | MSC_RDN(31) | MSC_RRR(7)) << 16 ) )
msc1:         .long   ( ( (MSC_RT_ROMFLASH | MSC_RBW16 | MSC_RDF(31) | MSC_RDN(31) | MSC_RRR(7)) <<  0 ) \
                      | ( (MSC_RT_ROMFLASH | MSC_RBW16 | MSC_RDF(31) | MSC_RDN(31) | MSC_RRR(7)) << 16 ) )
msc2:         .long   ( ( (MSC_RT_ROMFLASH | MSC_RBW16 | MSC_RDF(31) | MSC_RDN(31) | MSC_RRR(7)) <<  0 ) \
                      | ( (MSC_RT_BURST4   | MSC_RBW32 | MSC_RDF(3)  | MSC_RDN(3)  | MSC_RRR(2)) << 16 ) )
mecr:         .long   ( MECR_BSIO0(10) | MECR_BSA0(10) | MECR_BSM0(6) | MECR_FAST0 \
                      | MECR_BSIO1(10) | MECR_BSA1(10) | MECR_BSM1(6) | MECR_FAST1 )
smcnfg:       .long   0x00000000


.globl lowlevel_init
lowlevel_init:

	ldr r0, MEM_BASE

	ldr	r1, msc0
	str	r1, [r0, #MSC0]
	ldr	r1, msc1
	str	r1, [r0, #MSC1]
	ldr	r1, msc2
	str	r1, [r0, #MSC2]

	ldr	r1, smcnfg
	str	r1, [r0, #SMCNFG]

	ldr	r1, mecr
	str	r1, [r0, #MECR]

	mov r4, #0x2000
wait_sdclk:
	subs    r4, r4, #1
	bne     wait_sdclk

	ldr r1, mdcas00
	str r1, [r0, #MDCAS00]
	ldr r1, mdcas01
	str r1, [r0, #MDCAS01]
	ldr r1, mdcas02
	str r1, [r0, #MDCAS02]

	ldr r1, mdrefr
	str r1, [r0, #MDREFR]

	ldr	r1, mdcnfg
	str	r1, [r0, #MDCNFG]

	ldr	r2, MEM_START
.rept	8
	ldr	r3, [r2]
.endr

	ldr r2, [r0, #MDCNFG]
	orr r2, r2, #MDCNFG_DE0
	str r2, [r0, #MDCNFG]
	nop
	nop

	mov	pc, lr
