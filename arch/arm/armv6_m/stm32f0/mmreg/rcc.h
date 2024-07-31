#pragma once

#include <cstdint>

namespace stm32f0 {
namespace mmreg {
namespace RCC {

/* Clock control register */
struct CRBits {
	uint32_t HSION : 1;
	uint32_t HSIRDY : 1;
	uint32_t reserved1 : 1;
	uint32_t HSITRIM : 5;
	uint32_t HSICAL : 8;
	uint32_t HSEON : 1;
	uint32_t HSERDY : 1;
	uint32_t HSEBYP : 1;
	uint32_t CSSON : 1; // 19
	uint32_t reserved2 : 4;
	uint32_t PLLON : 1; // 24
	uint32_t PLLRDY : 1; // 25
	uint32_t reserved3 : 6; // 31:26

	static constexpr uint32_t PLLONMask = (0b1u << 24);
	static constexpr uint32_t PLLONOff = (0b0u << 24);
	static constexpr uint32_t PLLONOn = (0b1u << 24);

	static constexpr uint32_t PLLRDYMask = (1u << 25);
};
static_assert(sizeof(CRBits) == sizeof(uint32_t));
union CR {
	uint32_t word;
	CRBits bits;
};
static_assert(sizeof(CR) == sizeof(uint32_t));

/* Clock configuration register */
struct CFGRBits {
	uint32_t SW : 2; // 1:0
	uint32_t SWS : 2; // 3:2
	uint32_t HPRE : 4; // 7:4
	uint32_t PPRE : 3; // 10:8
	uint32_t reserved1 : 3; // 13:11
	uint32_t ADCPRE : 1; // 14
	uint32_t PLLSRC : 2; // 16:15
	uint32_t PLLXTPRE : 1; // 17
	uint32_t PLLMUL : 4; // 21:18
	uint32_t reserved2 : 2; // 23:22
	uint32_t MCO : 4; // 27:24
	uint32_t MCOPRE : 3; // 30:28
	uint32_t PLLNODIV : 1; // 31

	static constexpr uint32_t PLLMULMask = (0b1111u << 18);
	static constexpr uint32_t PLLMULx2 = (0b0000u << 18);
	static constexpr uint32_t PLLMULx3 = (0b0001u << 18);
	static constexpr uint32_t PLLMULx4 = (0b0010u << 18);
	static constexpr uint32_t PLLMULx5 = (0b0011u << 18);
	static constexpr uint32_t PLLMULx6 = (0b0100u << 18);
	static constexpr uint32_t PLLMULx7 = (0b0101u << 18);
	static constexpr uint32_t PLLMULx8 = (0b0110u << 18);
	static constexpr uint32_t PLLMULx9 = (0b0111u << 18);
	static constexpr uint32_t PLLMULx10 = (0b1000u << 18);
	static constexpr uint32_t PLLMULx11 = (0b1001u << 18);
	static constexpr uint32_t PLLMULx12 = (0b1010u << 18);
	static constexpr uint32_t PLLMULx13 = (0b1011u << 18);
	static constexpr uint32_t PLLMULx14 = (0b1100u << 18);
	static constexpr uint32_t PLLMULx15 = (0b1101u << 18);
	static constexpr uint32_t PLLMULx16 = (0b1110u << 18); // 0b1111u too

	static constexpr uint32_t PLLSRCMask = (0b11u << 15);
	static constexpr uint32_t PLLSRCHSI = (0b01u << 15);
	static constexpr uint32_t PLLSRCHSE = (0b10u << 15);

	static constexpr uint32_t PPREMask = (0b111u << 8);
	static constexpr uint32_t PPRENoDiv = (0b000u << 8);

	static constexpr uint32_t HPREMask = (0b1111u << 4);
	static constexpr uint32_t HPRENoDiv = (0b0000u << 4);

	static constexpr uint32_t SWSMask = (0b11u << 2);
	static constexpr uint32_t SWSHSI = (0b00u << 2);
	static constexpr uint32_t SWSHSE = (0b01u << 2);
	static constexpr uint32_t SWSPLL = (0b10u << 2);

	static constexpr uint32_t SWMask = (0b11u << 0);
	static constexpr uint32_t SWHSI = (0b00u << 0);
	static constexpr uint32_t SWHSE = (0b01u << 0);
	static constexpr uint32_t SWPLL = (0b10u << 0);
};
static_assert(sizeof(CFGRBits) == sizeof(uint32_t));
union CFGR {
	uint32_t word;
	CFGRBits bits;
};
static_assert(sizeof(CFGR) == sizeof(uint32_t));

union CIR {
	uint32_t word;
};
union APB2RSTR {
	uint32_t word;
};
union APB1RSTR {
	uint32_t word;
};

/* AHB peripheral clock enable register */
struct AHBENRBits {
	uint32_t DMAEN : 1; // 0
	uint32_t DMA2EN : 1; // 1
	uint32_t SRAMEN : 1; // 2
	uint32_t reserved1 : 1; // 3
	uint32_t FLITFEN : 1; // 4
	uint32_t reserved2 : 1; // 5
	uint32_t CRCEN : 1; // 6
	uint32_t reserved3 : 10; // 16:7
	uint32_t IOPAEN : 1; // 17
	uint32_t IOPBEN : 1; // 18
	uint32_t IOPCEN : 1; // 19
	uint32_t IOPDEN : 1; // 20
	uint32_t IOPEEN : 1; // 21
	uint32_t IOPFEN : 1; // 22
	uint32_t reserved4 : 1; // 23
	uint32_t TSCEN : 1; // 24
	uint32_t reserved5 : 7; // 31:25

