#pragma once
/*
PIO = Peripheral IO = inputs-outputs belonging to peripherals like I2C, SPI.
*/

#include <cstdio>

namespace pio {

template<typename GPIO>
struct PioDef {
	volatile GPIO &gpio;
	uint8_t pinNumber;
	uint8_t alternateFunction;

	enum IoType : uint8_t { PUSH_PULL,
		OPEN_DRAIN } ioType;
	enum IoSpeed : uint8_t { LOW,
		MEDIUM,
		HIGH,
		VERY_HIGH } ioSpeed;
	enum IoBias : uint8_t { NONE,
		PULL_UP,
		PULL_DOWN } ioBias;
};

}
