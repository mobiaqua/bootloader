#!/bin/sh

. env.sh

make -j4 CROSS_COMPILE=arm-linux-gnueabi- all
rm -f cmdsflash
