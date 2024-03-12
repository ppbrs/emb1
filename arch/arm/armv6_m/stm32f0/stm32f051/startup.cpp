#include "../../../../../if/mcu/chrono.h"
#include "../../../../../if/mcu/nvic.h"
#include "../../../../../if/mcu/tick.h"
#include <cstdint>

#if __STDC_HOSTED__ > 0
#error __STDC_HOSTED__ is not 0
#endif

extern int main();
extern "C" void Default_Handler();
extern "C" void Reset_Handler();
void NMI_Handler();
void HardFault_Handler();
void SVC_Handler();
void PendSV_Handler();
void SysTick_Handler();
void WWDG_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void RTC_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void RCC_CRS_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void EXTI0_1_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void EXTI2_3_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void EXTI4_15_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void TSC_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel2_3_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel4_5_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void ADC1_COMP_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void TIM14_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void TIM15_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void TIM16_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void TIM17_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void I2C1_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void I2C2_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler() __attribute__((weak, alias("Default_Handler")));
void CEC_CAN_IRQHandler() __attribute__((weak, alias("Default_Handler")));

/* Highest address of the user mode stack */
extern const volatile uint32_t _main_stack_end;
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
__attribute__((section(".isr_vector"), used)) void (*const g_pfnVectors[])(void) = {
	/* Initial SP value */
	((void (*)(void))(&_main_stack_end)),
	/* On reset, the processor loads the PC with the value of the reset vector, at address
	0x00000004. Bit[0] of the value is loaded into the EPSR T-bit at reset and must be 1. */
	Reset_Handler, // Exception 1, priority = -3 (the highest)
	NMI_Handler, // Exception 2, IRQ -14, priority = -2
	HardFault_Handler, // Exception 3, IRQ -13, priority = -1
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	nvic::svcISR, /*SVC_Handler,*/ // Exception 11, IRQ -5, priority is configurable
	0,
	0,
	nvic::pendsvISR, /*PendSV_Handler,*/ // Exception 14, IRQ -2, priority is configurable
	tick::sysTickISR, // Exception 15, IRQ -1, priority is configurable

	/* External Interrupts (IRQ0 ... IRQ31) */
	WWDG_IRQHandler, // IRQ0
	PVD_IRQHandler,
	RTC_IRQHandler,
	FLASH_IRQHandler,
	RCC_CRS_IRQHandler,
	EXTI0_1_IRQHandler,
	EXTI2_3_IRQHandler,
	EXTI4_15_IRQHandler,
	TSC_IRQHandler,
	DMA1_Channel1_IRQHandler,
	DMA1_Channel2_3_IRQHandler, // IRQ10
	DMA1_Channel4_5_IRQHandler,
	ADC1_COMP_IRQHandler,
	TIM1_BRK_UP_TRG_COM_IRQHandler,
	TIM1_CC_IRQHandler,
	chrono::steady_clock::overflow, /*TIM2_IRQHandler*/ // IRQ15
	chrono::high_resolution_clock::overflow, /*TIM3_IRQHandler*/ // IRQ16
	TIM6_DAC_IRQHandler,
	0,
	TIM14_IRQHandler,
	TIM15_IRQHandler, // IRQ20
	TIM16_IRQHandler,
	TIM17_IRQHandler,
	I2C1_IRQHandler,
	I2C2_IRQHandler,
	SPI1_IRQHandler,
	SPI2_IRQHandler,
	USART1_IRQHandler,
	USART2_IRQHandler,
	0,
	CEC_CAN_IRQHandler, // IRQ30
	0, // IRQ31
};
static_assert(sizeof(g_pfnVectors) == 4 * (1 + 15 + 32));

void Default_Handler() {
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

void Reset_Handler() {
	// TODO
	/* Set stack pointer */
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

void NMI_Handler() {
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
void HardFault_Handler() {
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

void SVC_Handler() {
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

void PendSV_Handler() {
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

void SysTick_Handler() {
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}
