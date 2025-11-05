/*
This file is supposed to be included from within a SECTIONS block of a linker script.

SECTIONS { */

	/* =========================================================================*/
	/* CORTEX-M0 PERIPHERALS */
	/* =========================================================================*/

	sysregs 0xE0000000 (NOLOAD): {
		. = 0xE010; KEEP(*(.bss.mmreg.systick))
		. = 0xE100; KEEP(*(.bss.mmreg.nvic))
		. = 0xED00; KEEP(*(.bss.mmreg.scb))
	} > cortexm0_periph_region

/* } */
