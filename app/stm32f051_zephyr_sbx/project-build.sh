#!/bin/bash

PWD0=$PWD
echo $PWD0

# BOARD_NAME=stm32f0_disco
# BOARD_NAME=nucleo_h743zi
# BOARD_NAME=rijeka
BOARD_NAME=riga


# PROJECT_PATH=~/zephyrproject/zephyr/samples/subsys/console/getchar
# PROJECT_PATH=~/zephyrproject/zephyr/samples/subsys/console/getline
# PROJECT_PATH=~/zephyrproject/zephyr/samples/net/sockets/echo
PROJECT_PATH=$PWD0

cd ~/zephyrproject/zephyr
west \
	build \
	--pristine=auto \
	-b=$BOARD_NAME \
	$PROJECT_PATH \
	-- \
	-DBOARD_ROOT=PWD0\..\..


# west build --cmake-only -b nrf52840dk_nrf52840 out_of_tree_board -- -DBOARD_ROOT=.

	# --cmake-only \
# rebuild: --pristine=always
# make: --pristine=auto


# --build-dir $PWD0/build