#pragma once

#include <cstdint>

namespace armv7e_m {
namespace mmreg {
namespace SCB {

struct FPCCRBits {
	uint32_t LSPACT : 1;
	uint32_t USER : 1;
	uint32_t reserved1 : 1;
	uint32_t THREAD : 1;
	uint32_t HFRDY : 1;
	uint32_t MMRDY : 1;
	uint32_t BFRDY : 1;
	uint32_t reserved2 : 1;
	uint32_t MONRDY : 1;
	uint32_t reserved3 : 21;
	uint32_t LSPEN : 1;
	uint32_t ASPEN : 1;
};
static_assert(sizeof(FPCCRBits) == 4U);

union FPCCR {
	uint32_t word;
	FPCCRBits bits;
};

struct FPDSCRBits {
	uint32_t reserved1 : 22;
	uint32_t RMode : 2;
	uint32_t FZ : 1;
	uint32_t DN : 1;
	uint32_t AHP : 1;
	uint32_t reserved2 : 5;
};
static_assert(sizeof(FPDSCRBits) == 4U);

union FPDSCR {
	uint32_t word;
	FPDSCRBits bits;
};

struct FP {
	union FPCCR CCR;
	void *CAR;
	union FPDSCR DSCR;
};
#if defined(__arm__)
static_assert(sizeof(FP) == 12U);
#endif

extern volatile FP FP;
}
}
}
