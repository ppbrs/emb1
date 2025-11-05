
MEMORY {
	/* Main flash memory. */
	flash_region (RX) : ORIGIN = 0x08000000, LENGTH = 64K /* for STM32F051x8 */

	/* 0x1FFF EC00 - 0x1FFF F7FF 3 KBSystem memory */
	/* 0x1FFF F800 - 0x1FFF FBFF 1 KBOption bytes */

	/* Main system SRAM. */
	sram_region (WXA) : ORIGIN = 0x20000000, LENGTH = 8K

	stm32f0_periph_region (WR) : ORIGIN = 0x40000000, LENGTH = 0x08001800

	cortexm0_periph_region (WR) : ORIGIN = 0xE0000000, LENGTH = 0x00100000 
}

/* check this: https://developer.arm.com/documentation/107976/21-1-1/Map-code-and-data-to-your-target-device/Linker-scripts/Linker-script-PHDRS-command */

SECTIONS {

	INCLUDE arch/arm/armv6_m/armv6-m.sections.ld /* sysregs at E0000000 */

	apb (0x40000000) : AT(0x40000000) {
		. = 0x00000; KEEP(*(.bss.mmreg.tim2))
		. = 0x00400; KEEP(*(.bss.mmreg.tim3))
		. = 0x01000; KEEP(*(.bss.mmreg.tim6))
		. = 0x01400; KEEP(*(.bss.mmreg.tim7))
		. = 0x02000; KEEP(*(.bss.mmreg.tim14))
		. = 0x02800; KEEP(*(.bss.mmreg.rtc))
		. = 0x02c00; KEEP(*(.bss.mmreg.wwdg))
		. = 0x03000; KEEP(*(.bss.mmreg.iwdg))
		. = 0x03800; KEEP(*(.bss.mmreg.spi2))
		. = 0x04400; KEEP(*(.bss.mmreg.usart2))
		. = 0x04800; KEEP(*(.bss.mmreg.usart3))
		. = 0x04C00; KEEP(*(.bss.mmreg.usart4))
		. = 0x05000; KEEP(*(.bss.mmreg.usart5))
		. = 0x05400; KEEP(*(.bss.mmreg.i2c1))
		. = 0x05800; KEEP(*(.bss.mmreg.i2c2))
		. = 0x05C00; KEEP(*(.bss.mmreg.usb))
		. = 0x06000; KEEP(*(.bss.mmreg.usb_can_sram))
		. = 0x06400; KEEP(*(.bss.mmreg.can))
		. = 0x06C00; KEEP(*(.bss.mmreg.crs))
		. = 0x07000; KEEP(*(.bss.mmreg.pwr))
		. = 0x07400; KEEP(*(.bss.mmreg.dac))
		. = 0x07800; KEEP(*(.bss.mmreg.cec))
		. = 0x10000; KEEP(*(.bss.mmreg.syscfg_comp))
		. = 0x10400; KEEP(*(.bss.mmreg.exti))
		. = 0x11400; KEEP(*(.bss.mmreg.usart6))
		. = 0x11800; KEEP(*(.bss.mmreg.usart7))
		. = 0x11C00; KEEP(*(.bss.mmreg.usart8))
		. = 0x12400; KEEP(*(.bss.mmreg.adc))
		. = 0x12C00; KEEP(*(.bss.mmreg.tim1))
		. = 0x13000; KEEP(*(.bss.mmreg.spi1_i2s1))
		. = 0x13800; KEEP(*(.bss.mmreg.usart1))
		. = 0x14000; KEEP(*(.bss.mmreg.tim15))
		. = 0x14400; KEEP(*(.bss.mmreg.tim16))
		. = 0x14800; KEEP(*(.bss.mmreg.tim17))
		. = 0x15800; KEEP(*(.bss.mmreg.dbgmcu))
	}

	ahb1 (0x40020000) : AT(0x40020000) {
		. = 0x1000; KEEP(*(.bss.mmreg.rcc))

		/*
		0x4002 0000 - 0x400203FF DMA
		0x4002 0400 - 0x400207FF DMA2
		0x4002 2000 - 0x400223FF FLASH interface
		0x4002 3000 - 0x400233FF CRC
		0x4002 4000 - 0x400243FF TSC
		*/
	}

	ahb2 (0x48000000) : AT(0x48000000) {
		. = 0x0000; KEEP(*(.bss.mmreg.gpioa))
		. = 0x0400; KEEP(*(.bss.mmreg.gpiob))
		. = 0x0800; KEEP(*(.bss.mmreg.gpioc))
		. = 0x0C00; KEEP(*(.bss.mmreg.gpiod))
		. = 0x1000; KEEP(*(.bss.mmreg.gpioe))
		. = 0x1400; KEEP(*(.bss.mmreg.gpiof))
	}

	INCLUDE arch/arm/armv6_m/stm32f0/stm32f0.sections.ld /* flash, sram SECTIONS */
}
