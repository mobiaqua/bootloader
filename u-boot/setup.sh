#!/bin/sh

. env.sh

if [ "$1" = "" ]; then
	echo "Please specify platform as argument."
	echo "Supported platforms: h3600, h3800"
	exit 1
fi

function addcmd() {
	echo "$1" >> cmdsflash
}

make CROSS_COMPILE=arm-linux-gnueabi- ${1}_config && {
	rm -f cmdsflash

	case $1 in
	h3600)
		addcmd "cable ${MA_JTAG_ADAPTER}"
		addcmd "detect"
		addcmd "poke 0x49000000 1" # unlock flash for writting
		addcmd "detectflash 0"
		addcmd "flashmem 0 u-boot.bin noverify"
		addcmd "reset"
		addcmd "quit"
		;;
	h3800)
		addcmd "cable ${MA_JTAG_ADAPTER}"
		addcmd "detect"
		addcmd "poke 0x49001f00 1" # unlock flash for writting
		addcmd "detectflash 0"
		addcmd "flashmem 0 u-boot.bin noverify"
		addcmd "reset"
		addcmd "quit"
		;;
	*)
		echo "flashing with jtag not supported for this platform"
		exit 1
		;;
	esac
} && make CROSS_COMPILE=arm-linux-gnueabi- clean
