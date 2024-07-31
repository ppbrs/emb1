#include "if/mcu/chrono.h"
#include "arch/arm/armv6_m/mmreg/nvic.h"
#include "arch/arm/armv6_m/stm32f0/mmreg/rcc.h"
#include "arch/arm/armv6_m/stm32f0/mmreg/tim2-3.h"
#include "if/mcu/mmreg.h"
#include <cassert>
#include <chrono>

namespace {
uint32_t steadyClockSeconds = 0;
uint32_t highResolutionClockSeconds = 0;
}

void chrono::steady_clock::init() {
	// The 32-bit general-puropose timer TIM2 will be used as std::chrono::steady_clock,
	// which will run with a one-microsecond resolution.

	using namespace mmreg;
	namespace TIM2 = stm32f0::mmreg::TIM2;
	namespace NVIC = armv6_m::mmreg::NVIC;

	static constexpr uint32_t tim2Freq = 1'000'000;
	static constexpr uint16_t tim2Prescaler = static_cast<uint16_t>(tick::apbFreq / tim2Freq - 1);
	static_assert(tim2Freq == tick::apbFreq / (tim2Prescaler + 1));
	TIM2::TIM2.PSC = tim2Prescaler;
	// TIM2::TIM2.ARR = 1'000'000 - 1;
	TIM2::TIM2.ARR = 0xFFFF'FFFF;
	// Generating an update event so that the value of the prescaler is applied.
	writeBits(TIM2::TIM2.EGR.word, TIM2::EGRBits::UGSet);
	while(!testBitsMasked(TIM2::TIM2.SR.word, TIM2::SRBits::UIFMask, TIM2::SRBits::UIFSet)) {};
	clearBits(TIM2::TIM2.SR.word, TIM2::SRBits::UIFMask);

	// Enable update interrupt:
	setBitsMasked(TIM2::TIM2.DIER.word, TIM2::DIERBits::UIEMask, TIM2::DIERBits::UIESet);
	// todo: Explicitly set the highest priority, which is already set by default.
	setBitsMasked(NVIC::NVIC.ISER, (1 << 15), (1 << 15));

	// Start the timer:
	setBitsMasked(TIM2::TIM2.CR1.word, TIM2::CR1Bits::CENMask, TIM2::CR1Bits::CENSet);
}

void chrono::high_resolution_clock::init() {
	// The 16-bit general-puropose timer TIM3 will be used as std::chrono::steady_clock.
	// It will use the highest-possible resolution which can be represented in nanoseconds.
	// 48 Mhz / 6 = 8 MHz => 125 ns.

	using namespace mmreg;
	namespace TIM3 = stm32f0::mmreg::TIM3;
	namespace NVIC = armv6_m::mmreg::NVIC;

	static constexpr uint32_t tim3Freq = 8'000'000;
	static constexpr uint16_t tim3Prescaler = static_cast<uint16_t>(tick::apbFreq / tim3Freq - 1);
	static_assert(tim3Freq == tick::apbFreq / (tim3Prescaler + 1));
	TIM3::TIM3.PSC = tim3Prescaler;
	TIM3::TIM3.ARR = 0xFFFF;
	// Generating an update event so that the value of the prescaler is applied.
	writeBits(TIM3::TIM3.EGR.word, TIM3::EGRBits::UGSet);
	while(!testBitsMasked(TIM3::TIM3.SR.word, TIM3::SRBits::UIFMask, TIM3::SRBits::UIFSet))
		;
	clearBits(TIM3::TIM3.SR.word, TIM3::SRBits::UIFMask);

	// Enable update interrupt:
	setBitsMasked(TIM3::TIM3.DIER.word, TIM3::DIERBits::UIEMask, TIM3::DIERBits::UIESet);
	// todo: Explicitly set the highest priority, which is already set by default.
	setBitsMasked(NVIC::NVIC.ISER, (1 << 15), (1 << 15));

	// Start the timer:
	setBitsMasked(TIM3::TIM3.CR1.word, TIM3::CR1Bits::CENMask, TIM3::CR1Bits::CENSet);
}

// This must be the highest-priority interrupt.
void chrono::steady_clock::overflow() {
	using namespace mmreg;
	namespace TIM2 = stm32f0::mmreg::TIM2;
	clearBits(TIM2::TIM2.SR.word, TIM2::SRBits::UIFMask);
	steadyClockSeconds++;
}

// This must be the highest-priority interrupt.
void chrono::high_resolution_clock::overflow() {
	using namespace mmreg;
	namespace TIM3 = stm32f0::mmreg::TIM3;
	clearBits(TIM3::TIM3.SR.word, TIM3::SRBits::UIFMask);
	highResolutionClockSeconds++;
}

/*
now():								overflow():

cntHi0 = steadyClockSeconds;
while {
									(1) TIM2.CNT overflow, steadyClockSeconds increment;
	cntLo = TIM2.CNT;
									(2) TIM2.CNT overflow, steadyClockSeconds increment;
	cntHi = steadyClockSeconds;
	if (cntHi == cntHi0) {
		break;
	}
	cntHi0 = cntHi;

Case (1):

Case (2):
	There is some error in CNT because the function was interrupted.
}
*/
namespace std::chrono {
time_point<steady_clock> steady_clock::now() {
	namespace TIM2 = stm32f0::mmreg::TIM2;

	uint32_t cntHi0 = steadyClockSeconds;
	while(true) {
		uint32_t cntLo = TIM2::TIM2.CNT;
		uint32_t cntHi = steadyClockSeconds;
		if(cntHi == cntHi0) {
			uint64_t cnt = (((uint64_t)cntHi << 32) + cntLo) * 1000ull;
			duration dur(cnt); // size = 8
			time_point tp(dur); // size = 8
			return tp;
		}
		cntHi0 = cntHi;
	}
}

time_point<high_resolution_clock> high_resolution_clock::now() {
	namespace TIM3 = stm32f0::mmreg::TIM3;

	uint32_t cntHi0 = highResolutionClockSeconds;
	while(true) {
		uint32_t cntLo = TIM3::TIM3.CNT;
		uint32_t cntHi = highResolutionClockSeconds;
		if(cntHi == cntHi0) {
			uint64_t cnt = (((uint64_t)cntHi << 32) + cntLo) * 1000ull;
			duration dur(cnt); // size = 8
			time_point tp(dur); // size = 8
			return tp;
		}
		cntHi0 = cntHi;
	}
}

}

void __assert_func(const char *, int, const char *, const char *) {
	__asm__ volatile("bkpt #0\n");
	while(true)
		;
}
