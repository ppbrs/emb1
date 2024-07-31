#pragma once

#include <concepts>
#include <cstdint>

namespace mmreg {

/*
In general, the mask is always without any offset. Offset is optional.
typename M is not restricted yet, because it can be an enum (e.g. OMode)
*/

template<std::unsigned_integral T, typename M>
void clearBits(volatile T &reg, M mask, std::size_t offset = 0) {
	reg = reg & (~(static_cast<T>(mask) << offset));
}

template<std::unsigned_integral T, typename M>
void setBits(volatile T &reg, M bits, std::size_t offset = 0) {
	reg = reg | (static_cast<T>(bits) << offset);
}

template<std::unsigned_integral T, typename M>
void writeBits(volatile T &reg, M bits, std::size_t offset = 0) {
	reg = (static_cast<T>(bits) << offset);
}

/*
When setting only one bit, it makes no sense to call setBitsMasked(...);
setBits(...) will do the job.
*/
template<std::unsigned_integral T, typename M>
void setBitsMasked(volatile T &reg, M mask, M bits, std::size_t offset = 0) {
	reg = (reg & (~(static_cast<T>(mask) << offset))) | (static_cast<T>(bits) << offset);
}

template<std::unsigned_integral T, typename M>
T getBits(const volatile T &reg, M mask, std::size_t offset = 0) {
	return (reg >> offset) & static_cast<T>(mask);
}

template<std::unsigned_integral T, typename M>
bool testBitsMasked(volatile T &reg, M mask, M bits, std::size_t offset = 0) {
	return (reg & (static_cast<T>(mask) << offset)) == (static_cast<T>(bits) << offset);
}

}
