#pragma once

#include <cstdint>

namespace armv6_m {
namespace mmreg {
namespace SCB {
struct SCB {
	uint32_t CPUID;
	uint32_t ICSR;
	uint32_t reserved1;
	uint32_t AIRCR;
	uint32_t SCR;
	uint32_t CCR;
	uint32_t reserved2;
	uint32_t SHPR2;
	uint32_t SHPR3;
};
static_assert(sizeof(SCB) == (0xE000ED24 - 0xE000ED00));

extern volatile SCB SCB;

extern volatile uint32_t STIR;
}
}
}
