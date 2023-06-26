#pragma once

#include <cstdint>

namespace armv7e_m {
namespace mmreg {
namespace SysTick {
struct CSRBits {
	uint32_t ENABLE : 1;
	uint32_t TICKINT : 1;
	uint32_t CLKSOURCE : 1;
	uint32_t reserved1 : 13;
	uint32_t COUNTFLAG : 1;
	uint32_t reserved2 : 15;
};
static_assert(sizeof(CSRBits) == 4U);

union CSR {
	uint32_t word;
	CSRBits bits;
};

struct CALIBBits {
	uint32_t TENMS : 24;
	uint32_t reserved : 6;
	uint32_t SKEW : 1;
	uint32_t NOREF : 1;
};
static_assert(sizeof(CALIBBits) == 4U);

union CALIB {
	uint32_t word;
	CALIBBits bits;
};

struct SYST {
	union CSR CSR;
	uint32_t RVR;
	uint32_t CVR;
	union CALIB CALIB;
};
static_assert(sizeof(SYST) == 16U);

extern volatile SYST SYST;
}
}
}
