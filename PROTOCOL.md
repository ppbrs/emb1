
# Goal

* Controlling the embedded device
	* sending commands to execute
	* sending settings that determine its behavior
* Reading the status of the embedded device

Messages are human-readable and resemble the linux terminal commands.

***
# Limitations

There is no addressing in the protocol itself. The protocol assumes that there are only two participants on the link - a `master`, which is normally a PC, and a `slave`, which is normally a board running `emb1` firmware.

A command is limited to ??? symbols including the newline character.

***
# Structure of a command

A command is a space-separated array of strings named **arguments** or **tokens**, e.g. `cmd arg0 arg1 arg2 ...`.

An **option** is a type of argument modifying the behavior of a command. Options can be short and long, e.g. `cmd -v` and `cmd --verbose`.

An option or the command itself can be parameterized, e.g. `cmd -a paramForA`, `cmd paramForCmd`.

Several short options that do not take parameters can be combined into a single argument, e.g. `cmd -abc` is equivalent to `cmd -a -b -c`.

***

# Commands
## read
Read memory

`read -a {address} -s {size} -f {format}`

`get setting -n {name}

## datetime

`datetime`

## ps

Get the list of threads.

## random

Get a random number.
***


