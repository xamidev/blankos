#!/bin/bash

qemu-system-i386 -s -S -drive file=blankos.iso,format=raw &
sleep 1
gdb -x gdbinit
