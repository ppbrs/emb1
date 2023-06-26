#pragma once

#include <cstdint>

namespace stm32 {
namespace mmreg {
namespace GPIO {
enum Mode : uint32_t {
	MODE_IN = 0U,
	MODE_OUT = 1U,
	MODE_AF = 2U,
	MODE_AN = 3U,
	MODE_MASK = 3U,
};

enum OType : uint32_t {
	OTYPE_PP = 0U,
	OTYPE_OD = 1U,
	OTYPE_MASK = 1U,
};

enum OData : uint16_t {
	ODATA_LOW = 0U,
	ODATA_HIGH = 1U,
	ODATA_MASK = 1U,
};

enum OSpeed : uint32_t {
	OSPEED_LOW = 0U,
	OSPEED_MEDIUM = 1U,
	OSPEED_HIGH = 2U,
	OSPEED_VERY_HIGH = 3U,
	OSPEED_MASK = 3U,
};

enum PUPD : uint32_t {
	PUPD_NONE = 0U,
	PUPD_PU = 1U,
	PUPD_PD = 2U,
	PUPD_MASK = 3U,
};

struct MODERBits {
	uint32_t MODER0 : 2;
	uint32_t MODER1 : 2;
	uint32_t MODER2 : 2;
	uint32_t MODER3 : 2;
	uint32_t MODER4 : 2;
	uint32_t MODER5 : 2;
	uint32_t MODER6 : 2;
	uint32_t MODER7 : 2;
	uint32_t MODER8 : 2;
	uint32_t MODER9 : 2;
	uint32_t MODER10 : 2;
	uint32_t MODER11 : 2;
	uint32_t MODER12 : 2;
	uint32_t MODER13 : 2;
	uint32_t MODER14 : 2;
	uint32_t MODER15 : 2;
};
static_assert(sizeof(MODERBits) == 4u);

union MODER {
	uint32_t word;
	MODERBits bits;
	static constexpr uint32_t mask = 0b11;
	static constexpr uint32_t inputMode = 0b00;
	static constexpr uint32_t outputMode = 0b01;
	static constexpr uint32_t alternatFunctionMode = 0b10;
	static constexpr uint32_t analogMode = 0b11;
};

struct OTYPERBits {
	uint32_t OTYPER0 : 1;
	uint32_t OTYPER1 : 1;
	uint32_t OTYPER2 : 1;
	uint32_t OTYPER3 : 1;
	uint32_t OTYPER4 : 1;
	uint32_t OTYPER5 : 1;
	uint32_t OTYPER6 : 1;
	uint32_t OTYPER7 : 1;
	uint32_t OTYPER8 : 1;
	uint32_t OTYPER9 : 1;
	uint32_t OTYPER10 : 1;
	uint32_t OTYPER11 : 1;
	uint32_t OTYPER12 : 1;
	uint32_t OTYPER13 : 1;
	uint32_t OTYPER14 : 1;
	uint32_t OTYPER15 : 1;
	uint32_t rsvd : 16;
};
static_assert(sizeof(OTYPERBits) == 4u);

union OTYPER {
	uint32_t word;
	OTYPERBits bits;
};

struct OSPEEDRBits {
	uint32_t OSPEEDR0 : 2;
	uint32_t OSPEEDR1 : 2;
	uint32_t OSPEEDR2 : 2;
	uint32_t OSPEEDR3 : 2;
	uint32_t OSPEEDR4 : 2;
	uint32_t OSPEEDR5 : 2;
	uint32_t OSPEEDR6 : 2;
	uint32_t OSPEEDR7 : 2;
	uint32_t OSPEEDR8 : 2;
	uint32_t OSPEEDR9 : 2;
	uint32_t OSPEEDR10 : 2;
	uint32_t OSPEEDR11 : 2;
	uint32_t OSPEEDR12 : 2;
	uint32_t OSPEEDR13 : 2;
	uint32_t OSPEEDR14 : 2;
	uint32_t OSPEEDR15 : 2;
};
static_assert(sizeof(OSPEEDRBits) == 4u);

union OSPEEDR {
	uint32_t word;
	OSPEEDRBits bits;

