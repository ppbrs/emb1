#include "i2c.h"
#include "arch/arm/stm32/mmreg/gpio.h"
#include "arch/arm/stm32/mmreg/i2c.h"
#include "if/mcu/i2c.h"

// Partial specialization of i2c::configure<T>:
template<>
void i2c::configure<volatile stm32::mmreg::I2C::I2C, volatile stm32::mmreg::GPIO::GPIO>(const I2cDefStm32 &i2cDef) {
	pio::configure(i2cDef.sclDef);
	pio::configure(i2cDef.sdaDef);
}
