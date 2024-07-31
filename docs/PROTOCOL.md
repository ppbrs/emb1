# Goal

* Controlling the embedded device
	* sending commands to execute
	* sending settings that determine its behavior
* Reading the status of the embedded device

Messages are human-readable and resemble the linux terminal commands.

***
# Limitations

There is no addressing in the protocol itself. The protocol assumes that there are only two participants on the link - a **master**, which is normally a PC, and a **slave**, which is normally an embedded system.

A command is limited to ??? symbols including the newline character.

***
# Commands syntax

Commands use the well-known POSIX schema for options and parameters.
A command is a space-separated array of strings named **arguments** or **tokens**, e.g. `prog arg0 arg1 arg2 ...`.

## Parameters aka unnamed parameters
Program parameters can be
* non-required (unexpected),
* required,
* optional.

## Options aka named parameters
An **option** is a type of argument modifying the behavior of a command. Options can be short and long, e.g. `prog -o` and `prog --option`.

An option or the command itself can be parameterized, e.g. `prog -a paramForA`, `prog paramForProg`.

Several short parameterless options can be combined into a single argument, e.g. `cmd -abc` is equivalent to `prog -a -b -c`.

Option parameters can be
* non-required (unexpected),
	* `prog -o`, `prog --option`,
* required,
	* `prog -oval`, `prog -o=val`, `prog -o val`,
	* `prog --option val`, `prog --option=val`,
* optional,
	* `prog -o`, `prog --option`,
	* `prog -oval`, `prog -o=val`, `prog --option val`, `prog --option=val`.

## Limitations

Sub-programs are not supported. For example, `prog -n 10` is valid while `prog subprog -n 10` is not (`subprog` will be considered an unnamed parameter).

***
# Programs
## memory

Read the memory contents and print the values.

`memory -a {address} -s {size} -f {format}`

Options:
* --address a: The address of the first word to print
* --size -s: The number of words to print. Size can be from 1 up to 8.
* --format -f: The format of words that `memory` prints.
	* `u32`, `u16`, `u8`: Decimal unsigned integers
	* `u32h`, `u16h`, `u8h`: Hexadecimal unsigned integers
	* `i32`, `i16`, `i8`: Decimal signed integers
	* Note: The data type is deduced from the format. For example, `u16` outputs 2-byte words.

If options are correct, `memory` outputs the list of values. Examples
```
```

***
## random

Generate random numbers.

`random -s {size} -f {format} [-c {crypto}]`

Options:
* --size -s: The number of words to print. Size can be from 1 up to 8.
* --format -f: The format of words that `memory` prints.
	* `u32`, `u16`, `u8`: Decimal unsigned integers
	* `u32h`, `u16h`, `u8h`: Decimal unsigned integers
	* `i32`, `i16`, `i8`: Decimal signed integers
	* Note: The data type is deduced from the format. For example, `u16` outputs 2-byte words.
* --crypto -c: Whether a crypthographic-quality random number generator should be used.


***
## setting

`setting -r {name}`

***
## os

Get the list of threads.

`os -l`

## selftest

***
# Implementation

1. Split the command into tokens.

2. Parse the tokens into parameters and options according to the command syntax.

***
