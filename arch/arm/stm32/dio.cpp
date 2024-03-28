#include "if/mcu/dio.h"
#include "arch/arm/stm32/mmreg/gpio.h"
#include "if/mcu/mmreg.h"

using DioDefStm32 = dio::DioDef<GpioRegsStm32>;

// Partial specialization of dio::configure<T>:
template<>
void dio::configure<GpioRegsStm32>(const DioDefStm32 &dioDef) {
	using mmreg::setBitsMasked;
	switch(dioDef.ioFunction) {
		default:
		case DioDefStm32::IoFunction::INPUT:
			break;
		case DioDefStm32::IoFunction::OUTPUT:
			switch(dioDef.ioType) {
				default:
				case DioDefStm32::IoType::PUSH_PULL: {
					setBitsMasked(dioDef.gpioRegs.OTYPER.word, stm32::mmreg::GPIO::OTYPE_MASK, stm32::mmreg::GPIO::OTYPE_PP, dioDef.pinNumber);
					break;
				}
				case DioDefStm32::IoType::OPEN_DRAIN: {
					setBitsMasked(dioDef.gpioRegs.OTYPER.word, stm32::mmreg::GPIO::OTYPE_MASK, stm32::mmreg::GPIO::OTYPE_OD, dioDef.pinNumber);
					break;
				}
			}
			switch(dioDef.ioBias) {
				default:
				case DioDefStm32::IoBias::NONE: {
					setBitsMasked(dioDef.gpioRegs.PUPDR.word, stm32::mmreg::GPIO::PUPD_MASK, stm32::mmreg::GPIO::PUPD_NONE, 2 * dioDef.pinNumber);
					break;
				}
				case DioDefStm32::IoBias::PULL_UP: {
					setBitsMasked(dioDef.gpioRegs.PUPDR.word, stm32::mmreg::GPIO::PUPD_MASK, stm32::mmreg::GPIO::PUPD_PU, 2 * dioDef.pinNumber);
					break;
				}
				case DioDefStm32::IoBias::PULL_DOWN: {
					setBitsMasked(dioDef.gpioRegs.PUPDR.word, stm32::mmreg::GPIO::PUPD_MASK, stm32::mmreg::GPIO::PUPD_PD, 2 * dioDef.pinNumber);
					break;
				}
			}

			switch(dioDef.ioSpeed) {
				default:
				case DioDefStm32::IoSpeed::LOW: {
					setBitsMasked(dioDef.gpioRegs.OSPEEDR.word, stm32::mmreg::GPIO::OSPEED_MASK, stm32::mmreg::GPIO::OSPEED_LOW, 2 * dioDef.pinNumber);
					break;
				}
				case DioDefStm32::IoSpeed::MEDIUM: {
					setBitsMasked(dioDef.gpioRegs.OSPEEDR.word, stm32::mmreg::GPIO::OSPEED_MASK, stm32::mmreg::GPIO::OSPEED_MEDIUM, 2 * dioDef.pinNumber);
					break;
				}
				case DioDefStm32::IoSpeed::HIGH: {
					setBitsMasked(dioDef.gpioRegs.OSPEEDR.word, stm32::mmreg::GPIO::OSPEED_MASK, stm32::mmreg::GPIO::OSPEED_HIGH, 2 * dioDef.pinNumber);
					break;
				}
				case DioDefStm32::IoSpeed::VERY_HIGH: {
					setBitsMasked(dioDef.gpioRegs.OSPEEDR.word, stm32::mmreg::GPIO::OSPEED_MASK, stm32::mmreg::GPIO::OSPEED_VERY_HIGH, 2 * dioDef.pinNumber);
					break;
				}
			}
			switch(dioDef.ioInitState) {
				default:
				case DioDefStm32::IoInitState::LOGIC_LOW: {
					setBitsMasked(dioDef.gpioRegs.ODR.halfword, stm32::mmreg::GPIO::ODATA_MASK, stm32::mmreg::GPIO::ODATA_LOW, dioDef.pinNumber);
					break;
				}
				case DioDefStm32::IoInitState::LOGIC_HIGH: {
					setBitsMasked(dioDef.gpioRegs.ODR.halfword, stm32::mmreg::GPIO::ODATA_MASK, stm32::mmreg::GPIO::ODATA_HIGH, dioDef.pinNumber);
					break;
				}
			}
			setBitsMasked(dioDef.gpioRegs.MODER.word, stm32::mmreg::GPIO::MODE_MASK, stm32::mmreg::GPIO::MODE_OUT, 2 * dioDef.pinNumber);
			break;
	}
}

template<>
void DioDefStm32::setLogicHigh() const {
	mmreg::setBits(this->gpioRegs.BSRR.word, 1u, pinNumber);
}
template<>
void DioDefStm32::setLogicLow() const {
	mmreg::setBits(this->gpioRegs.BSRR.word, 1u, 16u + pinNumber);
}
