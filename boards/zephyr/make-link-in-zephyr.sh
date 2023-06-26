#!/bin/bash
#
# Create symbolic links to this directory in zephyrproject.
#

EMB1_ZEPHYR_BOARDS_ROOT=$PWD
ZEPHYR_ARM_BOARDS_ROOT=~/zephyrproject/zephyr/boards/arm

BOARDS=(rijeka riga)

cd $ZEPHYR_ARM_BOARDS_ROOT
for BOARD in ${BOARDS[*]}; do
	echo
	TARGET=$EMB1_ZEPHYR_BOARDS_ROOT/$BOARD
	echo TARGET=$TARGET, BOARD=$BOARD

	ln -sf $TARGET $BOARD

	echo
	ls -l | grep $BOARD
done
