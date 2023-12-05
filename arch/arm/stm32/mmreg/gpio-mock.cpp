#include "./gpio-mock.h"

#include "arch/arm/stm32/mmreg/gpio.h"
#include "if/mcu/mmreg.h"

volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOA = {};
volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOB = {};

using GpioStm32 = volatile struct stm32::mmreg::GPIO::GPIO;


template<>
void mocks::GpioMock<GpioStm32>::update(){

	for (std::size_t pinIdx = 0; pinIdx < 16; pinIdx++) {
		using Mode = stm32::mmreg::GPIO::Mode;
		if (mmreg::testBitsMasked(gpio.MODER.word, Mode::MODE_MASK, Mode::MODE_OUT, pinIdx * 2)){
			if (mmreg::testBitsMasked(gpio.BSRR.word, 1u, 1u, pinIdx)) {
				mmreg::setBits(gpio.ODR.halfword, 1u, pinIdx);
				mmreg::setBits(gpio.ODR.halfword, 1u, pinIdx);
				mmreg::clearBits(gpio.BSRR.word, 1u, pinIdx);
			}
			if (mmreg::testBitsMasked(gpio.BSRR.word, 1u, 1u, 16u + pinIdx)) {
				mmreg::clearBits(gpio.ODR.halfword, 1u, pinIdx);
				mmreg::clearBits(gpio.IDR.halfword, 1u, pinIdx);
				mmreg::clearBits(gpio.BSRR.word, 1u, 16u + pinIdx);
			}
		}
	}
}

template<>
void mocks::GpioMock<GpioStm32>::reset(){
	gpio.MODER.word = 0xFFFFFFFFU;
	gpio.OTYPER.word = 0;
	gpio.OSPEEDR.word = 0;
	gpio.PUPDR.word = 0;
	gpio.IDR.halfword = 0;
	gpio.ODR.halfword = 0;
	gpio.BSRR.word = 0;
	gpio.LCKR.word = 0;
	gpio.AFRL.word = 0;
	gpio.AFRH.word = 0;
}

