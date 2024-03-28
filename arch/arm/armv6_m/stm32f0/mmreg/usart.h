#pragma once

#include <cstdint>

namespace stm32f0 {
namespace mmreg {
namespace USART {

// USART control register 1 (USART_CR1)
union CR1Union {
	uint32_t word;
};
// USART control register 2 (USART_CR2)
union CR2Union {
	uint32_t word;
};
// USART control register 3 (USART_CR3)
union CR3Union {
	uint32_t word;
};
// USART baud rate register (USART_BRR)
union BRRUnion {
	uint32_t word;
};
// USART guard time and prescaler register (USART_GTPR)
union GTPRUnion {
	uint32_t word;
};
// USART receiver timeout register (USART_RTOR)
union RTORUnion {
	uint32_t word;
};
// USART request register (USART_RQR)
union RQRUnion {
	uint32_t word;
};
// USART interrupt and status register (USART_ISR)
union ISRUnion {
	uint32_t word;
};
// USART interrupt flag clear register (USART_ICR)
union ICRUnion {
	uint32_t word;
};

struct USART {
	CR1Union CR1;
	CR1Union CR2;
	CR1Union CR3;
	BRRUnion BRR;
	GTPRUnion GTPR;
	RTORUnion RTOR;
	RQRUnion RQR;
	ISRUnion ISR;
	ICRUnion ICR;

	uint8_t RDR;
	uint8_t reserved0[3];
	uint8_t TDR;
	uint8_t reserved1[3];
};
static_assert(sizeof(USART) == 0x2Cu);
extern volatile struct USART USART1;
extern volatile struct USART USART2;
} // USART
} // mmreg
} // stm32f0
