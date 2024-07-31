#include "if/mcu/pio.h"
#include "arch/arm/stm32/mmreg/gpio.h"
#include "if/mcu/mmreg.h"

using PioDefStm32 = pio::PioDef<GpioRegsStm32>;

// Partial specialization of dio::configure<T>:
template<>
void pio::configure<GpioRegsStm32>(const PioDefStm32 &pioDef) {
	using mmreg::setBitsMasked;

	auto &otypeReg = pioDef.gpioRegs.OTYPER.word;
	const auto otypeMask = stm32::mmreg::GPIO::OTYPE_MASK;
	switch(pioDef.ioType) {
		default:
		case PioDefStm32::IoType::PUSH_PULL: {
			setBitsMasked(otypeReg, otypeMask, stm32::mmreg::GPIO::OTYPE_PP, pioDef.pinNumber);
			break;
		}
		case PioDefStm32::IoType::OPEN_DRAIN: {
			setBitsMasked(otypeReg, otypeMask, stm32::mmreg::GPIO::OTYPE_OD, pioDef.pinNumber);
			break;
		}
	}

	auto &pupdReg = pioDef.gpioRegs.PUPDR.word;
	const auto pupdMask = stm32::mmreg::GPIO::PUPD_MASK;
	switch(pioDef.ioBias) {
		default:
		case PioDefStm32::IoBias::NONE: {
			setBitsMasked(pupdReg, pupdMask, stm32::mmreg::GPIO::PUPD_NONE, 2 * pioDef.pinNumber);
			break;
		}
		case PioDefStm32::IoBias::PULL_UP: {
			setBitsMasked(pupdReg, pupdMask, stm32::mmreg::GPIO::PUPD_PU, 2 * pioDef.pinNumber);
			break;
		}
		case PioDefStm32::IoBias::PULL_DOWN: {
			setBitsMasked(pupdReg, pupdMask, stm32::mmreg::GPIO::PUPD_PD, 2 * pioDef.pinNumber);
			break;
		}
	}

	auto &ospeedReg = pioDef.gpioRegs.OSPEEDR.word;
	const auto ospeedMask = stm32::mmreg::GPIO::OSPEED_MASK;
	switch(pioDef.ioSpeed) {
		default:
		case PioDefStm32::IoSpeed::LOW: {
			setBitsMasked(ospeedReg, ospeedMask, stm32::mmreg::GPIO::OSPEED_LOW, 2 * pioDef.pinNumber);
			break;
		}
		case PioDefStm32::IoSpeed::MEDIUM: {
			setBitsMasked(ospeedReg, ospeedMask, stm32::mmreg::GPIO::OSPEED_MEDIUM, 2 * pioDef.pinNumber);
			break;
		}
		case PioDefStm32::IoSpeed::HIGH: {
			setBitsMasked(ospeedReg, ospeedMask, stm32::mmreg::GPIO::OSPEED_HIGH, 2 * pioDef.pinNumber);
			break;
		}
		case PioDefStm32::IoSpeed::VERY_HIGH: {
			setBitsMasked(ospeedReg, ospeedMask, stm32::mmreg::GPIO::OSPEED_VERY_HIGH, 2 * pioDef.pinNumber);
			break;
		}
	}

	auto &afr = (pioDef.pinNumber < 8) ? pioDef.gpioRegs.AFRL.word : pioDef.gpioRegs.AFRH.word;
	const uint32_t afrMask = (uint32_t)stm32::mmreg::GPIO::AFR::MASK;
	setBitsMasked(afr, afrMask, (uint32_t)pioDef.alternateFunction, 4u * (pioDef.pinNumber % 8));

	auto &modeReg32 = pioDef.gpioRegs.MODER.word;
	const uint32_t modeMask = stm32::mmreg::GPIO::MODE_MASK;
	setBitsMasked(modeReg32, modeMask, stm32::mmreg::GPIO::MODER::alternatFunctionMode, 2 * pioDef.pinNumber);
}
