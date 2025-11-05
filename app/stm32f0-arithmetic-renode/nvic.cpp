#include "if/mcu/nvic.h"
#include "if/mcu/tick.h"

extern "C" void resetHandler();
namespace nvic {
namespace {
__attribute__((section(".exception_vectors"), used)) void (*const exceptionVectors[])(void) = {
	/* On reset, the processor loads the PC with the value of the reset vector, at address
	0x00000004. Bit[0] of the value is loaded into the EPSR T-bit at reset and must be 1. */
	resetHandler, // Exception 1, priority = -3 (the highest)
	nvic::nmiHandler, // Exception 2, IRQ -14, priority = -2
	nvic::hardFaultHandler, // Exception 3, IRQ -13, priority = -1
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nvic::svcISR, // Exception 11, IRQ -5, priority is configurable
	nullptr,
	nullptr,
	nvic::pendsvISR, // Exception 14, IRQ -2, priority is configurable
	tick::sysTickISR, // Exception 15, IRQ -1, priority is configurable
};
static_assert(sizeof(exceptionVectors) == 4 * 15);

__attribute__((section(".interrupt_vectors"), used)) void (*const interruptVectors[])(void) = {
	/* External Interrupts (IRQ0 ... IRQ31) */
	nvic::defaultHandler, // WWDG_IRQHandler, // IRQ0
	nvic::defaultHandler, // PVD_IRQHandler,
	nvic::defaultHandler, // RTC_IRQHandler,
	nvic::defaultHandler, // FLASH_IRQHandler,
	nvic::defaultHandler, // RCC_CRS_IRQHandler,
	nvic::defaultHandler, // EXTI0_1_IRQHandler,
	nvic::defaultHandler, // EXTI2_3_IRQHandler,
	nvic::defaultHandler, // EXTI4_15_IRQHandler,
	nvic::defaultHandler, // TSC_IRQHandler,
	nvic::defaultHandler, // DMA1_Channel1_IRQHandler,
	nvic::defaultHandler, // DMA1_Channel2_3_IRQHandler, // IRQ10
	nvic::defaultHandler, // DMA1_Channel4_5_IRQHandler,
	nvic::defaultHandler, // ADC1_COMP_IRQHandler,
	nvic::defaultHandler, // TIM1_BRK_UP_TRG_COM_IRQHandler,
	nvic::defaultHandler, // TIM1_CC_IRQHandler,
	nvic::defaultHandler,
	/*TIM2_IRQHandler*/ // IRQ15
	nvic::defaultHandler,
	/*TIM3_IRQHandler*/ // IRQ16
	nvic::defaultHandler, // TIM6_DAC_IRQHandler,
	nullptr,
	nvic::defaultHandler, // TIM14_IRQHandler,
	nvic::defaultHandler, // TIM15_IRQHandler, // IRQ20
	nvic::defaultHandler, // TIM16_IRQHandler,
	nvic::defaultHandler, // TIM17_IRQHandler,
	nvic::defaultHandler, // I2C1_IRQHandler,
	nvic::defaultHandler, // I2C2_IRQHandler,
	nvic::defaultHandler, // SPI1_IRQHandler,
	nvic::defaultHandler, // SPI2_IRQHandler,
	nvic::defaultHandler, // USART1_IRQHandler,
	nvic::defaultHandler, // USART2_IRQHandler,
	nullptr,
	nvic::defaultHandler, // CEC_CAN_IRQHandler, // IRQ30
	nullptr, // IRQ31
};
static_assert(sizeof(interruptVectors) == 4 * 32);
}
}
