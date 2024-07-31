
# Overview

Possible USART use cases:
1. Console-like communication to a PC serial port using ASCII protocol.
2. Binary protocols (LIN, IrDA, Smart Card, Rs-485)
3. On-board communication with ADCs, DACs, etc.

***
# API for console emulation

## Zephyr option 1

Pull-style "getline" access:
`console_getline_init()` in called once to initialize the communication.
`char *console_getline(void)` is a blocking function that returns a line which resides in a system-owned buffer. The line returned does not contain EOL character(s).

`console_getline` is somewhat similar to the standard `fgets`:

`char* fgets( char* str, int count, std::FILE* stream )`
Reads at most `count - 1` characters from the `stream` and stores them in `str`.
Parsing stops if a newline character is found, in which case `str` will contain that newline character, or if end-of-file occurs.
If bytes are read and no errors occur, writes a null character at the position immediately after the last character written to str.
`count`	is typically the length of str.
Returns `str` on success or `nullptr` on failure, e.g. the end-of-file condition when no bytes were read.


## Zephyr option 2

`int console_init()` is called once to initialize the buffered communication.
`int console_getchar(void)` returns a character read (0-255, including control characters) or <0 if an error  occurred.
`int console_putchar(char c)` puts a character into console output buffer. It will be sent to a console asynchronously, e.g. using an IRQ handler. 

`ssize_t console_read(void *dummy, void *buf, size_t size)`
`ssize_t console_write(void *dummy, const void *buf, size_t size)`

***

## emb1 option 1

### input

* Two or more buffers are allocated for console input. One buffer is being filled by characters. When an end-of-line character is received, an OS event is sent to the application and console driver switches to another available buffer. Application sends an OS event to the driver once the buffer is processed to mark is as available.
* ESC and left-right arrows are processed naturally.
* Echo is not sent because applications like minicom can generate echo.
* If no buffers are available, an error message is sent back. (?) Alternatively, nothing is sent back but an internal error counter is incremented.

### output

* Two or more buffers are allocated for console output.
***

## emb1 option 2

Use FreeRTOS stream buffers.

***
