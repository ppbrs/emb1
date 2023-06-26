#pragma once

#include <cstdint>

namespace armv6_m {
namespace mmreg {
namespace SysTick {

/* SysTick Control and Status Register */
struct CSRBits {
	uint32_t ENABLE : 1;
	uint32_t TICKINT : 1;
	uint32_t CLKSOURCE : 1;
	uint32_t reserved1 : 13;
	uint32_t COUNTFLAG : 1;
	uint32_t reserved2 : 15;
};
static_assert(sizeof(CSRBits) == 4u);
union CSR {
	uint32_t word;
	CSRBits bits;
};
static_assert(sizeof(CSR) == 4u);

/* SysTick Reload Value Register */

/* SysTick Current Value Register */

/* SysTick Calibration Value Register */
struct CALIBBits {
	uint32_t TENMS : 24;
	uint32_t reserved : 6;
	uint32_t SKEW : 1;
	uint32_t NOREF : 1;
};
static_assert(sizeof(CALIBBits) == 4u);
union CALIB {
	uint32_t word;
	CALIBBits bits;
};
static_assert(sizeof(CALIB) == 4u);


struct SYST {
	union CSR CSR;
	uint32_t RVR;
	uint32_t CVR;
	union CALIB CALIB;
};
static_assert(sizeof(SYST) == (0xE000E020 - 0xE000E010));

extern volatile SYST SYST;
}
}
}
