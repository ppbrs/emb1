#pragma once

#include <cstddef>
#include <cstdint>

namespace armv7e_m {
namespace mmreg {
namespace ITM {

/* Stimulus Port registers */
struct STIMRead {
	uint32_t FIFOREADY : 1; /* Stimulus port can accept new write data when this bit is 1 */
	uint32_t reserved : 31;
};
union STIMWrite {
	uint8_t u8;
	uint16_t u16;
	uint32_t u32;
};
static_assert(sizeof(STIMRead) == 4U);
static_assert(sizeof(STIMWrite) == 4U);
union STIMUnion {
	STIMRead read;
	STIMWrite write;
};
static_assert(sizeof(STIMUnion) == 4U);

struct TPRBits {
	uint32_t PRIVMASK : 4; /* Enable unprivileged access to ITM stimulus ports */
	uint32_t reserved : 28;
};

static_assert(sizeof(TPRBits) == 4U);

struct TCRBits {
	uint32_t ITMENA : 1; /* ITM enable */
	uint32_t TSENA : 1; /* Local timestamp generation enable */
	uint32_t SYNCENA : 1; /* Synchronization packet transmission enable */
	uint32_t TXENA : 1; /* Hardware event packet forwarding enable */
	uint32_t SWOENA : 1; /* Asynchronous clocking enable for the timestamp counter (read-only) */
	uint32_t reserved0 : 3;
	uint32_t TSPRESCALE : 2; /* Local timestamp prescale */
	uint32_t GTSFREQ : 2; /* Global timestamp frequency */
	uint32_t reserved1 : 4;
	uint32_t TRACEBUSID : 7; /* Identifier for multi-source trace stream formatting */
	uint32_t BUSY : 1; /*  ITM busy: Indicates whether the ITM is currently processing events (read-only) */
	uint32_t reserved2 : 8;
};
static_assert(sizeof(TCRBits) == 4U);

struct ITM {
	union STIMUnion STIM[256];
	uint32_t reserved0[(0xE0000E00 - 0xE0000400) / sizeof(uint32_t)];
	uint32_t TER[8]; /* Trace Enable Registers */
	uint32_t reserved1[(0xE0000E40 - 0xE0000E20) / sizeof(uint32_t)];
	TPRBits TPR; /* Trace Privilege Register */
	uint32_t reserved2[(0xE0000E80 - 0xE0000E44) / sizeof(uint32_t)];
	TCRBits TCR; /* Trace Control Register */
	uint32_t reserved3[(0xE0001000 - 0xE0000E84) / sizeof(uint32_t)];
};
static_assert(sizeof(ITM) == (0xE0001000 - 0xE0000000));

extern volatile ITM ITM;
}
}
}
