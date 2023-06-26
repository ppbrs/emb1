#pragma once

#include <cstdint>

namespace armv7e_m {
namespace mmreg {
namespace cache {
struct Cache {
	uint32_t ICIALLU;
	uint32_t reserved;
	const volatile void *ICIMVAU;
	const volatile void *DCIMVAC;
	uint32_t DCISW;
	const volatile void *DCCMVAU;
	const volatile void *DCCMVAC;
	uint32_t DCCSW;
	const volatile void *DCCIMVAC;
	uint32_t DCCISW;
	uint32_t BPIALL;
};
#if defined(__arm__)
static_assert(sizeof(Cache) == 0x7C - 0x50);
#endif

extern volatile Cache cache;
}
}
}
