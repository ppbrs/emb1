#pragma once
//
// Project-scope IO configuration,. It includes both DIO and  PIO.
//

#include "arch/arm/stm32/mmreg/gpio.h"
#include "if/mcu/dio.h"
#include "if/mcu/pio.h"
#include <cstddef>

using GpioRegs = volatile stm32::mmreg::GPIO::GPIO;

enum class DioNames : size_t {
	LED3_GREEN,
	LED4_BLUE,

	NUM,
};

using DioDef = dio::DioDef<GpioRegs>;

// extern const DioDef &dioLED2;
// extern const DioDef &dioLED3;

extern const dio::DioAssertFunctor<GpioRegs, dio::AssertTypeLogicHigh> assertFuncLED3Green;
extern const dio::DioAssertFunctor<GpioRegs, dio::AssertTypeLogicHigh> assertFuncLED4Blue;

enum class PioNames : size_t {
	USART2_RX, // PA2
	USART2_TX, // PA3

	I2C1_SCL, // PB6
	I2C1_SDA, // PB7
	I2C2_SCL, // PB10
	I2C2_SDA, // PB11

	NUM,
};

using PioDef = pio::PioDef<GpioRegs>;
