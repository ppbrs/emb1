#!/bin/bash

source install-common.sh

# https://developer.arm.com/downloads/-/gnu-rm
URL=https://developer.arm.com/-/media/files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
ARCH_NAME=gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
EXTRACTED_NAME=gcc-arm-none-eabi-10.3-2021.10

TOOLCHAIN_NAME=gnu-arm-none-eabi-10.3

function download {
	echo Checking URL
	if wget --spider --quiet "$URL" &>/dev/null; then
		echo "URL exists and is accessible."
	else
		echo "URL does not exist or is not accessible."
		exit
	fi
	echo Downloading if it\'s not there
	wget \
		--no-clobber \
		-P $DOWNLOADS_DIR \
		$URL
	echo download done
}

function install {

	echo; echo ► Preparing directory for toolchains
	rm -R $TOOLCHAINS_DIR/$TOOLCHAIN_NAME
	rm -R $TOOLCHAINS_DIR/$EXTRACTED_NAME

	echo; echo ► Extracting archive \'$DOWNLOADS_DIR/$ARCH_NAME\'
	tar \
		-x \
		-j \
		-v \
		-f ./$DOWNLOADS_DIR/$ARCH_NAME \
		-C $TOOLCHAINS_DIR
		# x: Extracts the files from the archive.
		# j: Specifies that the archive is compressed with bzip2.
		# v: Provides verbose output, showing the files being extracted.
		# f: Specifies the archive file to be used.

	echo; echo ► Renaming to \'$TOOLCHAIN_NAME\'
	mv $TOOLCHAINS_DIR/$EXTRACTED_NAME $TOOLCHAINS_DIR/$TOOLCHAIN_NAME

	echo; echo ► Install done.
}

function inspect {
	echo; echo ► Inspecting toolchain \'$TOOLCHAINS_DIR/$TOOLCHAIN_NAME\'
	$TOOLCHAINS_DIR/$TOOLCHAIN_NAME/bin/arm-none-eabi-gcc --version
	echo; echo ► Inspect done.
}

# download

# install

inspect
