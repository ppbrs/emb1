#pragma once

#include "arch/arm/armv6_m/stm32f0/mmreg/usart.h"
#include "arch/arm/stm32/mmreg/gpio.h"
#include "if/mcu/usart.h"

namespace usart {

void isr1();
void isr2();
void func();
}

using UsartRegsF0 = volatile stm32f0::mmreg::USART::USART;
using GpioRegsF0 = volatile stm32::mmreg::GPIO::GPIO;

using UsartDefF0 = usart::UsartDef<UsartRegsF0, GpioRegsF0>;
