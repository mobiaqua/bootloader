#!/bin/sh

if [ "${OE_BASE}" == "" ]; then
	echo "Please setup OE environment first."
	exit 1
fi

curdir=${PWD}
cd ${OE_BASE}/build-${DISTRO} && source env.source && source crosstools-setup
cd ${curdir}
