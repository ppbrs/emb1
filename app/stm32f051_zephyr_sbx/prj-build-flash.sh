#!/bin/bash

BOARD_NAME=riga

PROJECT_PATH=$PWD

ZEPHYRPROJECT_PATH=~/zephyrproject/zephyr

BUILD_PATH=$PROJECT_PATH/build
ELF_PATH=$BUILD_PATH/zephyr/zephyr.elf
SDK_PATH=/opt/zephyr-sdk-0.16.1/arm-zephyr-eabi/arm-zephyr-eabi/bin/

cd $ZEPHYRPROJECT_PATH

if [[ $1 == 'make' ]]; then

	echo BUILD
	west \
		build \
		--pristine=auto \
		-b=$BOARD_NAME \
		$PROJECT_PATH \
		--build-dir $BUILD_PATH

elif [[ $1 == 'flash' ]]; then  # optional

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

elif [[ $1 == 'rebuild' ]]; then  # optional

	echo REBUILD
	west \
		build \
		--pristine=always \
		-b=$BOARD_NAME \
		$PROJECT_PATH \
		--build-dir $BUILD_PATH

else  # optional

	echo Unknown argument: $0

fi

mkdir -p $BUILD_PATH/elf
ELF_SECTIONS=$BUILD_PATH/elf/sections
ELF_SEGMENTS=$BUILD_PATH/elf/segments
ELF_SYMBOLS=$BUILD_PATH/elf/symbols
ELF_SIZE=$BUILD_PATH/elf/size

$SDK_PATH/readelf --sections --wide $ELF_PATH > $ELF_SECTIONS
$SDK_PATH/readelf --segments $ELF_PATH > $ELF_SEGMENTS
$SDK_PATH/readelf --symbols --wide $ELF_PATH > $ELF_SYMBOLS
size $ELF_PATH > $ELF_SIZE