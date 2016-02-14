#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_SA1110			1	/* This is an SA110 CPU */
#define CONFIG_SYS_FLASH_PROTECTION	1
#define CONFIG_BOARD_EARLY_INIT_F

#define CONFIG_PCMCIA
#define CONFIG_PCMCIA_SLOT_A
#define CONFIG_IDE_PCMCIA
#define CONFIG_IDE_RESET

#define CONFIG_SYS_TEXT_BASE		0x00000000

/*#define DEBUG				1*/

/* we will never enable dcache, because we have to setup MMU first */
#define CONFIG_SYS_DCACHE_OFF

/* Console setting */

#define CONFIG_CMDLINE_TAG		1	/* enable passing of ATAGs      */
#define CONFIG_SETUP_MEMORY_TAGS	1

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 128 * 1024)

/*
 * select serial console configuration
 */
#define CONFIG_SA1100_SERIAL	1
#define CONFIG_SERIAL3		1	/* we use serial 3 */
#define CONFIG_BAUDRATE		115200
#define CONFIG_LOADS_ECHO	1

/*
 * Command line configuration.
 */
#define CONFIG_CMD_FLASH
#define CONFIG_CMD_CONSOLE
#define CONFIG_CMD_ECHO
#define CONFIG_CMD_EDITENV
#define CONFIG_CMD_LOADB
#define CONFIG_CMD_RUN
#define CONFIG_CMD_SAVEENV
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_FAT
#define CONFIG_CMD_FS_GENERIC
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_IDE
#define CONFIG_CMD_PCMCIA

#define CONFIG_DOS_PARTITION

#undef CONFIG_BOOTM_NETBSD
#undef CONFIG_BOOTM_PLAN9
#undef CONFIG_BOOTM_RTEMS
#undef CONFIG_BOOTM_VXWORKS

#define CONFIG_BOOTDELAY	1
#define CONFIG_BOOTARGS	"root=/dev/mtdblock2 rootfstype=jffs2 ro console=ttySA0,115200n8 console=tty1 consoleblank=0 user_debug=31"
/*#define CONFIG_BOOTARGS		"root=/dev/sda1 rootfstype=ext4 console=ttySA0,115200n8 console=tty1 consoleblank=0 user_debug=31"*/
/*#define CONFIG_BOOTCOMMAND	"run boot_kernel"*/
/*#define CONFIG_BOOTARGS		"root=/dev/mtdblock2 rootfstype=jffs2 ro console=tty1 console=ttySA0,115200n8 consoleblank=0 loglevel=7"*/
#define CONFIG_BOOTCOMMAND	"run copy_kernel;bootm"
#define CONFIG_SYS_AUTOLOAD	"n"	/* No autoload */
#define CONFIG_SYS_LOAD_ADDR	CONFIG_SYS_SDRAM_BASE

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP	/* undef to save memory */
#define CONFIG_SYS_PROMPT		"h3800# "
#define CONFIG_SYS_CBSIZE		256	/* console buffsize */
#define CONFIG_SYS_PBSIZE		(256 + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16	/* max number of command args */
#define CONFIG_SYS_BARGSIZE		256	/* Boot Argument Buffer Size */
#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE	/* Start addr for test */
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_SDRAM_BASE + (PHYS_SDRAM_1_SIZE - 0x00200000))

#define CONFIG_SYS_CPUSPEED		0x0a /* core clock 206MHz */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 19200, 38400, 57600, 115200 }

#define	__io

#define CONFIG_SYS_PCMCIA_IO_BASE_ADDR	0x20000000 /* this IO space for pcmcia slot 0 address */
#define CONFIG_SYS_PCMCIA_MEM_BASE_ADDR	0x2C000000 /* this memory space for pcmcia slot 0 address */

