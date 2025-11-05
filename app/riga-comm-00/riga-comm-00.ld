/* RIGA-COMM-00 */

/*
    includes stm32f051.ld
        MEMORY
            defines flash_region
            defines sram_region
        SECTIONS
            defines MM peripherals: apb, ahb1, ahb2
            includes armv6-m.sections.ld for 0xE0000000 (Cortex-M0 peripherals)
            includes stm32f0.sections.ld for vectors, text, rodata, bss etc.
*/


ENTRY(resetHandler)

INCLUDE arch/arm/armv6_m/stm32f0/stm32f051/stm32f051.ld
