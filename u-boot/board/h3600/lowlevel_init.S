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

#define UTCR0      0x00
#define UTCR1      0x04
#define UTCR2      0x08
#define UTCR3      0x0c
#define UTDR       0x14
#define UTSR0      0x1c
#define UTSR1      0x20
#define UTCR3_RXE  (1 << 0)
#define UTCR3_TXE  (1 << 1)
#define UTCR0_8BIT (1 << 3)
#define UTCR0_1SB  (0 << 2)
#define UTSR1_TBY  (1 << 0)
#define UTSR1_TNF  (1 << 2)

#define RCSR       0x04
#define RCSR_HWR   (1 << 0)
#define RCSR_SWR   (1 << 1)
#define RCSR_WDR   (1 << 2)
#define RCSR_SMR   (1 << 3)

#define PSSR       0x04
#define PSSR_SSS   (1 << 0)
#define PSSR_BFS   (1 << 1)
#define PSSR_VFS   (1 << 2)
#define PSSR_DH    (1 << 3)
#define PSSR_PH    (1 << 4)

#define PSPR       0x08

#define EGPIO_VPP_ON   (1 << 0)
#define EGPIO_RS232_ON (1 << 7)

MEM_START:    .long   0xc0000000
MEM_BASE:     .long   0xa0000000
EGPIO_BASE:   .long   0x49000000
UART3_BASE:   .long   0x80050000
RC_BASE:      .long   0x90030000
PM_BASE:      .long   0x90020000


mdcas00:      .long   0xaaaaaaa7
mdcas01:      .long   0xaaaaaaaa
mdcas02:      .long   0xaaaaaaaa
mdrefr:       .long   (MDREFR_TRASR(1) | MDREFR_DRI(512) | MDREFR_E1PIN | MDREFR_K1RUN)
mdcnfg:       .long   (MDCNFG_DTIM0 | MDCNFG_DRAC0(5) | MDCNFG_TRP0(3) | MDCNFG_TDL0(3) | MDCNFG_TWR0(3))
msc0:         .long   ( ( (MSC_RT_ROMFLASH | MSC_RBW32 | MSC_RDF(14) | MSC_RDN(3)  | MSC_RRR(2)) <<  0 ) \
                      | ( (MSC_RT_ROMFLASH | MSC_RBW32 | MSC_RDF(31) | MSC_RDN(31) | MSC_RRR(7)) << 16 ) )
msc1:         .long   ( ( (MSC_RT_ROMFLASH | MSC_RBW16 | MSC_RDF(31) | MSC_RDN(31) | MSC_RRR(7)) <<  0 ) \
                      | ( (MSC_RT_ROMFLASH | MSC_RBW16 | MSC_RDF(31) | MSC_RDN(31) | MSC_RRR(7)) << 16 ) )
msc2:         .long   ( ( (MSC_RT_ROMFLASH | MSC_RBW16 | MSC_RDF(31) | MSC_RDN(31) | MSC_RRR(7)) <<  0 ) \
                      | ( (MSC_RT_BURST4   | MSC_RBW32 | MSC_RDF(3)  | MSC_RDN(3)  | MSC_RRR(2)) << 16 ) )
mecr:         .long   ( MECR_BSIO0(10) | MECR_BSA0(10) | MECR_BSM0(6) | MECR_FAST0 \
                      | MECR_BSIO1(10) | MECR_BSA1(10) | MECR_BSM1(6) | MECR_FAST1 )
smcnfg:       .long   0x00000000

init_str:
	.ascii  "Starting U-Boot..."
	.byte   0

.align 4
init_str_ptr:
	.long  init_str

