#!/bin/bash

TARGET_NAME=main

RELEASE_OR_DEV=
# RELEASE_OR_DEV=--release

cargo build --bin $TARGET_NAME $RELEASE_OR_DEV
echo

# cargo readobj --bin $TARGET_NAME -- --file-headers
# echo

cargo readobj --bin $TARGET_NAME $RELEASE_OR_DEV -- --symbols --demangle > $TARGET_NAME.symbols
cargo readobj --bin $TARGET_NAME $RELEASE_OR_DEV -- --sections --demangle  > $TARGET_NAME.sections

cargo size --bin $TARGET_NAME $RELEASE_OR_DEV -- -A
echo

# exit

pwd
../../../emb1-tools-infra/renode/renode-1.16.0+20260123gita3e74b5fa/renode \
    -p \
    --console \
    renode/rimini-rust-00.resc

    # --port 4444 \