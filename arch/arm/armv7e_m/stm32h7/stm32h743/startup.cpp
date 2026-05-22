
#include "arch/arm/armv7e_m/mmreg/itm.h"
#include "arch/arm/armv7e_m/mmreg/scb.h"
#include "arch/arm/armv7e_m/stm32h7/stm32h743/nvic.h"
#include "if/mcu/nvic.h"
#include "if/mcu/tick.h"
#include <cstdint>

/*================== function prototypes ==================*/
extern int main();
extern "C" void __libc_init_array();



/*=================== Global variables ====================*/
/* Highest address of the user mode stack */
extern const volatile uint32_t _main_stack_end;
/* start address for the initialization values of the .data section.
defined in linker script */
extern uint32_t _data_fast_lma_start;
extern uint32_t _data_regular1_lma_start;
extern uint32_t _data_regular2_lma_start;
extern uint32_t _data_regular3_lma_start;
/* start and end addresses for the .data sections. defined in linker script */
extern uint32_t _data_fast_vma_start, _data_fast_vma_end;
extern uint32_t _data_regular1_vma_start, _data_regular1_vma_end;
extern uint32_t _data_regular2_vma_start, _data_regular2_vma_end;
extern uint32_t _data_regular3_vma_start, _data_regular3_vma_end;


/* start and end addresses for the .bss sections defined in linker script */
extern uint32_t _bss_fast_start, _bss_fast_end;
extern uint32_t _bss_regular1_start, _bss_regular1_end;
extern uint32_t _bss_regular2_start, _bss_regular2_end;
extern uint32_t _bss_regular3_start, _bss_regular3_end;

/* The Interrupt Vector Table

When reset is deasserted, execution restarts from the address provided by the reset entry in the vector table. Execution restarts as privileged execution in Thread mode.

The vector table contains the reset value of the stack pointer,
and the start addresses, also called exception vectors, for all exception handlers.

*/

__attribute__((section(".initial_sp_value"), used)) void (*const initialSpValue[])(void) = {
	/* Initial SP value */
	((void (*)(void))(&_main_stack_end)),
};
static_assert(sizeof(initialSpValue) == 4 * 1);

/*================= Function definitions ==================*/

