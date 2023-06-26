
MEMORY {
	/* Instruction tightly coupled memory. */
	itcm_region (RXA) : ORIGIN = 0x00000000, LENGTH = 64K
	/* Flash, two banks, excluding bank 1 sectors 0 and 1. */
	flash_region (RX) : ORIGIN = 0x08000000, LENGTH = 2M

	/* Data tightly coupled memory. */
	dtcm_region (WXA) : ORIGIN = 0x20000000, LENGTH = 128K
	/* Main system SRAM. */
	sram_region_axi_d1 (WXA) : ORIGIN = 0x24000000, LENGTH = 512K
	/* The special D2 and D3 SRAMs. */
	sram_region_ahb_d2 (WXA) : ORIGIN = 0x30000000, LENGTH = (128K + 128K + 32K)
	sram_region_ahb_d3 (WXA) : ORIGIN = 0x38000000, LENGTH = 64K
	/* Backup SRAM */
	bkpram_region (rx)  : ORIGIN = 0x38800000, LENGTH = 0K
}



/*
The type of the section is inferred from its name.
For .bss.* it's NOBITS.
*/



SECTIONS {

	stsysmem (0x1FF00000) : AT(0x1FF00000) {
		. = 0x1E800; KEEP(*(.bss.mmreg.signature_uid))
		. = 0x1E820; KEEP(*(.bss.mmreg.adc_ts_cal1))
		. = 0x1E840; KEEP(*(.bss.mmreg.adc_ts_cal2))
		. = 0x1E880; KEEP(*(.bss.mmreg.signature_flash_size))
	}

	apb1 (0x40000000) : AT(0x40000000) {
		. = 0x0000; KEEP(*(.bss.mmreg.tim2))
		. = 0x0400; KEEP(*(.bss.mmreg.tim3))
		. = 0x0800; KEEP(*(.bss.mmreg.tim4))
		. = 0x0C00; KEEP(*(.bss.mmreg.tim5))
		. = 0x1000; KEEP(*(.bss.mmreg.tim6))
		. = 0x1400; KEEP(*(.bss.mmreg.tim7))
		. = 0x1800; KEEP(*(.bss.mmreg.tim12))
		. = 0x1C00; KEEP(*(.bss.mmreg.tim13))
		. = 0x2000; KEEP(*(.bss.mmreg.tim14))
		. = 0x3800; KEEP(*(.bss.mmreg.spi2))
		. = 0x3C00; KEEP(*(.bss.mmreg.spi3))
		. = 0x4400; KEEP(*(.bss.mmreg.usart2))
		. = 0x4800; KEEP(*(.bss.mmreg.usart3))
		. = 0x4C00; KEEP(*(.bss.mmreg.uart4))
		. = 0x5000; KEEP(*(.bss.mmreg.uart5))
		. = 0x5400; KEEP(*(.bss.mmreg.i2c1))
		. = 0x5800; KEEP(*(.bss.mmreg.i2c2))
		. = 0x5C00; KEEP(*(.bss.mmreg.i2c3))
		. = 0x7400; KEEP(*(.bss.mmreg.dac))
		. = 0x7800; KEEP(*(.bss.mmreg.uart7))
		. = 0x7C00; KEEP(*(.bss.mmreg.uart8))
	}

	apb2 (0x40010000) : AT(0x40010000) {
		. = 0x0000; KEEP(*(.bss.mmreg.tim1))
		. = 0x0400; KEEP(*(.bss.mmreg.tim8))
		. = 0x1000; KEEP(*(.bss.mmreg.usart1))
		. = 0x1400; KEEP(*(.bss.mmreg.usart6))
		. = 0x3000; KEEP(*(.bss.mmreg.spi1))
		. = 0x3400; KEEP(*(.bss.mmreg.spi4))
		. = 0x4000; KEEP(*(.bss.mmreg.tim15))
		. = 0x4400; KEEP(*(.bss.mmreg.tim16))
		. = 0x4800; KEEP(*(.bss.mmreg.tim17))
		. = 0x5000; KEEP(*(.bss.mmreg.spi5))
		. = 0x7000; KEEP(*(.bss.mmreg.dfsdm))
		. = 0x7400; KEEP(*(.bss.mmreg.hrtim))
	}

	ahb1 (0x40020000) : AT(0x40020000) {
		. = 0x00000; KEEP(*(.bss.mmreg.dma1))
		. = 0x00400; KEEP(*(.bss.mmreg.dma2))
		. = 0x00800; KEEP(*(.bss.mmreg.dmamux1))
		. = 0x02300; KEEP(*(.bss.mmreg.adc_common12))
		. = 0x08000; KEEP(*(.bss.mmreg.eth))
		. = 0x20000; KEEP(*(.bss.mmreg.otghs))
		. = 0x60000; KEEP(*(.bss.mmreg.otgfs))
	}

	ahb1dup (0x40020000) : AT(0x40020000) {
		. = 0x2000; KEEP(*(.bss.mmreg.adc1))
		. = 0x2100; KEEP(*(.bss.mmreg.adc2))
	}

	ahb2 (0x48020000) : AT(0x48020000) {
		. = 0x1800; KEEP(*(.bss.mmreg.rng))
	}

	ahb3 (0x51000000) : AT(0x51000000) {
		. = 0x00000000; KEEP(*(.bss.mmreg.axi))
		. = 0x01000000; KEEP(*(.bss.mmreg.mdma))
		. = 0x01002000; KEEP(*(.bss.mmreg.flash))
		. = 0x01005000; KEEP(*(.bss.mmreg.quadspi))
	}

	apb4 (0x58000000) : AT(0x58000000) {
		. = 0x0000; KEEP(*(.bss.mmreg.exti))
		. = 0x0400; KEEP(*(.bss.mmreg.syscfg))
		. = 0x1400; KEEP(*(.bss.mmreg.spi6))
		. = 0x1C00; KEEP(*(.bss.mmreg.i2c4))
		. = 0x4800; KEEP(*(.bss.mmreg.iwdg))
	}

	ahb4 (0x58020000) : AT(0x58020000) {
		. = 0x0000; KEEP(*(.bss.mmreg.gpioa))
		. = 0x0400; KEEP(*(.bss.mmreg.gpiob))
		. = 0x0800; KEEP(*(.bss.mmreg.gpioc))
		. = 0x0C00; KEEP(*(.bss.mmreg.gpiod))
		. = 0x1000; KEEP(*(.bss.mmreg.gpioe))
		. = 0x1400; KEEP(*(.bss.mmreg.gpiof))
		. = 0x1800; KEEP(*(.bss.mmreg.gpiog))
		. = 0x1C00; KEEP(*(.bss.mmreg.gpioh))
		. = 0x2000; KEEP(*(.bss.mmreg.gpioi))
		. = 0x2400; KEEP(*(.bss.mmreg.gpioj))
		. = 0x2800; KEEP(*(.bss.mmreg.gpiok))
		. = 0x4400; KEEP(*(.bss.mmreg.rcc))
		. = 0x4800; KEEP(*(.bss.mmreg.pwr))
		. = 0x4C00; KEEP(*(.bss.mmreg.crc))
		. = 0x5400; KEEP(*(.bss.mmreg.bdma))
		. = 0x5800; KEEP(*(.bss.mmreg.dmamux2))
		. = 0x6000; KEEP(*(.bss.mmreg.adc3))
		. = 0x6300; KEEP(*(.bss.mmreg.adc_common3))
	}

	stdbg (0x5C001000) : AT(0x5C001000) {
		KEEP(*(.bss.mmreg.dbgmcu))
	}

	dbg_swo (0x5C003000) : AT(0x5C003000) {
		KEEP(*(.bss.mmreg.dbg_swo))
	}
	dbg_swtf (0x5C004000) : AT(0x5C004000) {
		KEEP(*(.bss.mmreg.dbg_swtf))
	}

	INCLUDE arch/arm/armv7e_m/armv7e-m.sections.ld
	INCLUDE arch/arm/armv7e_m/stm32h7/stm32h7.sections.ld


}
