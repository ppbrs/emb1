#include "test_imult.h"
#include <cstdint>

void TestIMult::setUp() {
}

void TestIMult::run() {
	{
		const uint32_t factor1 = 9999;
		const uint32_t factor2 = 7777;
		uint32_t product = factor1 * factor2;
		expectEq(static_cast<uint32_t>(77762223u), product);
	}
	{
		const int32_t factor1 = 9999;
		const int32_t factor2 = -7777;
		int32_t product = factor1 * factor2;
		expectEq(static_cast<int32_t>(-77762223), product);
	}
}

void TestIMult::tearDown() {
}
