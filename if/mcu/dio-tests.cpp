#include "3party/googletest/googletest/include/gtest/gtest.h"
#include "arch/arm/stm32/mmreg/gpio-mock.h"
#include "arch/arm/stm32/mmreg/gpio.h"
#include "if/mcu/dio.h"
#include <array>
#include <iostream>

class DioTests : public ::testing::Test {
};


TEST_F(DioTests, TestDioStm32) {
	using GPIO = volatile struct stm32::mmreg::GPIO::GPIO;
	mocks::GpioMock<GPIO> gpioAMock{stm32::mmreg::GPIO::GPIOA};
	gpioAMock.reset();

	enum DioNames {
		PA0,
		PA15,
		PB7,
		LEN,
	};

	using DioDef = dio::DioDef<volatile struct stm32::mmreg::GPIO::GPIO>;
	static const std::array<DioDef, DioNames::LEN> gpioDefs = {{
		{stm32::mmreg::GPIO::GPIOA,
			0,
			DioDef::IoFunction::OUTPUT,
			DioDef::IoType::PUSH_PULL,
			DioDef::IoSpeed::LOW,
			DioDef::IoBias::NONE,
			DioDef::IoInitState::LOGIC_HIGH},
		{stm32::mmreg::GPIO::GPIOA,
			15,
			DioDef::IoFunction::OUTPUT,
			DioDef::IoType::PUSH_PULL,
			DioDef::IoSpeed::VERY_HIGH,
			DioDef::IoBias::NONE,
			DioDef::IoInitState::LOGIC_HIGH},
		{stm32::mmreg::GPIO::GPIOB,
			7,
			DioDef::IoFunction::OUTPUT,
			DioDef::IoType::PUSH_PULL,
			DioDef::IoSpeed::LOW,
			DioDef::IoBias::NONE,
			DioDef::IoInitState::LOGIC_LOW},
	}};
	dio::configure(gpioDefs);

	//
	// Check configuration
	//
	ASSERT_EQ(stm32::mmreg::GPIO::GPIOA.ODR.halfword, 0b1000'0000'0000'0001U);
	ASSERT_EQ(stm32::mmreg::GPIO::GPIOA.MODER.word, 0b01'11'11'11'11'11'11'11'11'11'11'11'11'11'11'01U);
	ASSERT_EQ(stm32::mmreg::GPIO::GPIOA.OSPEEDR.word, 0b11'00'00'00'00'00'00'00'00'00'00'00'00'00'00'00U);

	//
	// Check how outputs are set and reset directly.
	//

	auto &gpioDefPA0 = gpioDefs[DioNames::PA0]; // just an alias

	gpioDefPA0.setLogicHigh(); // PA0 to logic high
	gpioAMock.update();
	ASSERT_EQ(stm32::mmreg::GPIO::GPIOA.BSRR.word, 0U); // BSRR is cleared
	ASSERT_EQ((stm32::mmreg::GPIO::GPIOA.ODR.halfword >> 0) & 1U, 1U); // output pin is set high

	gpioDefPA0.setLogicLow(); // PA0 to logic low
	gpioAMock.update();
	ASSERT_EQ(stm32::mmreg::GPIO::GPIOA.BSRR.word, 0U); // BSRR is cleared
	ASSERT_EQ((stm32::mmreg::GPIO::GPIOA.ODR.halfword >> 0) & 1U, 0U); // output pin is set low

	//
	// Check how outputs are set and reset with an assert function.
	//

	dio::DioAssertFunctor<GPIO, dio::AssertTypeLogicHigh> assertFuncPA0{gpioDefPA0};

	assertFuncPA0(true);
	gpioAMock.update();
	ASSERT_EQ((stm32::mmreg::GPIO::GPIOA.ODR.halfword >> 0) & 1U, 1U); // output pin is set high

	assertFuncPA0(false);
	gpioAMock.update();
	ASSERT_EQ((stm32::mmreg::GPIO::GPIOA.ODR.halfword >> 0) & 1U, 0U); // output pin is set low
}
