
# Goal

* getting status
* sending commands to execute
* settings

Messages must be human-readable and resemble the linux terminal commands.

# Limitations

There is no addressing in the protocol itself. The protocol assumes that there are only two participants on the link - a `master`, which is normally a PC, and a `slave`, which is normally a board with `emb1` firmware.

A command is limited to ??? symbols including the newline character.

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

***


