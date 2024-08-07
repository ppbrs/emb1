#!/bin/bash

ELF_FILE=bin/stm32f051-sbx.elf

CFG_FILE=boards/riga.openocd.cfg

cd ../../

openocd -f $CFG_FILE \
  -c init \
  -c "reset halt" \
  -c "flash write_image erase $ELF_FILE" \
  -c "flash verify_image $ELF_FILE" \
  -c "reset run" \
  -c shutdown
