#pragma once
//
// Project-scope IO configuration. 
//

#include "if/mcu/dio.h"
#include "if/mcu/pio.h"
#include "arch/arm/stm32/mmreg/gpio.h"


enum DioNames {
	LED3_GREEN,
	LED4_BLUE,
	NUM_DIO,
};


using DioDef = dio::DioDef<volatile struct stm32::mmreg::GPIO::GPIO>;

extern const DioDef &dioLED2;
extern const DioDef &dioLED3;

// using GPIO = volatile struct stm32::reg::GPIO::GPIO;
extern const dio::DioAssertFunctor<volatile struct stm32::mmreg::GPIO::GPIO, dio::AssertTypeLogicHigh> assertFuncLED3Green;
extern const dio::DioAssertFunctor<volatile struct stm32::mmreg::GPIO::GPIO, dio::AssertTypeLogicHigh> assertFuncLED4Blue;

enum PioNames {
	I2C1_SCL, // PB6
	I2C1_SDA, // PB7
	I2C2_SCL, // PB10
	I2C2_SDA, // PB11
	NUM_PIO,
};

using PioDef = pio::PioDef<volatile struct stm32::mmreg::GPIO::GPIO>;
