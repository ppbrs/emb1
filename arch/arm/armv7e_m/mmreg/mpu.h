#pragma once

#include <cstdint>

namespace armv7e_m {
namespace mmreg {
namespace MPU {
struct TYPEBits {
	uint32_t SEPARATE : 1;
	uint32_t reserved1 : 7;
	uint32_t DREGION : 8;
	uint32_t IREGION : 8;
	uint32_t reserved2 : 8;
};
static_assert(sizeof(TYPEBits) == 4U);

union TYPE {
	uint32_t word;
	TYPEBits bits;
};

struct CTRLBits {
	uint32_t ENABLE : 1;
	uint32_t HFNMIENA : 1;
	uint32_t PRIVDEFENA : 1;
	uint32_t reserved : 29;
};
static_assert(sizeof(CTRLBits) == 4U);

union CTRL {
	uint32_t word;
	CTRLBits bits;
};

struct RBARBits {
	uint32_t REGION : 4;
	uint32_t VALID : 1;
	uint32_t ADDR : 27;
};
static_assert(sizeof(RBARBits) == 4U);

union RBAR {
	uint32_t word;
	RBARBits bits;
};

struct RASRBits {
	uint32_t ENABLE : 1;
	uint32_t SIZE : 5;
	uint32_t reserved1 : 2;
	uint32_t SRD : 8;
	uint32_t B : 1;
	uint32_t C : 1;
	uint32_t S : 1;
	uint32_t TEX : 3;
	uint32_t reserved2 : 2;
	uint32_t AP : 3;
	uint32_t reserved3 : 1;
	uint32_t XN : 1;
	uint32_t reserved4 : 3;
};
static_assert(sizeof(RASRBits) == 4U);

union RASR {
	uint32_t word;
	RASRBits bits;
};

struct MPU {
	union TYPE TYPE;
	union CTRL CTRL;
	uint32_t RNR;
	union RBAR RBAR;
	union RASR RASR;
};
static_assert(sizeof(MPU) == 20U);

extern volatile MPU MPU;
}
}
}
