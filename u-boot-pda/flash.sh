#!/bin/sh

. env.sh

if [ ! -e u-boot.bin ]; then
	echo "Missing u-boot.bin file to flash!"
	exit 1
fi

if [ ! -e cmdsflash ]; then
	echo "Missing cmdsflash file!"
	exit 1
fi

jtagmini cmdsflash
