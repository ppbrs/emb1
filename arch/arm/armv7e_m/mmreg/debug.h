#pragma once

#include <cstdint>

namespace armv7e_m {
namespace mmreg {
namespace DEBUG {

/* Debug Halting Control and Status Register */
struct DHCSRBits {
	uint32_t C_DEBUGEN : 1;
	uint32_t C_HALT : 1;
	uint32_t C_STEP : 1;
	uint32_t C_MASKINTS : 1;
	uint32_t reserved1 : 1;
	uint32_t C_SNAPSTALL : 1;
	uint32_t reserved2 : 10;
	uint32_t S_REGRDY : 1;
	uint32_t S_HALT : 1;
	uint32_t S_SLEEP : 1;
	uint32_t S_LOCKUP : 1;
	uint32_t reserved3 : 4;
	uint32_t S_RETIRE_ST : 1;
	uint32_t S_RESET_ST : 1;
	uint32_t reserved4 : 6;
};
static_assert(sizeof(DHCSRBits) == 4U);
union DHCSRUnion {
	uint32_t word;
	DHCSRBits bits;
};

/* Debug Core Register Selector Register */
struct DCRSRBits {
	uint32_t REGSEL : 7;
	uint32_t reserved1 : 9;
	uint32_t REGWnR : 1;
	uint32_t reserved2 : 15;
};
static_assert(sizeof(DCRSRBits) == 4U);
union DCRSRUnion {
	uint32_t word;
	DCRSRBits bits;
};

/* Debug Exception and Monitor Control Register */
struct DEMCRBits {
	uint32_t VC_CORERESET : 1;
	uint32_t reserved1 : 3;
	uint32_t VC_MMERR : 1;
	uint32_t VC_NOCPERR : 1;
	uint32_t VC_CHKERR : 1;
	uint32_t VC_STATERR : 1;
	uint32_t VC_BUSERR : 1;
	uint32_t VC_INTERR : 1;
	uint32_t VC_HARDERR : 1;
	uint32_t reserved2 : 5;
	uint32_t MON_EN : 1;
	uint32_t MON_PEND : 1;
	uint32_t MON_STEP : 1;
	uint32_t MON_REQ : 1;
	uint32_t reserved3 : 4;
	uint32_t TRCENA : 1; // bit 24
	uint32_t reserved4 : 7;
};
static_assert(sizeof(DEMCRBits) == 4U);
union DEMCRUnion {
	uint32_t word;
	DEMCRBits bits;
};

struct DEBUG {
	union DHCSRUnion DHCSR;
	union DCRSRUnion DCRSR;
	uint32_t DCRDR;
	union DEMCRUnion DEMCR;
};
static_assert(sizeof(DEBUG) == 0xE000EE00 - 0xE000EDF0);

extern volatile DEBUG DEBUG;
}
}
}
