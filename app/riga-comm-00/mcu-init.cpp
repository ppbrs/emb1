// This source file belongs to riga-comm-00 project.
#include "if/mcu/mcu-init.h"
#include "./app.h"
#include "./io.h"
#include "./usart.h"
#include "arch/arm/armv6_m/mmreg/nvic.h"
#include "arch/arm/armv6_m/stm32f0/mmreg/rcc.h"
#include "arch/arm/armv6_m/stm32f0/usart.h"
#include "if/mcu/mmreg.h"
#include "if/mcu/pio.h"
#include "if/mcu/usart.h"
#include <array>

//
// DIOs for Riga board:
//
// LD3 (green) for PC9 output (active high)
// LD4 (blue) for PC8 output (active high)
//
using GpioRegs = volatile stm32::mmreg::GPIO::GPIO;

static constexpr std::array<DioDef, (size_t)DioNames::NUM> dioDefs = {{
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

static const DioDef &dioLED3Green = dioDefs[(size_t)DioNames::LED3_GREEN];
static const DioDef &dioLED4Blue = dioDefs[(size_t)DioNames::LED4_BLUE];

const dio::DioAssertFunctor<GpioRegs, dio::AssertTypeLogicHigh> assertFuncLED3Green{dioLED3Green};
const dio::DioAssertFunctor<GpioRegs, dio::AssertTypeLogicHigh> assertFuncLED4Blue{dioLED4Blue};

static constexpr std::array<PioDef, (size_t)PioNames::NUM> pioDefs = {{
	{
		// USART2_RX, // PA2
		stm32::mmreg::GPIO::GPIOA,
		2,
		1,
		PioDef::IoType::PUSH_PULL,
		PioDef::IoSpeed::HIGH,
		PioDef::IoBias::NONE,
	},
	{
		// USART2_TX, // PA3
		stm32::mmreg::GPIO::GPIOA,
		3,
		1,
		PioDef::IoType::PUSH_PULL,
		PioDef::IoSpeed::HIGH,
		PioDef::IoBias::NONE,
	},
}};

static constexpr std::array<UsartDefF0, (size_t)UsartNames::NUM> usartDefs = {{
	{
		// CONSOLE
		stm32f0::mmreg::USART::USART2, // regs
		pioDefs[(size_t)PioNames::USART2_TX], // txPioDef
		pioDefs[(size_t)PioNames::USART2_RX], // rxPioDef
		app::init, // initFunc
		app::consumeByteFromISR, // consumeByteFromISR
		app::getNextTxByte, // isrGetNextTx
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
	while(!getBits(RCC::RCC.CR.word, RCC::CRBits::PLLRDYMask)) {};

	/* After a system reset, the HSI oscillator is selected as system clock. */
	setBitsMasked(RCC::RCC.CFGR.word, RCC::CFGRBits::SWMask, RCC::CFGRBits::SWPLL);
	while(getBits(RCC::RCC.CFGR.word, RCC::CFGRBits::SWSMask) != RCC::CFGRBits::SWSPLL) {};

	/* Enable IO ports */
	setBitsMasked(RCC::RCC.AHBENR.word,
		RCC::AHBENRBits::IOPAENMask + RCC::AHBENRBits::IOPBENMask + RCC::AHBENRBits::IOPCENMask + RCC::AHBENRBits::IOPFENMask,
		RCC::AHBENRBits::IOPAENSet + RCC::AHBENRBits::IOPBENSet + RCC::AHBENRBits::IOPCENSet + RCC::AHBENRBits::IOPFENSet);

	/* Enable I2C; set I2C1 clock source is SysClk */
	setBitsMasked(RCC::RCC.CFGR3.word, RCC::CFGR3Bits::I2C1SWMask, RCC::CFGR3Bits::I2C1SWSysClk);
	setBitsMasked(RCC::RCC.CFGR3.word, RCC::APB1ENRBits::I2C1ENMask, RCC::APB1ENRBits::I2C1ENSet);
	setBitsMasked(RCC::RCC.APB1ENR.word, RCC::APB1ENRBits::I2C2ENMask, RCC::APB1ENRBits::I2C2ENSet);

	/* Enable USART2; */
	setBitsMasked(RCC::RCC.APB1ENR.word, RCC::APB1ENRBits::USART2ENMask, RCC::APB1ENRBits::USART2ENSet);
}

void mcuInit::systemClock::initChrono() {
}

void mcuInit::io::init() {
	dio::configure(dioDefs);
}

void mcuInit::comm::init() {
	usart::configure(usartDefs);
}
