/*
stm32h7-arithmetic-renode.ld

*/
ENTRY(resetHandler)

MEMORY {
	/* Instruction tightly coupled memory. */
	itcm_region (RXA) : ORIGIN = 0x00000000, LENGTH = 64K
	/* Flash, two banks, excluding bank 1 sectors 0 and 1. */
	flash_region (RX) : ORIGIN = 0x08000000, LENGTH = 2M

	/* Data tightly coupled memory. */
	dtcm_region (WA) : ORIGIN = 0x20000000, LENGTH = 128K
	/* Main system SRAM. */
	sram_region_axi_d1 (WA) : ORIGIN = 0x24000000, LENGTH = 512K
	/* The special D2 and D3 SRAMs. */
	sram_region_ahb_d2 (WA) : ORIGIN = 0x30000000, LENGTH = (128K + 128K + 32K)
	sram_region_ahb_d3 (WA) : ORIGIN = 0x38000000, LENGTH = 64K
	/* Backup SRAM */
	bkpram_region (RA)  : ORIGIN = 0x38800000, LENGTH = 0K
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

	/* INCLUDE arch/arm/armv7e_m/armv7e-m.sections.ld */

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


	/* INCLUDE arch/arm/armv7e_m/stm32h7/stm32h7.sections.ld */

    /* =========================================================================*/
    /* CODE */
    /* =========================================================================*/

    /* The startup code goes first into FLASH */
    .isr_vector : ALIGN(4) {
        /* 
        The KEEP statement instructs the linker to keep the specified section,
        even if no symbols inside it are referenced.
        Without this directive the vector table, which might not be referenced
        explicitly in code, may be pruned out.
        */
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } >flash_region

    /* The program code and other data goes into FLASH 

    .text : { *(.text)}
    means get all .text sections of all object files 
    and concatenate them into one .text section.

    */
    .text : ALIGN(4) {
        *(.text .text*)
        *(.glue_7)         /* glue arm to thumb code */
        *(.glue_7t)        /* glue thumb to arm code */
        *(.eh_frame)

        KEEP (*(.init))
        KEEP (*(.fini))
        . = ALIGN(4);
    } >flash_region

    .rodata : ALIGN(4) {
        *(.rodata .rodata*)
        . = ALIGN(4);
    } >flash_region

    .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >flash_region
    .ARM : {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } >flash_region

    .preinit_array :
    {
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
    } >flash_region
    .init_array :
    {
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
    } >flash_region
    .fini_array :
    {
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
    } >flash_region

    .itcmram : ALIGN(4) {
        *(.itcmram .itcmram*)
        . = ALIGN(4);
    } >itcm_region

    /* =========================================================================*/
    /* INITIALIZED DATA
    /* =========================================================================*/

    /*
    DTCM = fast
    SRAM1 = regular1
    SRAM2 = regular2
    SRAM3 = regular3
    */

    _data_fast_lma_start = LOADADDR(.data.fast);
    _data_regular1_lma_start = LOADADDR(.data.regular1);
    _data_regular2_lma_start = LOADADDR(.data.regular2);
    _data_regular3_lma_start = LOADADDR(.data.regular3);

    /* Initialized data sections goes into RAM, load LMA copy after code */
    .data.fast : ALIGN(4) {
        _data_fast_vma_start = .;
        *(.data.fast*)
        . = ALIGN(4);
        _data_fast_vma_end = .;
    } >dtcm_region AT> flash_region

    .data.regular1 : ALIGN(4) {
        _data_regular1_vma_start = .;
        *(.data .data.regular1*)
        . = ALIGN(4);
        _data_regular1_vma_end = .;
    } >sram_region_axi_d1 AT> flash_region

    .data.regular2 : ALIGN(4) {
        _data_regular2_vma_start = .;
        *(.data.regular2*)
        . = ALIGN(4);
        _data_regular2_vma_end = .;
    } >sram_region_ahb_d2 AT> flash_region

    .data.regular3 : ALIGN(4) {
        _data_regular3_vma_start = .;
        *(.data.regular3*)
        . = ALIGN(4);
        _data_regular3_vma_end = .;
    } >sram_region_ahb_d3 AT> flash_region


    /* =========================================================================*/
    /* ZERO-INITIALIZED DATA (BSS)
    /* =========================================================================*/

    /*
    DTCM = fast
    SRAM1 = regular1
    SRAM2 = regular2
    SRAM3 = regular3
    */

    .bss.fast : ALIGN(4) {
        *(.bss.fast*)
        . = ALIGN(4);
    } >dtcm_region

    .bss.regular2 : ALIGN(4) {
        *(.bss.regular2*)
        . = ALIGN(4);
    } >sram_region_ahb_d2

    .bss.regular3 : ALIGN(4) {
        *(.bss.regular3*)
        . = ALIGN(4);
    } >sram_region_ahb_d3

    .bss.regular1 : ALIGN(4) {
        *(.bss.regular1* .bss.* .bss COMMON)
        . = ALIGN(4);
    } >sram_region_axi_d1


    _bss_fast_start = ADDR(.bss.fast);
    _bss_fast_end = ADDR(.bss.fast) + SIZEOF(.bss.fast);
    _bss_regular1_start = ADDR(.bss.regular1);
    _bss_regular1_end = ADDR(.bss.regular1) + SIZEOF(.bss.regular1);
    _bss_regular2_start = ADDR(.bss.regular2);
    _bss_regular2_end = ADDR(.bss.regular2) + SIZEOF(.bss.regular2);
    _bss_regular3_start = ADDR(.bss.regular3);
    _bss_regular3_end = ADDR(.bss.regular3) + SIZEOF(.bss.regular3);


    /* =========================================================================*/
    /* MAIN STACK */
    /* =========================================================================*/

    /* Limit of the Main Stack, which is used for exception handlers and the startup code
        (i.e. before the scheduler has started). */
    _main_stack_size = 0x800;
    _main_stack_start = ADDR(main_stack);
    _main_stack_end = ADDR(main_stack) + SIZEOF(main_stack);

    main_stack : ALIGN(4) {
        . = . + _main_stack_size;
    } >dtcm_region

    /* =========================================================================*/
    /* =========================================================================*/

    _sisram_d1 = LOADADDR(.sram_d1);

    /* SRAM_D1 section 
    * 
    * IMPORTANT NOTE! 
    * If initialized variables will be placed in this section, 
    * the startup code needs to be modified to copy the init-values.  
    */
    .sram_d1 :
    {
        . = ALIGN(4);
        _ssram_d1 = .;       /* create a global symbol at sram_d1 start */
        *(.sram_d1)
        *(.sram_d1*)
        
        . = ALIGN(4);
        _esram_d1 = .;       /* create a global symbol at sram_d1 end */
    } >sram_region_axi_d1 AT> flash_region

    _sisram_d2 = LOADADDR(.sram_d2);

    /* SRAM_D2 section 
    * 
    * IMPORTANT NOTE! 
    * If initialized variables will be placed in this section, 
    * the startup code needs to be modified to copy the init-values.  
    */
    .sram_d2 :
    {
        . = ALIGN(4);
        _ssram_d2 = .;       /* create a global symbol at sram_d2 start */
        *(.sram_d2)
        *(.sram_d2*)
        
        . = ALIGN(4);
        _esram_d2 = .;       /* create a global symbol at sram_d2 end */
    } >sram_region_ahb_d2 AT> flash_region

    _sisram_d3 = LOADADDR(.sram_d3);

    /* SRAM_D3 section 
    * 
    * IMPORTANT NOTE! 
    * If initialized variables will be placed in this section, 
    * the startup code needs to be modified to copy the init-values.  
    */
    .sram_d3 :
    {
        . = ALIGN(4);
        _ssram_d3 = .;       /* create a global symbol at sram_d3 start */
        *(.sram_d3)
        *(.sram_d3*)
        
        . = ALIGN(4);
        _esram_d3 = .;       /* create a global symbol at sram_d3 end */
    } >sram_region_ahb_d3 AT> flash_region



    /* MEMORY_bank1 section, code must be located here explicitly            */
    /* Example: extern int foo(void) __attribute__ ((section (".mb1text"))); */
    /*  .memory_b1_text :
    {
        *(.mb1text)        .mb1text sections (code)
        *(.mb1text*)       .mb1text* sections (code) 
        *(.mb1rodata)      read-only data (constants)
        *(.mb1rodata*)
    } >MEMORY_B1 */

    /* Remove information from the standard libraries */
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }

    .ARM.attributes 0 : { *(.ARM.attributes) }


}