.align 4
.globl lowlevel_init
lowlevel_init:

	mov	r13, lr

	bl	h3600_serial3_init
	ldr	r0, init_str_ptr
	bl	h3600_serial3_put_string


	ldr	r0, MEM_BASE

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


	ldr	r0, RC_BASE
	ldr	r1, [r0, #RCSR]
	and	r1, r1, #RCSR_SMR
	teq	r1, #RCSR_SMR
	bne	notwakeup
wakeup:
	mov	r1, #RCSR_SMR
	str	r1, [r0]

	ldr	r0, PM_BASE
	mov	r1, #(PSSR_PH | PSSR_DH)
	str	r1, [r0, #PSSR]

	ldr	r4, [r0, #PSPR]

	ldr	r0, MEM_BASE
	ldr	r1, mdcas00
	str	r1, [r0, #MDCAS00]
	ldr	r1, mdcas01
	str	r1, [r0, #MDCAS01]
	ldr	r1, mdcas02
	str	r1, [r0, #MDCAS02]

	ldr	r1, [r0, #MDREFR]
	bic	r1, r1, #MDREFR_EAPD | MDREFR_KAPD
	orr	r1, r1, #MDREFR_K1RUN
	str	r1, [r0, #MDREFR]
	bic	r1, r1, #MDREFR_SLFRSH
	str	r1, [r0, #MDREFR]
	orr	r1, r1, #MDREFR_E1PIN
	str	r1, [r0, #MDREFR]
	ldr	r1, mdrefr
	str	r1, [r0, #MDREFR]

	ldr	r1, mdcnfg
	orr	r1, r1, #MDCNFG_DE0
	str	r1, [r0, #MDCNFG]

	mov	pc, r4

notwakeup:
	mov	r4, #0x2000
wait_sdclk:
	subs	r4, r4, #1
	bne	wait_sdclk

	ldr	r0, MEM_BASE

	ldr	r1, mdcas00
	str	r1, [r0, #MDCAS00]
	ldr	r1, mdcas01
	str	r1, [r0, #MDCAS01]
	ldr	r1, mdcas02
	str	r1, [r0, #MDCAS02]

	ldr	r1, mdrefr
	str	r1, [r0, #MDREFR]

	ldr	r1, mdcnfg
	str	r1, [r0, #MDCNFG]

	ldr	r2, MEM_START
.rept	8
	ldr	r3, [r2]
.endr

	ldr	r2, [r0, #MDCNFG]
	orr	r2, r2, #MDCNFG_DE0
	str	r2, [r0, #MDCNFG]
	nop
	nop

	mov	pc, r13


h3600_serial3_init:
	ldr     r0, EGPIO_BASE
	mov	r1, #(EGPIO_RS232_ON)
	str	r1, [r0, #0]
.rept	100
	nop
.endr
	ldr	r0, UART3_BASE
	mov	r1, #0x00
	str	r1, [r0, #UTCR3]
	mov	r1, #0xff
	str	r1, [r0, #UTSR0]
	mov	r1, #(UTCR0_8BIT | UTCR0_1SB)
	str	r1, [r0, #UTCR0]
	mov	r1, #0x00
	str	r1, [r0, #UTCR1]
	mov	r1, #1 // 115200
	str	r1, [r0, #UTCR2]
	mov	r1, #(UTCR3_RXE | UTCR3_TXE)
	str	r1, [r0, #UTCR3]

	mov	pc, lr


.globl h3600_serial3_put_char
h3600_serial3_put_char:
	ldr	r1, UART3_BASE
full:
	ldr	r2, [r1, #UTSR1]
	tst	r2, #UTSR1_TNF
	beq	full
	str	r0, [r1, #UTDR]
busy:
	ldr	r2, [r1, #UTSR1]
	tst	r2, #UTSR1_TBY
	bne	busy

	mov	pc, lr

.globl h3600_serial3_put_string
h3600_serial3_put_string:
	mov	r8, lr

	mov	r4, r0
	mov	r3, #0
	mov	r0, #0
next_char:
	ldrb	r0, [r4, r3]
	cmp	r0, #0
	beq	end
	bl	h3600_serial3_put_char
	add	r3, #1
	b	next_char
end:
	mov	r0, #'\r'
	bl	h3600_serial3_put_char
	mov	r0, #'\n'
	bl	h3600_serial3_put_char

	mov	pc, r8
