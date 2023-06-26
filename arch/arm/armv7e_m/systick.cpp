#include "if/mcu/systick.h"
#include "arch/arm/armv7e_m/mmreg/systick.h"
#include "if/mcu/tick.h"

namespace SysTick = armv7e_m::mmreg::SysTick;

namespace systick {
}

/**
 * @brief Initializes the processor’s SysTick timer.
 */
void systick::init() {
	SysTick::SYST.RVR = tick::systemTimerReloadValue;
	SysTick::SYST.CVR = 0;
	SysTick::CSR csr = {};
	csr.bits.ENABLE = 1;
	csr.bits.CLKSOURCE = 1;
	csr.bits.TICKINT = 1;
	SysTick::SYST.CSR.word = csr.word;
}
