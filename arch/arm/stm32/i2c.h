#pragma once
// todo: move this file to arch

#include "../../../if/mcu/i2c.h"
#include "mmreg/i2c.h"
#include "mmreg/gpio.h"

namespace i2c {
}

using I2cDef = i2c::I2cDef<volatile struct stm32::mmreg::I2C::I2C, volatile struct stm32::mmreg::GPIO::GPIO>;

