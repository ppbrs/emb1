#pragma once

#include <cstdint>

namespace armv6_m {
namespace mmreg {
namespace NVIC {
struct NVIC {
	uint32_t ISER;
	uint32_t pad1[31];
	uint32_t ICER;
	uint32_t pad2[31];
	uint32_t ISPR;
	uint32_t pad3[31];
	uint32_t ICPR;
	uint32_t pad4[(0xE400 - 0xE284) / 4];
	uint32_t IPR[8];
};
static constexpr uint32_t IPRMask = 0xFF;

static_assert(sizeof(NVIC) == (0xE000E420 - 0xE000E100));

extern volatile NVIC NVIC;

}
}
}
