#!/bin/bash
#
# Use this script to write the application image when OpenOCD is not running.
#
cd ../../

ELF_FILE=bin/stm32h743-sbx.elf

# CFG_FILE=boards/rijeka.on-the-fly.openocd.cfg
CFG_FILE=boards/rijeka.reset.openocd.cfg

openocd -f $CFG_FILE \
  -c init \
  -c "reset halt" \
  -c "program $ELF_FILE verify reset" \
  -c "reset run" \
  -c shutdown
