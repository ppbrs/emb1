/*
This file is supposed to be included from within a SECTIONS block of a linker script.
*/

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
