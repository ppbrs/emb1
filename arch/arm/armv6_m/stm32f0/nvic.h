#pragma once

namespace armv6_m {
namespace nvic {
enum InterruptNumber : uint8_t {
	WWDG, // IRQ0
	PVD,
	RTC,
	FLASH,
	RCC_CRS,
	EXTI0_1,
	EXTI2_3,
	EXTI4_15,
	TSC,
	DMA1_Channel1,
	DMA1_Channel2_3, // IRQ10
	DMA1_Channel4_5,
	ADC1_COMP,
	TIM1_BRK_UP_TRG_COM,
	TIM1_CC,
	TIM2, // IRQ15
	TIM3, // IRQ16
	TIM6_DAC,
	RESERVED_IRQ18,
	TIM14,
	TIM15, // IRQ20
	TIM16,
	TIM17,
	I2C1,
	I2C2,
	SPI1,
	SPI2,
	USART1,
	USART2,
	RESERVED_IRQ29,
	CEC_CAN_IRQHandler, // IRQ30
	RESERVED_IRQ31,
	NUMBER,
};
static_assert(InterruptNumber::NUMBER == 32);

}
}
