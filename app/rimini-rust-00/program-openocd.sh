#!/bin/bash

ELF_FILE=target/thumbv7em-none-eabihf/debug/main

CFG_FILE=../../boards/rimini/rimini.openocd.cfg

openocd -f $CFG_FILE \
  -c init \
  -c "reset halt" \
  -c "program $ELF_FILE verify reset" \
  -c "reset run" \
  -c shutdown
  