#!/bin/bash

BOARD_NAME=rijeka

PROJECT_PATH=$PWD

ZEPHYRPROJECT_PATH=~/zephyrproject/zephyr

BUILD_PATH=$PROJECT_PATH/build

cd $ZEPHYRPROJECT_PATH

if [[ $1 == 'make' ]]; then

	echo MAKE
	west \
		build \
		--pristine=auto \
		-b=$BOARD_NAME \
		$PROJECT_PATH \
		--build-dir="$BUILD_PATH"

elif [[ $1 == 'flash' ]]; then

	echo MAKE AND FLASH
	west \
		build \
		--pristine=auto \
		-b=$BOARD_NAME \
		$PROJECT_PATH \
		--build-dir="$BUILD_PATH"
	west \
		flash \
		--build-dir="$BUILD_PATH"

elif [[ $1 == 'rebuild' ]]; then

	echo REBUILD
	west \
		build \
		--pristine=always \
		-b=$BOARD_NAME \
		$PROJECT_PATH \
		--build-dir="$BUILD_PATH"

else  # optional

	echo Unknown argument: $0

fi
exit
