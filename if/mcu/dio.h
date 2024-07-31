#pragma once
/*
DIO = Digital IO = inputs-outputs that can be used directly as general-purpose inputs and outputs.
*/

#include <cstdint>
#include <ranges>

namespace dio {

// todo: Convert stm32::reg::GPIO::GPIO to a generic type
// so that this structure stays generic to any MCU architecture.
template<typename GpioRegs>
struct DioDef {
	GpioRegs &gpioRegs;
	// volatile struct stm32::reg::GPIO::GPIO &gpio;
	uint8_t pinNumber;
	enum class IoFunction : uint8_t {
		INPUT,
		OUTPUT,
		DONT_CARE
	} ioFunction;
	enum class IoType : uint8_t {
		PUSH_PULL,
		OPEN_DRAIN
	} ioType;
	enum class IoSpeed : uint8_t {
		LOW,
		MEDIUM,
		HIGH,
		VERY_HIGH
	} ioSpeed;
	enum class IoBias : uint8_t {
		NONE,
		PULL_UP,
		PULL_DOWN
	} ioBias;
	enum class IoInitState : uint8_t {
		LOGIC_LOW,
		LOGIC_HIGH,
		DONT_CARE,
	} ioInitState;

	void setLogicHigh() const;
	void setLogicLow() const;

	//	DioDef(GPIO &gpio, uint32_t pinNumber, IoFunction  ioFunction, IoType  ioType, IoSpeed  ioSpeed, IoBias ioBias, IoInitState ioInitState)
	//		: gpio(gpio), pinNumber(pinNumber),
	//		ioFunction(ioFunction), ioType(ioType), ioSpeed(ioSpeed), ioBias(ioBias), ioInitState(ioInitState)  {
	//	}
};

// This function is defined separately for each architecture.
template<typename GPIO>
void configure(const DioDef<GPIO> &dioDef);

template<std::ranges::range T>
void configure(const T &dioDefs) {
	for(auto &dioDef : dioDefs) {
		configure(dioDef);
	}
}

struct AssertType {};
struct AssertTypeLogicHigh : public AssertType {
	static constexpr bool valWhenAsserted = true;
};
struct AssertTypeLogicLow : public AssertType {
	static constexpr bool valWhenAsserted = false;
};

template<typename GPIO, typename Assert>
	requires std::derived_from<Assert, AssertType>
class DioAssertFunctor {
	const DioDef<GPIO> &dioDef;

	public:
	constexpr DioAssertFunctor(const DioDef<GPIO> &dioDef) :
			dioDef(dioDef) {}

	/* Function call operator. */
	void operator()(bool enable) const {
		if(enable == Assert::valWhenAsserted) {
			dioDef.setLogicHigh();
		} else {
			dioDef.setLogicLow();
		}
	}
};

}
