#include "if/mcu/debug.h"

#include "arch/arm/armv7e_m//mmreg/debug.h"
#include "arch/arm/armv7e_m/mmreg/itm.h"
#include "arch/arm/stm32/mmreg/gpio.h"
#include "arch/arm/armv7e_m/stm32h7/mmreg/debug.h" // todo
#include "if/mcu/mmreg.h"

namespace debug {
	constexpr uint32_t swoBaudRate = 2'000'000;
}


void debug::swvInit(uint32_t sysFreq) {
	(void)sysFreq;

	/* Clocking */
	stm32h7::mmreg::DEBUG::DBGMCU::DBGMCU.CR.bits.TRACECLKEN = 1;

	/* Enable ITM trace. */
	armv7e_m::mmreg::DEBUG::DEBUG.DEMCR.bits.TRCENA = 1;
	armv7e_m::mmreg::ITM::ITM.TER[0] = 0b1111; // Enable stimulus ports 0, 1, 2, and 3.

	/* Enable SWO. Inspired by https://gist.github.com/tstellanova/107cb66cd0599fa20cca1fce9556468c */
	using stm32h7::mmreg::DEBUG::SWO::SWO, stm32h7::mmreg::DEBUG::SWTF::SWTF;
	// 1) Unlock funnel
	SWTF.LAR = 0xC5ACCE55;
	SWO.LAR = 0xC5ACCE55;
	// 2) SWO current output divisor register
	uint32_t swoPrescaler = (sysFreq / swoBaudRate) - 1;
	SWO.CODR.bits.PRESCALER = swoPrescaler;
	// 3) SWO selected pin protocol register
	SWO.SPPR.bits.PPROT = SWO.SPPR.bits.PPROTNRZ;
	// 4) Enable ITM input of SWO trace funnel
	SWTF.CTRL.bits.ENS0 = 1;

	// TODO: This is stm32h7-specific code and should be moved somewhere.

	// Configure PB3 to AF0, which corresponds to TRACESWO.
	// (which turns out to be pointless since PB3 is configured as TRACESWO by default)
	auto &GPIOB = stm32::mmreg::GPIO::GPIOB;
	mmreg::setBitsMasked(GPIOB.OSPEEDR.word, GPIOB.OSPEEDR.mask, GPIOB.OSPEEDR.veryHighSpeed, 2 * 3);
	mmreg::setBitsMasked(GPIOB.MODER.word, GPIOB.MODER.mask, GPIOB.MODER.alternatFunctionMode, 2 * 3);
	GPIOB.AFRL.bits.AFRL3 = 0;
}

void debug::swvSendChar(int8_t ch) {
	auto &stimulusReg0 = armv7e_m::mmreg::ITM::ITM.STIM[0];
	auto &stimulusReg1 = armv7e_m::mmreg::ITM::ITM.STIM[1];
	// auto &stimulusReg2 = armv7e_m::mmreg::ITM::ITM.STIM[2];
	// auto &stimulusReg3 = armv7e_m::mmreg::ITM::ITM.STIM[3];

	while(!(stimulusReg0.read.FIFOREADY & 1));
	stimulusReg0.write.u8 = (int8_t)ch;
	stimulusReg0.write.u16 = (int8_t)ch + 1;
	stimulusReg0.write.u32 = (int8_t)ch + 2;

	while(!(stimulusReg1.read.FIFOREADY & 1));
	stimulusReg1.write.u8 = (int8_t)ch + 16;
	stimulusReg1.write.u16 = (int8_t)ch + 16 + 1;
	stimulusReg1.write.u32 = (int8_t)ch + 16 + 2;

	// while(!(stimulusReg2.read.FIFOREADY & 1));
	// stimulusReg1.write.u8 = (int8_t)ch + 2;

	// while(!(stimulusReg3.read.FIFOREADY & 1));
	// stimulusReg1.write.u8 = (int8_t)ch + 3;
}
