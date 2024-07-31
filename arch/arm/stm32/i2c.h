#pragma once

#include "arch/arm/stm32/mmreg/gpio.h"
#include "arch/arm/stm32/mmreg/i2c.h"
#include "if/mcu/i2c.h"

namespace i2c {
}

using I2cDefStm32 = i2c::I2cDef<I2CRegsStm32, GpioRegsStm32>;
