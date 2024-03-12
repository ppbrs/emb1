// todo: move this file to arch

#include "i2c.h"
#include "../../../if/mcu/i2c.h"
#include "mmreg/gpio.h"
#include "mmreg/i2c.h"

using I2cDefStm32 = i2c::I2cDef<volatile struct stm32::mmreg::I2C::I2C, volatile struct stm32::mmreg::GPIO::GPIO>;

// Partial specialization of i2c::configure<T>:
template<>
void i2c::configure<volatile struct stm32::mmreg::I2C::I2C, volatile struct stm32::mmreg::GPIO::GPIO>(const I2cDefStm32 &i2cDef) {
	(void)i2cDef;
}
