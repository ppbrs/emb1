#include "usart.h"
#include "arch/arm/armv6_m/mmreg/nvic.h"
#include "arch/arm/armv6_m/stm32f0/mmreg/usart.h"
#include "arch/arm/armv6_m/stm32f0/nvic.h"
#include "arch/arm/stm32/mmreg/gpio.h"
#include "if/mcu/mmreg.h"
#include "if/mcu/nvic.h"
#include <array>

namespace usart {
namespace {
std::array<ConsumeByteFromISR, 2> consumeByteFromISRArr = {};
std::array<GetNextByte, 2> getNextByteArr = {};

void notifyDataReady1() {
	using namespace stm32f0::mmreg::USART;
	mmreg::setBits(USART1.CR1.word, CR1Bits::TXEIEMask);
}
void notifyDataReady2() {
	using namespace stm32f0::mmreg::USART;
	mmreg::setBits(USART2.CR1.word, CR1Bits::TXEIEMask);
}

}
}

// Partial specialization of usart::configure<T>:
template<>
void usart::configure<UsartRegsF0, GpioRegsF0>(const UsartDefF0 &usartDef) {
	pio::configure(usartDef.txPioDef);
	pio::configure(usartDef.rxPioDef);

	if(&usartDef.regs == &stm32f0::mmreg::USART::USART1) {
		usartDef.initFunc(notifyDataReady1);
		consumeByteFromISRArr[0] = usartDef.consumeByteFromISR;
		getNextByteArr[0] = usartDef.getNextByte;
	} else if(&usartDef.regs == &stm32f0::mmreg::USART::USART2) {
		usartDef.initFunc(notifyDataReady2);
		consumeByteFromISRArr[1] = usartDef.consumeByteFromISR;
		getNextByteArr[1] = usartDef.getNextByte;
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
	mmreg::setBitsMasked(NVIC::NVIC.IPR[irqNum / 4], NVIC::IPRMask, irqPrio, 8 * (irqNum % 4));
	mmreg::setBits(NVIC::NVIC.ISER, 1, InterruptNumber::USART2);
}

void usart::isr1() {
	using stm32f0::mmreg::USART::USART1;
	auto &isr = USART1.ISR;
	while(isr.bits.RXNE) {
		volatile uint8_t byte = USART1.RDR;
		if(consumeByteFromISRArr[0]) {
			consumeByteFromISRArr[1](byte);
		}
	}
}

void usart::isr2() {
	using stm32f0::mmreg::USART::USART2;
	auto &isr = USART2.ISR;

	if(isr.bits.TXE) {
		std::optional<uint8_t> nextByte = getNextByteArr[1]();
		if(nextByte.has_value()) {
			USART2.TDR = nextByte.value();
		} else {
			using namespace stm32f0::mmreg::USART;
			mmreg::clearBits(USART2.CR1.word, CR1Bits::TXEIEMask);
		}
	}

	while(isr.bits.RXNE) {
		volatile uint8_t byte = USART2.RDR;
		if(consumeByteFromISRArr[1]) {
			consumeByteFromISRArr[1](byte);
		}
	}
}
