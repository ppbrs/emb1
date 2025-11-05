#include "test_imult.h"
#include <cstdint>
#include <array>

namespace {

template <typename M1, typename M2, typename P>
struct TestCase {
	M1 multiplicand;
	M2 multiplier;
	P product;
};

using U32ByU32ToU32TestCase = TestCase<uint32_t, uint32_t, uint32_t>;


constexpr std::array u32ByU32toU32TestCases = {
	U32ByU32ToU32TestCase{9999u, 7777u, 77762223u},
	U32ByU32ToU32TestCase{0u, 0u, 0u},
	U32ByU32ToU32TestCase{0u, UINT32_MAX, 0u},
	U32ByU32ToU32TestCase{1u, UINT32_MAX, UINT32_MAX},
};
}

void TestIMult::setUp() {
}

void TestIMult::run() {

	for (const auto tc: u32ByU32toU32TestCases){
		decltype(tc.product) product = tc.multiplicand * tc.multiplier;
		expectEq(tc.product, product);
	}
	// {
	// 	const int32_t factor1 = 9999;
	// 	const int32_t factor2 = -7777;
	// 	int32_t product = factor1 * factor2;
	// 	expectEq(static_cast<int32_t>(-77762223), product);
	// }
}

void TestIMult::tearDown() {
}