void nvic::defaultHandler() {
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

extern "C" void resetHandler() {
	/* The processor starts in privileged mode */

	/* Set stack pointer */
	__asm("ldr sp, =_main_stack_end"); // Is it necessary?

	/* The FPU is disabled from reset. Here we enable it by writing to CPACR. */
	__asm("ldr r0, =0xE000ED88\n" /* TODO: use CPACR address from scb.h */
		  "ldr r1, [r0]\n" // read CPACR
		  "orr r1, r1, #(0xF << 20)\n" // enable CP11 CP11
		  "str r1, [r0]\n" // write back to CPACR
		  "dsb\n"
		  "isb\n");

	/* Enable configurable fault handlers: */
	armv7e_m::mmreg::SCB::SCB.SHCSR.bits.MEMFAULTENA = 1;
	armv7e_m::mmreg::SCB::SCB.SHCSR.bits.BUSFAULTENA = 1;
	armv7e_m::mmreg::SCB::SCB.SHCSR.bits.USGFAULTENA = 1;

	/* Copy the data segment initializers from flash to SRAM */
	{
		uint32_t *src_fast = &_data_fast_lma_start;
		for(uint32_t *dst = &_data_fast_vma_start; dst < &_data_fast_vma_end;) {
			*dst++ = *src_fast++;
		}
		uint32_t *src_regular1 = &_data_regular1_lma_start;
		for(uint32_t *dst = &_data_regular1_vma_start; dst < &_data_regular1_vma_end;) {
			*dst++ = *src_regular1++;
		}
		uint32_t *src_regular2 = &_data_regular2_lma_start;
		for(uint32_t *dst = &_data_regular2_vma_start; dst < &_data_regular2_vma_end;) {
			*dst++ = *src_regular2++;
		}
		uint32_t *src_regular3 = &_data_regular3_lma_start;
		for(uint32_t *dst = &_data_regular3_vma_start; dst < &_data_regular3_vma_end;) {
			*dst++ = *src_regular3++;
		}
	}

	/* Zero fill the bss segment */
	__asm("ldr r0, =_bss_fast_start\n"
		  "ldr r1, =_bss_fast_end\n"
		  "mov r2, #0\n"
		  ".thumb_func\n"
		  "bss_fast_loop:\n"
		  "cmp r0, r1\n"
		  "it lt\n"
		  "strlt r2, [r0], #4\n"
		  "blt bss_fast_loop");
	__asm("ldr r0, =_bss_regular1_start\n"
		  "ldr r1, =_bss_regular1_end\n"
		  "mov r2, #0\n"
		  ".thumb_func\n"
		  "bss_regular1_loop:\n"
		  "cmp r0, r1\n"
		  "it lt\n"
		  "strlt r2, [r0], #4\n"
		  "blt bss_regular1_loop");
	__asm("ldr r0, =_bss_regular2_start\n"
		  "ldr r1, =_bss_regular2_end\n"
		  "mov r2, #0\n"
		  ".thumb_func\n"
		  "bss_regular2_loop:\n"
		  "cmp r0, r1\n"
		  "it lt\n"
		  "strlt r2, [r0], #4\n"
		  "blt bss_regular2_loop");
	__asm("ldr r0, =_bss_regular3_start\n"
		  "ldr r1, =_bss_regular3_end\n"
		  "mov r2, #0\n"
		  ".thumb_func\n"
		  "bss_regular3_loop:\n"
		  "cmp r0, r1\n"
		  "it lt\n"
		  "strlt r2, [r0], #4\n"
		  "blt bss_regular3_loop");

	/* Call static constructors

	https://stackoverflow.com/questions/15265295/understanding-the-libc-init-array
	*/
	__libc_init_array();

	/* Call the application's entry point */
	main();
}


/*

https://stackoverflow.com/questions/13734745/why-do-i-have-an-undefined-reference-to-init-in-libc-init-array

*/
extern "C" void _init(void) { ; }

void nvic::nmiHandler() {
	nvic::defaultHandler();
}

void nvic::sysTickISR() {
	nvic::defaultHandler();
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
Useful articles:
	https://interrupt.memfault.com/blog/cortex-m-hardfault-debug
	https://www.segger.com/downloads/application-notes/AN00016
	https://www.freertos.org/Debugging-Hard-Faults-On-Cortex-M-Microcontrollers.html
	https://www.iar.com/knowledge/support/technical-notes/debugger/debugging-a-hardfault-on-cortex-m/
	https://www.embeddedrelated.com/showarticle/912.php

When a hard fault exception occurs, the CPU saves the following register on the current stack,
which can be either main stack or process stack:
				<previous> <-- SP points here before exception
	SP + 0x1C	xPSR
	SP + 0x18	PC
	SP + 0x14	LR
	SP + 0x10	R12
	SP + 0x0C	R3
	SP + 0x08	R2
	SP + 0x04	R1
	SP + 0x00	R0 <-- SP points here after exception

When entering an exception handler, the LR register is updated to a special value
called EXC_RETURN with the upper 28 bits all set to 1. This value, when loaded into
the PC at the end of the exception handler execution, will cause the CPU to perform
an exception return sequence.
Bit 2 of the LR register determines the used stack before entering the exception:
	0 = main stack
	1 = process stack

Encoding of The EXC_RETURN Value
EXC_RETURN 5 low-order bits:
				Stack Pointer	Frame Type (extended = uses floating-point state)
												Execution Mode (where to return)
11101 (0x1D)	Process stack	Basic frame		Thread mode
11001 (0x19)	Main stack		Basic frame		Thread mode
10001 (0x11)	Main stack		Basic frame		Handler mode
01101 (0x0D)	Process stack	Extended frame	Thread mode
01001 (0x09)	Main stack		Extended frame	Thread mode
00001 (0x01)	Main stack		Extended frame	Handler mode

GDB:
	p/x $lr&(1<<2)
	p/a *(uint32_t[8] *)$psp

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
	armv7e_m::mmreg::SCB::CFSR cfsr;
	cfsr.word = armv7e_m::mmreg::SCB::SCB.CFSR.word;
	(void)cfsr;
	FrameBasic &frameBasic = *(FrameBasic *)sp;
	(void)frameBasic;
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

/*
MemManage: detects memory access violations to regions that are defined in the Memory
Management Unit (MPU); for example, code execution from a memory region with read/write access
only.
*/
void nvic::memManageHandler() {
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
	armv7e_m::mmreg::SCB::CFSR cfsr;
	cfsr.word = armv7e_m::mmreg::SCB::SCB.CFSR.word;
	(void)cfsr;
	FrameBasic &frameBasic = *(FrameBasic *)sp;
	(void)frameBasic;
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

/*
BusFault: detects memory access errors on instruction fetch, data read/write, interrupt vector fetch,
and register stacking (save/restore) on interrupt (entry/exit).

Cache maintenance operations can result in an asynchronous (imprecise) BusFault.

Due to the design in the bus interface, the bus error in Cortex-M7 can be imprecise
if the memory operation is a write to a strongly ordered memory region. In such case,
the stacked PC could be showing a different context (for example, an IRQ handler that was triggered
shortly after the buffered write took place). As a result, on Cortex-M7 the BusFault handler
cannot rely on stacked PC to determine the fault location if the BusFault is asynchronous.

*/
void nvic::busFaultHandler() {
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
	armv7e_m::mmreg::SCB::CFSR cfsr;
	cfsr.word = armv7e_m::mmreg::SCB::SCB.CFSR.word;
	(void)cfsr;
	FrameBasic &frameBasic = *(FrameBasic *)sp;
	(void)frameBasic;
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

/*
UsageFault: detects execution of undefined instructions, unaligned memory access for load/store
multiple. When enabled, divide-by-zero and other unaligned memory accesses are detected.
*/
void nvic::usageFaultHandler() {
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
	armv7e_m::mmreg::SCB::CFSR cfsr;
	cfsr.word = armv7e_m::mmreg::SCB::SCB.CFSR.word;
	(void)cfsr;
	FrameBasic &frameBasic = *(FrameBasic *)sp;
	(void)frameBasic;
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

// void SVC_Handler() {
//     while(1) {
//         __asm("nop");
//     }
// }

void nvic::debugMonHandler() {
	nvic::defaultHandler();
}


#if 0
static void SystemInit(void) {

		/* Enable the floating-point unit. Any configuration of the
		floating-point unit must be done here prior to it being enabled */
		HWREG(0xE000ED88) = ((HWREG(0xE000ED88) & ~0x00F00000) | 0x00F00000);

		/*------- Reset the RCC clock configuration to the default reset state -------*/
		/* Set HSION bit */
		RCC->CR |= 0x00000001;
		/* Reset CFGR register */
		RCC->CFGR = 0x00000000;
		/* Reset HSEON, CSSON , CSION,RC48ON, CSIKERON PLL1ON, PLL2ON and PLL3ON bits */
		RCC->CR &= (uint32_t)0xEAF6ED7F;
		/* Reset D1CFGR register */
		RCC->D1CFGR = 0x00000000;
		/* Reset D2CFGR register */
		RCC->D2CFGR = 0x00000000;
		/* Reset D3CFGR register */
		RCC->D3CFGR = 0x00000000;
		/* Reset PLLCKSELR register */
		RCC->PLLCKSELR = 0x00000000;
		/* Reset PLLCFGR register */
		RCC->PLLCFGR = 0x00000000;
		/* Reset PLL1DIVR register */
		RCC->PLL1DIVR = 0x00000000;
		/* Reset PLL1FRACR register */
		RCC->PLL1FRACR = 0x00000000;
		/* Reset PLL2DIVR register */
		RCC->PLL2DIVR = 0x00000000;
		/* Reset PLL2FRACR register */
		RCC->PLL2FRACR = 0x00000000;
		/* Reset PLL3DIVR register */
		RCC->PLL3DIVR = 0x00000000;
		/* Reset PLL3FRACR register */
		RCC->PLL3FRACR = 0x00000000;
		/* Reset HSEBYP bit */
		RCC->CR &= (uint32_t)0xFFFBFFFF;
		/* Disable all interrupts */
		RCC->CIER = 0x00000000;

		/* Change the switch matrix read issuing capability to 1 for the AXI SRAM target (Target 7) */
		HWREG(0x51008108) = 0x000000001;
}
#endif