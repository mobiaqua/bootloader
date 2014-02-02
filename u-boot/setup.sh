#!/bin/sh

. env.sh

if [ "$1" = "" ]; then
	echo "Please specify platform as argument."
	exit 1
fi

make CROSS_COMPILE=arm-linux-gnueabi- ${1}_config && {
	rm -f cmdsflash

	case $1 in
	h3600)
		echo "cable ${MA_JTAG_ADAPTER}" > cmdsflash
		echo "detect" >> cmdsflash
		echo "poke 0x49000000 1" >> cmdsflash
		echo "detectflash 0" >> cmdsflash
		echo "eraseflash 0 2" >> cmdsflash
		echo "flashmem 0 u-boot.bin" >> cmdsflash
		echo "reset" >> cmdsflash
		echo "quit" >> cmdsflash
		;;
	*)
		echo "flashing with jtag not supported for this platform"
		;;
	esac
}
