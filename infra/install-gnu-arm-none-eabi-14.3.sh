#!/bin/bash

source install-common.sh

# https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/downloads
URL=https://developer.arm.com/-/media/Files/downloads/gnu/14.3.rel1/binrel/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi.tar.xz
ARCH_NAME=arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi.tar.xz
EXTRACTED_NAME=arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi

TOOLCHAIN_NAME=gnu-arm-none-eabi-14.3

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
		-v \
		-f ./$DOWNLOADS_DIR/$ARCH_NAME \
		-C $TOOLCHAINS_DIR
		# x: Extracts the files from the archive.
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
