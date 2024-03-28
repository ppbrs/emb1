#include "if/mcu/mcu-init.h"
#include "./io.h"
#include "arch/arm/armv7e_m/stm32h7/mmreg/rcc.h"
#include "arch/arm/stm32/mmreg/gpio.h"
#include "if/mcu/chrono.h"
#include "if/mcu/dio.h"
#include <array>


//
// DIOs for Nucleo board:
//
// User LD1: a green user LED is connected to the STM32H7 I/O PB0 (SB39 ON and SB47 OFF) or PA5 (SB47 ON and SB39 OFF) corresponding to the ST Zio D13.
// User LD2: a yellow user LED is connected to PE1.
// User LD3: a red user LED is connected to PB14.
// These user LEDs are on when the I/O is HIGH value, and are off when the I/O is LOW.
//
static constexpr std::array<DioDef, DioNames::LEN> dioDefs = {{
	{// LED2
		stm32::mmreg::GPIO::GPIOE, 1,
		DioDef::IoFunction::OUTPUT,
		DioDef::IoType::PUSH_PULL,
		DioDef::IoSpeed::LOW,
		DioDef::IoBias::NONE,
		DioDef::IoInitState::LOGIC_LOW},
	{// LED3
		stm32::mmreg::GPIO::GPIOB, 14,
		DioDef::IoFunction::OUTPUT,
		DioDef::IoType::PUSH_PULL,
		DioDef::IoSpeed::LOW,
		DioDef::IoBias::NONE,
		DioDef::IoInitState::LOGIC_LOW},
}};

const DioDef &dioLED2 = dioDefs[0];
const DioDef &dioLED3 = dioDefs[1];

const dio::DioAssertFunctor<volatile struct stm32::mmreg::GPIO::GPIO, dio::AssertTypeLogicHigh> assertFuncLED2{dioDefs[DioNames::LED2]};
const dio::DioAssertFunctor<volatile struct stm32::mmreg::GPIO::GPIO, dio::AssertTypeLogicLow> assertFuncLED3{dioDefs[DioNames::LED3]};

void mcuInit::systemClock::initTree() {
	namespace RCC = stm32h7::mmreg::RCC;
	RCC::AHB4ENR ahb4EnR{};
	ahb4EnR.bits.GPIOAEN = 1;
	ahb4EnR.bits.GPIOBEN = 1;
	ahb4EnR.bits.GPIOCEN = 1;
	ahb4EnR.bits.GPIODEN = 1;
	ahb4EnR.bits.GPIOEEN = 1;
	ahb4EnR.bits.GPIOFEN = 1;
	ahb4EnR.bits.GPIOGEN = 1;
	ahb4EnR.bits.GPIOHEN = 1;
	ahb4EnR.bits.GPIOIEN = 1;
	ahb4EnR.bits.GPIOJEN = 1;
	ahb4EnR.bits.GPIOKEN = 1;
	RCC::RCC.AHB4ENR.word = ahb4EnR.word;
}

void mcuInit::systemClock::initChrono() {
	chrono::steady_clock::init();
	chrono::high_resolution_clock::init();
}

void mcuInit::io::init() {
	dio::configure(dioDefs);
}

void mcuInit::comm::init() {
}
