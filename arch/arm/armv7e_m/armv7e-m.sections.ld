/*
This file is supposed to be included from within a SECTIONS block of a linker script.
*/

sysregs (0xE0000000) : AT(0xE0000000) {
	. = 0x0000; KEEP(*(.bss.mmreg.itm))
	. = 0xE010; KEEP(*(.bss.mmreg.systick))
	. = 0xE100; KEEP(*(.bss.mmreg.nvic))
	. = 0xED00; KEEP(*(.bss.mmreg.scb))
	. = 0xED90; KEEP(*(.bss.mmreg.mpu))
	. = 0xEDF0; KEEP(*(.bss.mmreg.debug2)) /* Debug registers, part 2 */
	. = 0xEF00; KEEP(*(.bss.mmreg.nvic_stir))
	. = 0xEF34; KEEP(*(.bss.mmreg.fpu))
	. = 0xEF50; KEEP(*(.bss.mmreg.cache))
}
