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
  -c "flash write_image erase $ELF_FILE" \
  -c "flash verify_image $ELF_FILE" \
  -c "reset run" \
  -c shutdown
