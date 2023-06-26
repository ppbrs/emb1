/*
This file is supposed to be included from within a SECTIONS block of a linker script.
*/

sysregs 0xE0000000 : AT(0xE0000000) {
	. = 0xE010; KEEP(*(.bss.mmreg.systick))
	. = 0xE100; KEEP(*(.bss.mmreg.nvic))
	. = 0xED00; KEEP(*(.bss.mmreg.scb))
}