	static constexpr uint32_t IOPAENMask = (0b1u << 17);
	static constexpr uint32_t IOPAENSet = (0b1u << 17);
	static constexpr uint32_t IOPBENMask = (0b1u << 18);
	static constexpr uint32_t IOPBENSet = (0b1u << 18);
	static constexpr uint32_t IOPCENMask = (0b1u << 19);
	static constexpr uint32_t IOPCENSet = (0b1u << 19);
	static constexpr uint32_t IOPDENMask = (0b1u << 20);
	static constexpr uint32_t IOPDENSet = (0b1u << 20);
	static constexpr uint32_t IOPEENMask = (0b1u << 21);
	static constexpr uint32_t IOPEENSet = (0b1u << 21);
	static constexpr uint32_t IOPFENMask = (0b1u << 22);
	static constexpr uint32_t IOPFENSet = (0b1u << 22);
};
static_assert(sizeof(AHBENRBits) == sizeof(uint32_t));
union AHBENR {
	uint32_t word;
	AHBENRBits bits;
};
static_assert(sizeof(AHBENR) == sizeof(uint32_t));

/* APB peripheral clock enable register 2 */
struct APB2ENRBits {
};
union APB2ENR {
	uint32_t word;
	APB2ENRBits bits;
};
static_assert(sizeof(APB2ENR) == sizeof(uint32_t));

/* APB peripheral clock enable register 1 */
struct APB1ENRBits {
	uint32_t TIM2EN : 1; // Bit 0
	uint32_t TIM3EN : 1; // Bit 1
	uint32_t reserved1 : 2; // Bits 3:2
	uint32_t TIM6EN : 1; // Bit 4
	uint32_t TIM7EN : 1; // Bit 5
	uint32_t reserved2 : 2; // Bits 7:6
	uint32_t TIM14EN : 1; // Bit 8
	uint32_t reserved3 : 2; // Bits 10:9
	uint32_t WWDGEN : 1; // Bit 11
	uint32_t reserved : 2; // Bits 13:12
	uint32_t SPI2EN : 1; // Bit 14
	uint32_t reserved4 : 2; // Bits 16:15
	uint32_t USART2EN : 1; // Bit 17
	uint32_t USART3EN : 1; // Bit 18
	uint32_t USART4EN : 1; // Bit 19
	uint32_t USART5EN : 1; // Bit 20
	uint32_t I2C1EN : 1; // Bit 21
	uint32_t I2C2EN : 1; // Bit 22
	uint32_t USBEN : 1; // Bit 23
	uint32_t reserved5 : 1; // Bit 24
	uint32_t CANEN : 1; // Bit 25
	uint32_t reserved6 : 1; // Bit 26
	uint32_t CRSEN : 1; // Bit 27
	uint32_t PWREN : 1; // Bit 28
	uint32_t DACEN : 1; // Bit 29
	uint32_t CECEN : 1; // Bit 30
	uint32_t reserved7 : 1; // Bit 31

	static constexpr uint32_t TIM2ENMask = (0b1u << 0);
	static constexpr uint32_t TIM2ENSet = TIM2ENMask;
	static constexpr uint32_t TIM3ENMask = (0b1u << 1);
	static constexpr uint32_t TIM3ENSet = TIM3ENMask;

	static constexpr uint32_t I2C1ENMask = (0b1u << 21);
	static constexpr uint32_t I2C1ENSet = I2C1ENMask;
	static constexpr uint32_t I2C2ENMask = (0b1u << 22);
	static constexpr uint32_t I2C2ENSet = I2C2ENMask;

	static constexpr uint32_t USART2ENMask = (0b1u << 17);
	static constexpr uint32_t USART2ENSet = USART2ENMask;
};
union APB1ENR {
	uint32_t word;
	APB1ENRBits bits;
};
static_assert(sizeof(APB1ENR) == sizeof(uint32_t));

union BDCR {
	uint32_t word;
};
union CSR {
	uint32_t word;
};
union AHBRSTR {
	uint32_t word;
};
/* Clock configuration register 2 */
struct CFGR2Bits {
	uint32_t PREDIV : 3;
	uint32_t reserved : 29;
};
union CFGR2 {
	uint32_t word;
	CFGR2Bits bits;
};
static_assert(sizeof(CFGR2) == sizeof(uint32_t));
/* Clock configuration register 3 */
struct CFGR3Bits {
	uint32_t USART1SW : 2;
	uint32_t reserved1 : 2;
	uint32_t I2C1SW : 1;
	uint32_t reserved2 : 1;
	uint32_t CECSW : 1;
	uint32_t USBSW : 1;
	uint32_t ADCSW : 1;
	uint32_t reserved3 : 7;
	uint32_t USART2SW : 2;
	uint32_t USART3SW : 3;

	static constexpr uint32_t I2C1SWMask = (1 << 4);
	static constexpr uint32_t I2C1SWHSI = (0 << 4);
	static constexpr uint32_t I2C1SWSysClk = (1 << 4);
};
union CFGR3 {
	uint32_t word;
	CFGR3Bits bits;
};
static_assert(sizeof(CFGR3) == sizeof(uint32_t));
/* Clock control register 2 */
union CR2 {
	uint32_t word;
};

struct RCC {
	union CR CR;
	union CFGR CFGR;
	union CIR CIR;
	union APB2RSTR APB2RSTR;
	union APB1RSTR APB1RSTR;
	union AHBENR AHBENR;
	union APB2ENR APB2ENR;
	union APB1ENR APB1ENR;
	union BDCR BDCR;
	union CSR CSR;
	union AHBRSTR AHBRSTR;
	union CFGR2 CFGR2;
	union CFGR3 CFGR3;
	union CR2 CR2;
};
static_assert(sizeof(RCC) == 0x38U);

extern volatile struct RCC RCC;
}
}
}
