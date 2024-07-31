#pragma once

#include "pio.h"
// #include <cstdint>
#include <ranges>

namespace i2c {

template<typename I2C, typename GPIO>
struct
	I2cDef {
	I2C &i2c;
	const pio::PioDef<GPIO> &sclDef;
	const pio::PioDef<GPIO> &sdaDef;
};


// This function is defined separately for each architecture.
template<typename I2C, typename GPIO>
void configure(const I2cDef<I2C, GPIO> &i2cDef);

template<std::ranges::range T>
void configure(const T &i2cDefs) {
	for(auto &i2cDef : i2cDefs) {
		configure(i2cDef);
	}
}

}
