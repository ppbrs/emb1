#pragma once
//
// Project-scope IO configuration. 
//

#include "if/mcu/dio.h"
#include "arch/arm/stm32/mmreg/gpio.h"

enum DioNames {
	LED2,
	LED3,
	LEN,
};

using DioDef = dio::DioDef<volatile struct stm32::mmreg::GPIO::GPIO>;
// extern const std::array<DioDef, DioNames::LEN> dioDefs;

extern const DioDef &dioLED2;
extern const DioDef &dioLED3;

// using GPIO = volatile struct stm32::mmreg::GPIO::GPIO;
extern const dio::DioAssertFunctor<volatile struct stm32::mmreg::GPIO::GPIO, dio::AssertTypeLogicHigh> assertFuncLED2;
extern const dio::DioAssertFunctor<volatile struct stm32::mmreg::GPIO::GPIO, dio::AssertTypeLogicLow> assertFuncLED3;

// }
