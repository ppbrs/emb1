#include "if/mcu/mcu-init.h"
#include "./io.h"
#include "arch/arm/armv6_m/mmreg/nvic.h"
#include "arch/arm/armv6_m/stm32f0/mmreg/rcc.h"
#include "arch/arm/stm32/i2c.h"
#include "arch/arm/stm32/mmreg/i2c.h"
#include "if/mcu/chrono.h"
#include "if/mcu/i2c.h"
#include "if/mcu/mmreg.h"
#include "if/mcu/pio.h"
#include <array>

//
// DIOs for Discovery051 board:
//
// LD3 (green) for PC9 output (active high)
// LD4 (blue) for PC8 output (active high)
//
static constexpr std::array<DioDef, DioNames::NUM_DIO> dioDefs = {{
	{// LED3_GREEN
		stm32::mmreg::GPIO::GPIOC, 9,
		DioDef::IoFunction::OUTPUT,
		DioDef::IoType::PUSH_PULL,
		DioDef::IoSpeed::LOW,
		DioDef::IoBias::NONE,
		DioDef::IoInitState::LOGIC_LOW},
	{// LED4_BLUE
		stm32::mmreg::GPIO::GPIOC, 8,
		DioDef::IoFunction::OUTPUT,
		DioDef::IoType::PUSH_PULL,
		DioDef::IoSpeed::LOW,
		DioDef::IoBias::NONE,
		DioDef::IoInitState::LOGIC_LOW},
}};

const DioDef &dioLED3Green = dioDefs[LED3_GREEN];
const DioDef &dioLED4Blue = dioDefs[LED4_BLUE];

const dio::DioAssertFunctor<volatile struct stm32::mmreg::GPIO::GPIO, dio::AssertTypeLogicHigh> assertFuncLED3Green{dioDefs[DioNames::LED3_GREEN]};
const dio::DioAssertFunctor<volatile struct stm32::mmreg::GPIO::GPIO, dio::AssertTypeLogicHigh> assertFuncLED4Blue{dioDefs[DioNames::LED4_BLUE]};

static constexpr std::array<PioDef, PioNames::NUM_PIO> pioDefs = {{
	{
		// I2C1_SCL, PB6
		stm32::mmreg::GPIO::GPIOB,
		6,
		1,
		PioDef::IoType::OPEN_DRAIN,
		PioDef::IoSpeed::HIGH,
		PioDef::IoBias::PULL_UP,
	},
	{
		// I2C1_SDA, PB7
		stm32::mmreg::GPIO::GPIOB,
		7,
		1,
		PioDef::IoType::OPEN_DRAIN,
		PioDef::IoSpeed::HIGH,
		PioDef::IoBias::PULL_UP,
	},
	{
		// I2C2_SCL, PB10
		stm32::mmreg::GPIO::GPIOB,
		10,
		1,
		PioDef::IoType::OPEN_DRAIN,
		PioDef::IoSpeed::HIGH,
		PioDef::IoBias::PULL_UP,
	},
	{
		// I2C2_SDA, PB11
		stm32::mmreg::GPIO::GPIOB,
		11,
		1,
		PioDef::IoType::OPEN_DRAIN,
		PioDef::IoSpeed::HIGH,
		PioDef::IoBias::PULL_UP,
	},
}};

// todo: move to comm.h
enum I2cNames {
	I2C1,
	I2C2,
	NUM_I2C,
};

static constexpr std::array<I2cDef, I2cNames::NUM_I2C> i2cDefs = {{
	{
		// I2C1
		stm32::mmreg::I2C::I2C1,
		pioDefs[PioNames::I2C1_SCL],
		pioDefs[PioNames::I2C1_SDA],
	},
	{
		// I2C2
		stm32::mmreg::I2C::I2C2,
		pioDefs[PioNames::I2C2_SCL],
		pioDefs[PioNames::I2C2_SDA],
	},
}};

