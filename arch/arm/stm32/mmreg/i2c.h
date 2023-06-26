#pragma once

#include <cstdint>

namespace stm32 {
namespace mmreg {
namespace I2C {


struct I2C {

	uint32_t CR1;
	uint32_t CR2;
	uint32_t OAR1;
	uint32_t OAR2;
	uint32_t TIMINGR;
	uint32_t TIMEOUTR;
	uint32_t ISR;
	uint32_t ICR;
	uint32_t PECR;
	uint32_t RXDR;
	uint32_t TXDR;
};
static_assert(sizeof(I2C) == 0x2cu);

extern volatile struct I2C I2C1;
extern volatile struct I2C I2C2;

}
}
}


/*
I2C control register 1 (I2C_CR1) 0x00
I2C control register 2 (I2C_CR2) 0x04
I2C own address 1 register (I2C_OAR1) 0x08
I2C own address 2 register (I2C_OAR2) 0x0C
I2C timing register (I2C_TIMINGR) 0x10
I2C timeout register (I2C_TIMEOUTR) 0x14
I2C interrupt and status register (I2C_ISR) 0x18
I2C interrupt clear register (I2C_ICR) 0x1C
I2C PEC register (I2C_PECR) 0x20
I2C receive data register (I2C_RXDR) 0x24
I2C transmit data register (I2C_TXDR) 0x28
*/