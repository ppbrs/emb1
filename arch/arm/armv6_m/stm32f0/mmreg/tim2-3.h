#pragma once

#include <cstdint>

namespace stm32f0 {
namespace mmreg {
namespace TIM2 {

/* control register 1 */
struct CR1Bits {
	uint32_t CEN : 1; // 0;
	uint32_t UDIS : 1; // 1;
	uint32_t URS : 1; // 2;
	uint32_t OPM : 1; // 3;
	uint32_t DIR : 1; // 4;
	uint32_t CMS : 2; // 6:5;
	uint32_t ARPE : 1; // 7;
	uint32_t CKD : 1; // 9:8;
	uint32_t Reserved : 6; // 15:10;

	static constexpr uint32_t CENMask = (1 << 0);
	static constexpr uint32_t CENSet = CENMask;
};
union CR1Union {
	uint32_t word;
	CR1Bits bits;
};
union CR2Union {
	uint32_t word;
};
union SMCRUnion {
	uint32_t word;
};

/* DMA/Interrupt enable register */
struct DIERBits {
	uint16_t UIE : 1; // bit 0
	uint16_t CC1IE : 1; // bit 1
	uint16_t CC2IE : 1; // bit 2
	uint16_t CC3IE : 1; // bit 3
	uint16_t CC4IE : 1; // bit 4
	uint16_t reserved1 : 1; // bit 5
	uint16_t TIE : 1; // bit 6
	uint16_t reserved2 : 1; // bit 7
	uint16_t UDE : 1; // bit 8
	uint16_t CC1DE : 1; // bit 9
	uint16_t CC2DE : 1; // bit 10
	uint16_t CC3DE : 1; // bit 11
	uint16_t CC4DE : 1; // bit 12
	uint16_t reserved3 : 1; // bit 13
	uint16_t TDE : 1; // bit 14
	uint16_t reserved4 : 1; // bit 15
	static constexpr uint16_t UIEMask = (1 << 0);
	static constexpr uint16_t UIESet = UIEMask;
};
static_assert(sizeof(DIERBits) == 2);
union DIERUnion {
	uint32_t word;
	DIERBits bits;
};

/* status register */
struct SRBits {
	uint16_t UIF : 1; // bit 0
	uint16_t CC1IF : 1; // bit 1
	uint16_t CC2IF : 1; // bit 2
	uint16_t CC3IF : 1; // bit 3
	uint16_t CC4IF : 1; // bit 4
	uint16_t Reserved1 : 1; // bit 5
	uint16_t TIF : 1; // bit 6
	uint16_t Reserved2 : 2; // bits 8:7
	uint16_t CC1OF : 1; // bit 9
	uint16_t CC2OF : 1; // bit 10
	uint16_t CC3OF : 1; // bit 11
	uint16_t CC4OF : 1; // bit 12
	uint16_t Reserved3 : 3; // bits 15:13
	static constexpr uint16_t UIFMask = (1 << 0);
	static constexpr uint16_t UIFSet = UIFMask;
};
static_assert(sizeof(SRBits) == 2);
union SRUnion {
	uint32_t word;
	SRBits bits;
};

/* event generation register */
struct EGRBits {
	uint16_t UG : 1; // Bit 0
	uint16_t CC1G : 1; // Bit 1
	uint16_t CC2G : 1; // Bit 2
	uint16_t CC3G : 1; // Bit 3
	uint16_t CC4G : 1; // Bit 4
	uint16_t reserved1 : 1; // Bit 5
	uint16_t TG : 1; // Bit 6
	uint16_t reserved2 : 9; // Bits 7
	static constexpr uint16_t UGSet = (1 << 0);
};
static_assert(sizeof(EGRBits) == 2);
union EGRUnion {
	uint32_t word;
	EGRBits bits;
};

union CCMR1Union {
	uint32_t word;
};
union CCMR2Union {
	uint32_t word;
};
union CCERUnion {
	uint32_t word;
};
union CCR1Union {
	uint32_t word;
};
union CCR2Union {
	uint32_t word;
};
union CCR3Union {
	uint32_t word;
};
union CCR4Union {
	uint32_t word;
};
union DCRUnion {
	uint32_t word;
};
union DMARUnion {
	uint32_t word;
};


struct TIM2 {
	CR1Union CR1;
	CR2Union CR2;
	SMCRUnion SMCR;
	DIERUnion DIER;
	SRUnion SR;
	EGRUnion EGR; // 0x14
	CCMR1Union CCMR1;
	CCMR2Union CCMR2;
	CCERUnion CCER;
	uint32_t CNT;
	uint16_t PSC;
	uint16_t reserved1;
	uint32_t ARR;
	uint32_t reserved2;
	uint32_t CCR1;
	uint32_t CCR2;
	uint32_t CCR3;
	uint32_t CCR4;
	uint32_t reserved3;
	DCRUnion DCR;
	DMARUnion DMAR;
};
static_assert(sizeof(TIM2) == 0x50u);

extern volatile struct TIM2 TIM2;

}

namespace TIM3 {

using CR1Union = stm32f0::mmreg::TIM2::CR1Union;
using CR1Bits = stm32f0::mmreg::TIM2::CR1Bits;
using CR2Union = stm32f0::mmreg::TIM2::CR2Union;
using SMCRUnion = stm32f0::mmreg::TIM2::SMCRUnion;
using DIERUnion = stm32f0::mmreg::TIM2::DIERUnion;
using DIERBits = stm32f0::mmreg::TIM2::DIERBits;
using SRUnion = stm32f0::mmreg::TIM2::SRUnion;
using SRBits = stm32f0::mmreg::TIM2::SRBits;
using EGRUnion = stm32f0::mmreg::TIM2::EGRUnion;
using EGRBits = stm32f0::mmreg::TIM2::EGRBits;
using CCMR1Union = stm32f0::mmreg::TIM2::CCMR1Union;
using CCMR2Union = stm32f0::mmreg::TIM2::CCMR2Union;
using CCERUnion = stm32f0::mmreg::TIM2::CCERUnion;
using DCRUnion = stm32f0::mmreg::TIM2::DCRUnion;
using DMARUnion = stm32f0::mmreg::TIM2::DMARUnion;

struct TIM3 {
	CR1Union CR1;
	CR2Union CR2;
	SMCRUnion SMCR;
	DIERUnion DIER;
	SRUnion SR;
	EGRUnion EGR; // 0x14
	CCMR1Union CCMR1;
	CCMR2Union CCMR2;
	CCERUnion CCER;
	uint16_t CNT;
	uint16_t reservedCNTHi;
	uint16_t PSC;
	uint16_t reserved1;
	uint16_t ARR;
	uint16_t reservedARRHi;
	uint32_t reserved2;
	uint16_t CCR1;
	uint16_t reservedCCR1Hi;
	uint16_t CCR2;
	uint16_t reservedCCR2Hi;
	uint16_t CCR3;
	uint16_t reservedCCR3Hi;
	uint16_t CCR4;
	uint16_t reservedCCR4Hi;
	uint16_t reserved3;
	DCRUnion DCR;
	DMARUnion DMAR;
};
static_assert(sizeof(TIM3) == 0x50u);

extern volatile struct TIM3 TIM3;

}
} // mmreg
} // stm32f0
