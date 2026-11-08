#!/bin/bash
# Grabbing renode-xxxx.linux-portable.tar.gz from https://builds.renode.io.

source install-common.sh

RENODE_NAME="renode-1.16.0+20260123gita3e74b5fa"

RENODE_GZ="$RENODE_NAME.linux-portable.tar.gz"
RENODE_URL_PREFIX="https://builds.renode.io"

# Directory where renode will live:
RENODE_DEST=$RENODE_DIR/$RENODE_NAME

function download {
	echo Downloading to $
	wget $URL_PREFIX/$RENODE_GZ -O $DOWNLOADS_DIR/$RENODE_GZ
}

function unpack {
	echo Preparing directory for renode
	mkdir -p $RENODE_DEST/
	echo Unpacking tar.gz
	tar xf $DOWNLOADS_DIR/$RENODE_GZ -C $RENODE_DEST --strip-components=1
	echo Done unpacking
}

# download

unpack

echo
$RENODE_DEST/renode --version
echo
