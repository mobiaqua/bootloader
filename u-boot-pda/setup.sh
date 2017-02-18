#!/bin/sh

. env.sh

if [ "$1" = "" ]; then
	echo "Please specify platform as argument."
	echo "Supported platforms: h3600, h3800"
	exit 1
fi

function addcmd() {
	echo "$1" >> cmdsflash
	if [ "$2" != "n" ]; then
		echo "$1" >> cmdsreset
	fi
}

make CROSS_COMPILE=arm-linux-gnueabi- ${1}_config && {
	rm -f cmdsflash
	rm -f cmdsreset

	case $1 in
	h3600)
		addcmd "cable ${MA_JTAG_ADAPTER}"
		addcmd "detect"
		addcmd "poke 0x49000000 1" n # unlock flash for writting
		addcmd "detectflash 0"
		addcmd "flashmem 0 u-boot.bin noverify" n
		addcmd "reset"
		addcmd "quit"
		;;
	h3800)
		addcmd "cable ${MA_JTAG_ADAPTER}"
		addcmd "detect"
		addcmd "poke 0x49001f00 1" n # unlock flash for writting
		addcmd "detectflash 0"
		addcmd "flashmem 0 u-boot.bin noverify" n
		addcmd "reset"
		addcmd "quit"
		;;
	*)
		echo "flashing with jtag not supported for this platform"
		exit 1
		;;
	esac
}
