#pragma once

#include <cstdint>

namespace stm32h7 {
namespace mmreg {
namespace USART {


struct USART {
	uint32_t CR1;
	uint32_t CR2;
	uint32_t CR3;
	uint32_t BRR;
	uint32_t GTPR;
	uint32_t RTOR;
	uint32_t RQR;
	uint32_t ISR;
	uint32_t ICR;
	uint32_t RDR;
	uint32_t TDR;
	uint32_t PRESC;
};
static_assert(sizeof(USART) == 0x30);

extern volatile struct USART USART1;
extern volatile struct USART USART2;
extern volatile struct USART USART3;
extern volatile struct USART UART4;
extern volatile struct USART UART5;
extern volatile struct USART USART6;
extern volatile struct USART UART7;
extern volatile struct USART UART8;
}
}
}
