#!/bin/bash
#
#
#
mkdir tmp

#
#
#
RENODE_GZ=tmp/renode-latest.linux-portable.tar.gz
# Directory where renode will live:
RENODE_DEST=./3party/renode_portable
mkdir $RENODE_DEST
wget https://builds.renode.io/renode-latest.linux-portable.tar.gz -O $RENODE_GZ
tar xf $RENODE_GZ -C $RENODE_DEST --strip-components=1
