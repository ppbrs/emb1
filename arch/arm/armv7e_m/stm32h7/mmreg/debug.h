#pragma once

#include <cstdint>

namespace stm32h7 {
namespace mmreg {
namespace DEBUG {

namespace SWO {

struct CODRBits {
	uint32_t PRESCALER : 13; // SWO baud rate scaling
	uint32_t reserved0 : (32 - 13); // must be kept at reset value.
};
union CODRUnion {
	uint32_t word;
	CODRBits bits;
};
static_assert(sizeof(CODRUnion) == 4);

struct SPPRBits {
	uint32_t PPROT : 2; // Pin protocol
	uint32_t reserved0 : (32 - 2); // must be kept at reset value.

	static constexpr uint32_t PPROTManchester = 1u;
	static constexpr uint32_t PPROTNRZ = 2u;
};
union SPPRUnion {
	uint32_t word;
	SPPRBits bits;
};
static_assert(sizeof(SPPRUnion) == 4);


struct SWO {
	uint32_t reserved0[0x10 / sizeof(uint32_t)];
	CODRUnion CODR;
	uint32_t reserved1[(0xF0 - 0x14) / sizeof(uint32_t)];
	SPPRUnion SPPR;
	uint32_t reserved2[(0xFB0 - 0xF4) / sizeof(uint32_t)];
	uint32_t LAR;
	uint32_t reserved3[(0x1000 - 0xFB4) / sizeof(uint32_t)];
};
static_assert(sizeof(SWO) == 0x1000);
extern volatile struct SWO SWO;
}

namespace SWTF {

struct CTRLBits {
	uint32_t ENS0 : 1; // Slave port S0 enable
	uint32_t reserved0 : 7; // must be kept at reset value.
	uint32_t MIN_HOLD_TIME : 4; // Number of transactions between arbitrations.
	uint32_t reserved1 : (32 - 12); // must be kept at reset value.
};
union CTRLUnion {
	uint32_t word;
	CTRLBits bits;
};
static_assert(sizeof(CTRLUnion) == 4);

struct SWTF {
	CTRLUnion CTRL;
	uint32_t reserved0[(0xFB0 - 0x04) / sizeof(uint32_t)];
	uint32_t LAR;
	uint32_t reserved1[(0x1000 - 0xFB4) / sizeof(uint32_t)];
};
static_assert(sizeof(SWTF) == 0x1000);
extern volatile struct SWTF SWTF;
}

namespace DBGMCU {

struct CRBits {
	uint32_t DBGSLEEP_D1 : 1;
	uint32_t DBGSTOP_D1 : 1;
	uint32_t DBGSTBY_D1 : 1;
	uint32_t reserved0 : (20 - 3);
	uint32_t TRACECLKEN : 1;
	uint32_t D1DBGCKEN : 1;
	uint32_t D3DBGCKEN : 1;
	uint32_t reserved1 : (28 - 23);
	uint32_t TRGOEN : 1;
	uint32_t reserved2 : (32 - 29);
};

union CRUnion {
	uint32_t word;
	CRBits bits;
};


struct DBGMCU {
	uint32_t IDC;
	CRUnion CR;
	uint32_t reserved0[(0x34 - 0x08) / sizeof(uint32_t)];
	uint32_t APB3FZ;
	uint32_t reserved1[(0x3C - 0x38) / sizeof(uint32_t)];
	uint32_t APB1LF;
	uint32_t reserved2[(0x4C - 0x40) / sizeof(uint32_t)];
	uint32_t APB2FZ;
	uint32_t reserved3[(0x54 - 0x50) / sizeof(uint32_t)];
	uint32_t APB4FZ;
};
static_assert(sizeof(DBGMCU) == 0x58);
extern volatile struct DBGMCU DBGMCU;
}

}
}
}
