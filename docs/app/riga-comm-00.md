# riga-comm-00

An external program sends random ascii messages at 115200 bps.
The board sends out statistics every second about received bytes and messages.

This particular application uses FreeRTOS stream buffers.

Goals:
* Test FreeRTOS stream buffers
* Test STM32F051 USART driver