void mcuInit::systemClock::initTree() {
	using namespace mmreg;
	namespace RCC = stm32f0::mmreg::RCC;

	/* List of available clocks:
	 * HSI 8 MHz RC oscillator clock
	 * HSE oscillator clock
	 * PLL clock
	 * 40 kHz low speed internal RC (LSI RC)
	 * 32.768 kHz low speed external crystal (LSE crystal)
	 * 14 MHz high speed internal RC (HSI14) dedicated for ADC
	 */

	/* Maximum core frequency is 48 MHz.
	The maximum frequency of the AHB and the APB domains (HCLK and PCLK) is 48 MHz.

	The internal RC 8 MHz oscillator is selected as default CPU clock on reset.
	An external 4 to 32 MHz crystal oscillator can be connected, but its not populated on
	the DiscoveryF0 board.
	*/

	/* To modify the PLL configuration, proceed as follows:
	1.Disable the PLL by setting PLLON to 0.
	2.Wait until PLLRDY is cleared. The PLL is now fully stopped.
	3.Change the desired parameter.
	4.Enable the PLL again by setting PLLON to 1.
	5.Wait until PLLRDY is set. */
	clearBits(RCC::RCC.CR.word, RCC::CRBits::PLLONMask);
	while(getBits(RCC::RCC.CR.word, RCC::CRBits::PLLRDYMask))
		;
	setBitsMasked(RCC::RCC.CFGR.word, RCC::CFGRBits::PLLMULMask, RCC::CFGRBits::PLLMULx12);
	setBitsMasked(RCC::RCC.CFGR.word, RCC::CFGRBits::PLLSRCMask, RCC::CFGRBits::PLLSRCHSI);
	setBitsMasked(RCC::RCC.CFGR.word, RCC::CFGRBits::PPREMask, RCC::CFGRBits::PPRENoDiv);
	setBitsMasked(RCC::RCC.CFGR.word, RCC::CFGRBits::HPREMask, RCC::CFGRBits::HPRENoDiv);

	setBitsMasked(RCC::RCC.CR.word, RCC::CRBits::PLLONMask, RCC::CRBits::PLLONOn);
	while(!getBits(RCC::RCC.CR.word, RCC::CRBits::PLLRDYMask))
		;

	/* After a system reset, the HSI oscillator is selected as system clock. */
	setBitsMasked(RCC::RCC.CFGR.word, RCC::CFGRBits::SWMask, RCC::CFGRBits::SWPLL);
	while(getBits(RCC::RCC.CFGR.word, RCC::CFGRBits::SWSMask) != RCC::CFGRBits::SWSPLL)
		;

	/* Enable IO ports */
	setBitsMasked(RCC::RCC.AHBENR.word,
		RCC::AHBENRBits::IOPAENMask + RCC::AHBENRBits::IOPBENMask + RCC::AHBENRBits::IOPCENMask + RCC::AHBENRBits::IOPFENMask,
		RCC::AHBENRBits::IOPAENSet + RCC::AHBENRBits::IOPBENSet + RCC::AHBENRBits::IOPCENSet + RCC::AHBENRBits::IOPFENSet);

	/* Enable I2C; set I2C1 clock source is SysClk */
	setBitsMasked(RCC::RCC.CFGR3.word, RCC::CFGR3Bits::I2C1SWMask, RCC::CFGR3Bits::I2C1SWSysClk);
	setBitsMasked(RCC::RCC.CFGR3.word, RCC::APB1ENRBits::I2C1ENMask, RCC::APB1ENRBits::I2C1ENSet);
	setBitsMasked(RCC::RCC.APB1ENR.word, RCC::APB1ENRBits::I2C2ENMask, RCC::APB1ENRBits::I2C2ENSet);
}

void mcuInit::systemClock::initChrono() {
	chrono::steady_clock::init();
	chrono::high_resolution_clock::init();
}

void mcuInit::io::init() {
	dio::configure(dioDefs);
}

void mcuInit::comm::init() {
	i2c::configure(i2cDefs);
}
