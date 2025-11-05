#pragma once
/*
PIO = Peripheral IO = inputs-outputs belonging to peripherals like I2C, SPI.
*/

#include <cstdint>
#include <cstdio>

namespace pio {

template<typename GpioRegs>
struct PioDef {
	GpioRegs &gpioRegs; // e.g. GPIOA.
	uint8_t pinNumber; // 0..15.
	uint8_t alternateFunction; // AF0..AF7.
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
};

template<typename GpioRegs>
void configure(const PioDef<GpioRegs> &pioDef);

}
