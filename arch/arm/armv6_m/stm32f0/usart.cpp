#include "usart.h"
#include "arch/arm/armv6_m/mmreg/nvic.h"
#include "arch/arm/armv6_m/stm32f0/mmreg/usart.h"
#include "arch/arm/armv6_m/stm32f0/nvic.h"
#include "arch/arm/stm32/mmreg/gpio.h"
#include "if/mcu/mmreg.h"
#include "if/mcu/nvic.h"
#include <array>

namespace {
std::array<void (*)(uint8_t), 2> isrRxFuncArr = {};
}

// Partial specialization of usart::configure<T>:
template<>
void usart::configure<UsartRegsF0, GpioRegsF0>(const UsartDefF0 &usartDef) {
	pio::configure(usartDef.txPioDef);
	pio::configure(usartDef.rxPioDef);

	if(usartDef.initFunc) {
		usartDef.initFunc();
	}

	if(&usartDef.regs == &stm32f0::mmreg::USART::USART1) {
		isrRxFuncArr[0] = usartDef.isrRxFunc;
	} else if(&usartDef.regs == &stm32f0::mmreg::USART::USART2) {
		isrRxFuncArr[1] = usartDef.isrRxFunc;
	} else {
		// fatal error
	}

	// 48000000 / 115200 = 417
	usartDef.regs.BRR = 0x1A1;

	stm32f0::mmreg::USART::CR1Union cr1 = {};
	cr1.bits.TE = 1;
	cr1.bits.RE = 1;
	cr1.bits.UE = 1;
	cr1.bits.RXNEIE = 1;
	usartDef.regs.CR1.word = cr1.word;

	using armv6_m::nvic::InterruptNumber;
	using mmreg::setBitsMasked;
	namespace NVIC = armv6_m::mmreg::NVIC;
	uint32_t irqNum = InterruptNumber::USART2;
	uint32_t irqPrio = ((1 << 2) - 1) << (8 - 2); // lowest
	setBitsMasked(NVIC::NVIC.IPR[irqNum / 4], NVIC::IPRMask, irqPrio, 8 * (irqNum % 4));
	setBitsMasked(NVIC::NVIC.ISER, 1, 1, InterruptNumber::USART2);
}

void usart::isr1() {
	using stm32f0::mmreg::USART::USART1;
	auto &isr = USART1.ISR;
	while(isr.bits.RXNE) {
		volatile uint8_t byte = USART1.RDR;
		if(isrRxFuncArr[0]) {
			isrRxFuncArr[1](byte);
		}
	}
}

void usart::isr2() {
	using stm32f0::mmreg::USART::USART2;
	auto &isr = USART2.ISR;
	while(isr.bits.RXNE) {
		volatile uint8_t byte = USART2.RDR;
		if(isrRxFuncArr[1]) {
			isrRxFuncArr[1](byte);
		}
	}
}
