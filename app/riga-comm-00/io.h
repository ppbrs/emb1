#pragma once
// This header belongs to riga-comm-00 project.
//
// Project-scope IO configuration. It includes both DIO and PIO.
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

extern const dio::DioAssertFunctor<GpioRegs, dio::AssertTypeLogicHigh> assertFuncLED3Green;
extern const dio::DioAssertFunctor<GpioRegs, dio::AssertTypeLogicHigh> assertFuncLED4Blue;

enum class PioNames : size_t {
	USART2_RX, // PA2
	USART2_TX, // PA3

	NUM,
};

using PioDef = pio::PioDef<GpioRegs>;
