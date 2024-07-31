#include "if/mcu/nvic.h"
#include <cstdint>

#if __STDC_HOSTED__ > 0
#error __STDC_HOSTED__ is not 0
#endif

extern int main();

/* Highest address of the user mode stack */
extern const volatile uint32_t _main_stack_end;
// uint32_t _main_stack_size = 0x100;
/* start address for the initialization values of the .data section.
defined in linker script */
extern uint32_t _data_lma_start;
/* start and end addresses for the .data sections. defined in linker script */
extern uint32_t _data_vma_start, _data_vma_end;

/* start and end addresses for the .bss sections defined in linker script */
extern uint32_t _bss_start, _bss_end;

// extern uint32_t _bss_regular1_start, _bss_regular1_end;
// extern uint32_t _bss_regular2_start, _bss_regular2_end;
// extern uint32_t _bss_regular3_start, _bss_regular3_end;

/*
The STM32F0xx family embeds a nested vectored interrupt controller able to handle up to
32 maskable interrupt channels (not including the 16 interrupt lines of Cortex -M0) and 4
priority levels.
*/

__attribute__((section(".initial_sp_value"), used)) void (*const initialSpValue[])(void) = {
	/* Initial SP value */
	((void (*)(void))(&_main_stack_end)),
};
static_assert(sizeof(initialSpValue) == 4 * 1);


void nvic::defaultHandler() {
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

extern "C" void resetHandler() {
	// TODO
	/* Set stack pointer */
	// __asm("ldr sp, =_main_stack_end"); // Is it necessary?
	// __asm__ volatile("mov r0, %0\n" : "=r"(&_main_stack_end));
	// "nop\n"); // Is it necessary?
	// __asm__ volatile("mrs %0, PSP\n" : "=r"(sp)); // process stack was used


	/* Copy the data segment initializers from flash to SRAM */
	{
		uint32_t *src = &_data_lma_start;
		for(uint32_t *dst = &_data_vma_start; dst < &_data_vma_end;) {
			*dst++ = *src++;
		}
	}

	/* Zero fill the bss segment */
	{
		for(uint32_t *dst = &_bss_start; dst < &_bss_end;) {
			*dst++ = 0;
		}
	}

	/* Call the application's entry point */
	main();
}

void nvic::nmiHandler() {
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}


struct FrameBasic {
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r12;
	uint32_t lr;
	uint32_t pc;
	uint32_t xpsr;
};
static_assert(sizeof(FrameBasic) == 8 * 4);

/*
https://www.embedded.com/debugging-hard-faults-in-arm-cortex-m0-based-socs/

*/
void nvic::hardFaultHandler() {
	uint32_t lr, sp;
	__asm__ volatile("mov %0, LR\n"
					 : "=r"(lr));
	if(lr & (1 << 2)) {
		__asm__ volatile("mrs %0, PSP\n"
						 : "=r"(sp)); // process stack was used
	} else {
		__asm__ volatile("mrs %0, MSP\n"
						 : "=r"(sp)); // main stack was used
	}
	// armv7e_m::reg::SCB::CFSR cfsr;
	// cfsr.word = armv7e_m::reg::SCB::SCB.CFSR.word;
	// (void)cfsr;
	FrameBasic &frameBasic = *(FrameBasic *)sp;
	(void)frameBasic;
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

void svcHandler() {
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

void pendSvHandler() {
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

void sysTickHandler() {
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}
