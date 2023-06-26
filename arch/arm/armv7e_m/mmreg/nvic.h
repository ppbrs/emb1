#pragma once

#include <cstdint>

namespace armv7e_m {
namespace mmreg {
namespace NVIC {
struct NVIC {
	uint32_t ISER[8]; // Interrupt Set-enable Registers, 1 bit per interrupt
	uint32_t reserved1[24];
	uint32_t ICER[8];
	uint32_t reserved2[24];
	uint32_t ISPR[8];
	uint32_t reserved3[24];
	uint32_t ICPR[8];
	uint32_t reserved4[24];
	uint32_t IABR[8];
	uint32_t reserved5[56];
	uint8_t IPR[240];
};
static_assert(sizeof(NVIC) == (0xE4F0 - 0xE100));

extern volatile NVIC NVIC;

extern volatile uint32_t STIR;
}
}
}