	static constexpr uint32_t mask = 0b11;
	static constexpr uint32_t lowSpeed = 0b00;
	static constexpr uint32_t mediumSpeed = 0b01;
	static constexpr uint32_t highSpeed = 0b10;
	static constexpr uint32_t veryHighSpeed = 0b11;
};

struct PUPDRBits {
	uint32_t PUPDR0 : 2;
	uint32_t PUPDR1 : 2;
	uint32_t PUPDR2 : 2;
	uint32_t PUPDR3 : 2;
	uint32_t PUPDR4 : 2;
	uint32_t PUPDR5 : 2;
	uint32_t PUPDR6 : 2;
	uint32_t PUPDR7 : 2;
	uint32_t PUPDR8 : 2;
	uint32_t PUPDR9 : 2;
	uint32_t PUPDR10 : 2;
	uint32_t PUPDR11 : 2;
	uint32_t PUPDR12 : 2;
	uint32_t PUPDR13 : 2;
	uint32_t PUPDR14 : 2;
	uint32_t PUPDR15 : 2;
};
static_assert(sizeof(PUPDRBits) == 4u);

union PUPDR {
	uint32_t word;
	PUPDRBits bits;
};

struct IDRBits {
	uint32_t IDR0 : 1;
	uint32_t IDR1 : 1;
	uint32_t IDR2 : 1;
	uint32_t IDR3 : 1;
	uint32_t IDR4 : 1;
	uint32_t IDR5 : 1;
	uint32_t IDR6 : 1;
	uint32_t IDR7 : 1;
	uint32_t IDR8 : 1;
	uint32_t IDR9 : 1;
	uint32_t IDR10 : 1;
	uint32_t IDR11 : 1;
	uint32_t IDR12 : 1;
	uint32_t IDR13 : 1;
	uint32_t IDR14 : 1;
	uint32_t IDR15 : 1;
	uint32_t rsvd : 16;
};
static_assert(sizeof(IDRBits) == 4u);

union IDR {
	// uint32_t word;
	uint16_t halfword;
	IDRBits bits;
};

struct ODRBits {
	uint32_t ODR0 : 1;
	uint32_t ODR1 : 1;
	uint32_t ODR2 : 1;
	uint32_t ODR3 : 1;
	uint32_t ODR4 : 1;
	uint32_t ODR5 : 1;
	uint32_t ODR6 : 1;
	uint32_t ODR7 : 1;
	uint32_t ODR8 : 1;
	uint32_t ODR9 : 1;
	uint32_t ODR10 : 1;
	uint32_t ODR11 : 1;
	uint32_t ODR12 : 1;
	uint32_t ODR13 : 1;
	uint32_t ODR14 : 1;
	uint32_t ODR15 : 1;
	uint32_t rsvd : 16;
};
static_assert(sizeof(ODRBits) == 4u);

union ODR {
	// uint32_t word;
	uint16_t halfword;
	ODRBits bits;
};

struct BSRRBits {
	uint32_t BS0 : 1;
	uint32_t BS1 : 1;
	uint32_t BS2 : 1;
	uint32_t BS3 : 1;
	uint32_t BS4 : 1;
	uint32_t BS5 : 1;
	uint32_t BS6 : 1;
	uint32_t BS7 : 1;
	uint32_t BS8 : 1;
	uint32_t BS9 : 1;
	uint32_t BS10 : 1;
	uint32_t BS11 : 1;
	uint32_t BS12 : 1;
	uint32_t BS13 : 1;
	uint32_t BS14 : 1;
	uint32_t BS15 : 1;
	uint32_t BR0 : 1;
	uint32_t BR1 : 1;
	uint32_t BR2 : 1;
	uint32_t BR3 : 1;
	uint32_t BR4 : 1;
	uint32_t BR5 : 1;
	uint32_t BR6 : 1;
	uint32_t BR7 : 1;
	uint32_t BR8 : 1;
	uint32_t BR9 : 1;
	uint32_t BR10 : 1;
	uint32_t BR11 : 1;
	uint32_t BR12 : 1;
	uint32_t BR13 : 1;
	uint32_t BR14 : 1;
	uint32_t BR15 : 1;
};
static_assert(sizeof(BSRRBits) == 4u);

/*
GPIO port bit set/reset register.
This is a write-only register.
Bits 31:16 BR[15:0]: Port x reset I/O pin y (y = 15 to 0)
Bits 15:0 BS[15:0]: Port x set I/O pin y (y = 15 to 0)
*/
union BSRR {
	uint32_t word;
	BSRRBits bits;
};

struct LCKRBits {
	uint32_t LCK : 16;
	uint32_t LCKK : 1;
	uint32_t rsvd : 15;
};
static_assert(sizeof(LCKRBits) == 4u);

union LCKR {
	uint32_t word;
	LCKRBits bits;
};

struct AFRLBits {
	uint32_t AFRL0 : 4;
	uint32_t AFRL1 : 4;
	uint32_t AFRL2 : 4;
	uint32_t AFRL3 : 4;
	uint32_t AFRL4 : 4;
	uint32_t AFRL5 : 4;
	uint32_t AFRL6 : 4;
	uint32_t AFRL7 : 4;
};
static_assert(sizeof(AFRLBits) == 4u);

union AFRL {
	uint32_t word;
	AFRLBits bits;
};

struct AFRHBits {
	uint32_t AFRH8 : 4;
	uint32_t AFRH9 : 4;
	uint32_t AFRH10 : 4;
	uint32_t AFRH11 : 4;
	uint32_t AFRH12 : 4;
	uint32_t AFRH13 : 4;
	uint32_t AFRH14 : 4;
	uint32_t AFRH15 : 4;
};
static_assert(sizeof(AFRHBits) == 4u);

union AFRH {
	uint32_t word;
	AFRHBits bits;
};

struct GPIO {
	union MODER MODER;
	union OTYPER OTYPER;
	union OSPEEDR OSPEEDR;
	union PUPDR PUPDR;
	union IDR IDR;
	union ODR ODR;
	union BSRR BSRR;
	union LCKR LCKR;
	union AFRL AFRL;
	union AFRH AFRH;
	uint32_t pad[0xF6];
};
static_assert(sizeof(GPIO) == 0x400U);

extern volatile struct GPIO GPIOA;
extern volatile struct GPIO GPIOB;
extern volatile struct GPIO GPIOC;
extern volatile struct GPIO GPIOD;
extern volatile struct GPIO GPIOE;
extern volatile struct GPIO GPIOF;
extern volatile struct GPIO GPIOG;
extern volatile struct GPIO GPIOH;
extern volatile struct GPIO GPIOI;
extern volatile struct GPIO GPIOJ;
extern volatile struct GPIO GPIOK;
}
}
}