#define CONFIG_SYS_PCMCIA_MEM_ADDR	0x28000000 /* it's actually Attributes Space slot 0 address, */
#define CONFIG_SYS_PCMCIA_MEM_SIZE	0x04000000 /* used by cmd_pcmcia.c code and to prevent modify file */

#define CONFIG_SYS_IDE_MAXBUS		1 /* max. 1 IDE busses */
#define CONFIG_SYS_IDE_MAXDEVICE	(CONFIG_SYS_IDE_MAXBUS) /* max. 1 drives per IDE bus */

#define CONFIG_SYS_ATA_BASE_ADDR	CONFIG_SYS_PCMCIA_MEM_BASE_ADDR
#define CONFIG_SYS_ATA_IDE0_OFFSET	0x0000
#define CONFIG_SYS_ATA_DATA_OFFSET	0x0400 /* Offset for data I/O */
#define CONFIG_SYS_ATA_REG_OFFSET	0x0000 /* Offset for normal register access */
#define CONFIG_SYS_ATA_ALT_OFFSET	0x0000 /* Offset for alternate registers */

#define CONFIG_SYS_FLASH_CFI		1
#define CONFIG_FLASH_CFI_DRIVER		1
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE 1
#define CONFIG_SYS_FLASH_CFI_WIDTH	FLASH_CFI_32BIT
#define CONFIG_SYS_FLASH_BASE		0x00000000
#define CONFIG_SYS_MAX_FLASH_BANKS	1
#define CONFIG_SYS_MAX_FLASH_SECT	128
#define CONFIG_SYS_FLASH_BANKS_LIST	{ CONFIG_SYS_FLASH_BASE }
#define CONFIG_SYS_FLASH_EMPTY_INFO	1
#define CONFIG_SYS_MONITOR_LEN		0x00040000
#define CONFIG_SYS_MONITOR_BASE		0x00000000
#define CONFIG_FLASH_SHOW_PROGRESS	1

#define CONFIG_ENV_SIZE			0x00040000
#define CONFIG_ENV_IS_NOWHERE

/*
  Monitor -     0x00000000 - 0x00040000 (256kb)
  Kernel -      0x00040000 - 0x00340000 (3mb)
  Rootfs -      0x00340000 - 0x........ (rest)
*/

#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x1000 - \
					GENERATED_GBL_DATA_SIZE)

#define PHYS_SDRAM_1			0xC0000000	/* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE		0x04000000	/* 64 MB */

#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE
#define CONFIG_FLASH_CFI_MTD
#define MTDIDS_DEFAULT		"nor0=h3800-0"
#define MTDPARTS_DEFAULT	"mtdparts=h3800-0:256k(u-boot),3m(kernel),-(user);"

#define	CONFIG_EXTRA_ENV_SETTINGS				\
	"install_uboot=run copy_uboot;run flash_uboot;\0"	\
	"copy_uboot=pinit on;ide reset;fatload ide 0:1 c0000000 u-boot.bin;\0"		\
	"flash_uboot=protect off 00000000 0003ffff; "			\
	"erase 00000000 0003ffff;cp.b c0000000 00000000 00040000;\0"	\
	"install_kernel=run copy_kernel;run flash_kernel;\0"	\
	"copy_kernel=pinit on;ide reset;fatload ide 0:1 c0000000 uImage.bin;\0"		\
	"flash_kernel=protect off 00040000 0033ffff; "		\
	"erase 00040000 0033ffff;cp.b c0000000 00040000 00300000;\0"	\
	"install_rootfs=run copy_rootfs;run flash_rootfs;\0"	\
	"copy_rootfs=pinit on;ide reset;fatload ide 0:1 c0000000 rootfs.jffs2;\0"	\
	"flash_rootfs=protect off 00340000 00ffffff; "			\
	"erase 00340000 00ffffff;cp.b c0000000 00340000 00cc0000;\0"	\
	"boot_kernel=cp.b 00040000 c0000000 00300000;bootm;\0"
#endif /* __CONFIG_H */
