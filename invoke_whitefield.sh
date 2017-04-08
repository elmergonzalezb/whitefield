#!/bin/bash

. ./config.inc

export LD_LIBRARY_PATH=$NS3PATH

make || exit

if [ "$1" == "gdb" ]; then
	shift
	cmdprefix="gdb --args"
fi
$cmdprefix $BINDIR/whitefield $*