
#include "if/mcu/dio.h"
#include "arch/arm/stm32/mmreg/gpio.h"
#include "if/mcu/mmreg.h"

// using GPIOStm32 = volatile struct stm32::mmreg::GPIO::GPIO;
using DioDefStm32 = dio::DioDef<volatile struct stm32::mmreg::GPIO::GPIO>;

// Partial specialization of dio::configure<T>:
template<>
void dio::configure<volatile struct stm32::mmreg::GPIO::GPIO>(const DioDefStm32 &dioDef) {
	switch(dioDef.ioFunction) {
		default:
		case DioDefStm32::IoFunction::INPUT:
			break;
		case DioDefStm32::IoFunction::OUTPUT:
			switch(dioDef.ioType) {
				default:
				case DioDefStm32::IoType::PUSH_PULL: {
					mmreg::setBitsMasked(dioDef.gpio.OTYPER.word, stm32::mmreg::GPIO::OTYPE_MASK, stm32::mmreg::GPIO::OTYPE_PP, dioDef.pinNumber);
					break;
				}
				case DioDefStm32::IoType::OPEN_DRAIN: {
					mmreg::setBitsMasked(dioDef.gpio.OTYPER.word, stm32::mmreg::GPIO::OTYPE_MASK, stm32::mmreg::GPIO::OTYPE_OD, dioDef.pinNumber);
					break;
				}
			}
			switch(dioDef.ioBias) {
				default:
				case DioDefStm32::IoBias::NONE: {
					mmreg::setBitsMasked(dioDef.gpio.PUPDR.word, stm32::mmreg::GPIO::PUPD_MASK, stm32::mmreg::GPIO::PUPD_NONE, 2 * dioDef.pinNumber);
					break;
				}
				case DioDefStm32::IoBias::PULL_UP: {
					mmreg::setBitsMasked(dioDef.gpio.PUPDR.word, stm32::mmreg::GPIO::PUPD_MASK, stm32::mmreg::GPIO::PUPD_PU, 2 * dioDef.pinNumber);
					break;
				}
				case DioDefStm32::IoBias::PULL_DOWN: {
					mmreg::setBitsMasked(dioDef.gpio.PUPDR.word, stm32::mmreg::GPIO::PUPD_MASK, stm32::mmreg::GPIO::PUPD_PD, 2 * dioDef.pinNumber);
					break;
				}
			}
			switch(dioDef.ioSpeed) {
				default:
				case DioDefStm32::IoSpeed::LOW: {
					mmreg::setBitsMasked(dioDef.gpio.OSPEEDR.word, stm32::mmreg::GPIO::OSPEED_MASK, stm32::mmreg::GPIO::OSPEED_LOW, 2 * dioDef.pinNumber);
					break;
				}
				case DioDefStm32::IoSpeed::MEDIUM: {
					mmreg::setBitsMasked(dioDef.gpio.OSPEEDR.word, stm32::mmreg::GPIO::OSPEED_MASK, stm32::mmreg::GPIO::OSPEED_MEDIUM, 2 * dioDef.pinNumber);
					break;
				}
				case DioDefStm32::IoSpeed::HIGH: {
					mmreg::setBitsMasked(dioDef.gpio.OSPEEDR.word, stm32::mmreg::GPIO::OSPEED_MASK, stm32::mmreg::GPIO::OSPEED_HIGH, 2 * dioDef.pinNumber);
					break;
				}
				case DioDefStm32::IoSpeed::VERY_HIGH: {
					mmreg::setBitsMasked(dioDef.gpio.OSPEEDR.word, stm32::mmreg::GPIO::OSPEED_MASK, stm32::mmreg::GPIO::OSPEED_VERY_HIGH, 2 * dioDef.pinNumber);
					break;
				}
			}
			switch(dioDef.ioInitState) {
				default:
				case DioDefStm32::IoInitState::LOGIC_LOW: {
					mmreg::setBitsMasked(dioDef.gpio.ODR.halfword, stm32::mmreg::GPIO::ODATA_MASK, stm32::mmreg::GPIO::ODATA_LOW, dioDef.pinNumber);
					break;
				}
				case DioDefStm32::IoInitState::LOGIC_HIGH: {
					mmreg::setBitsMasked(dioDef.gpio.ODR.halfword, stm32::mmreg::GPIO::ODATA_MASK, stm32::mmreg::GPIO::ODATA_HIGH, dioDef.pinNumber);
					break;
				}
			}
			mmreg::setBitsMasked(dioDef.gpio.MODER.word, stm32::mmreg::GPIO::MODE_MASK, stm32::mmreg::GPIO::MODE_OUT, 2 * dioDef.pinNumber);
			break;
	}
}

template<>
void DioDefStm32::setLogicHigh() const {
	mmreg::setBits(this->gpio.BSRR.word, 1u, pinNumber);
}
template<>
void DioDefStm32::setLogicLow() const {
	mmreg::setBits(this->gpio.BSRR.word, 1u, 16u + pinNumber);
}
