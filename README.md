# Overview

Embedded systems sandbox.


# Terms

arch = architecture
ARM, x86

mcu
STM32H743

mcu_core
(no multicores yet)

board
Nucleo-H743ZI2

app


# debug
## Starting OpenOCD

Starting the default configuration for the Nucleo board:
$ openocd -f /board/st_nucleo_h743zi.cfg

Starting the local customized configuration:
$ openocd -f board/nucleo743.openocd.cfg
$ openocd -f board/discovery051.openocd.cfg

## Starting GDB

$ gdb-multiarch -x app/stm32h743_sbx/openocd.gdb  ./bin/stm32h743_sbx.elf
$ gdb-multiarch -x app/stm32f051_sbx/openocd.gdb  ./bin/stm32f051_sbx.elf

telnet localhost 4444

mdw 0x58021000  # read GPIOE base register
mdw 0xE000E010 4  # read SysTick registers


b app/stm32h743_sbx/main.cpp:36

# TODO
* USART for human-readable communication
  * ascii-type protocol (bidirectional UART)
* chrono

## maybe later
* debug output (SWO?)

# Nucleo H743

By default the USART3 communication between the target STM32H7 and the STLINK-V3E is enabled, to support the Virtual COM.
PD8 = USART3 TX
PD9 = USART3 RX

PB3 = TRACESWO

# Prerequisites

* googletest version ??? cloned to ...
* openocd version ??? installed to ...

***
# Host tests.

The **googletest** framework is used.
Use this command to build host tests:
```
make host-tests
```
Use this command to run them:
```
make host-tests-run"
```
***
