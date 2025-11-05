#include "imult.h"
#include "test.h"
#include <array>
#include <cstdint>

namespace {

template<typename M1, typename M2, typename P>
struct TestCase {
	M1 multiplicand;
	M2 multiplier;
	P product;
};

using U32ByU32ToU32TestCase = TestCase<uint32_t, uint32_t, uint32_t>;
using U32ByU32ToU64TestCase = TestCase<uint32_t, uint32_t, uint64_t>;
using I32ByI32ToI64TestCase = TestCase<int32_t, int32_t, int64_t>;

constexpr std::array u32ByU32ToU32TestCases = {
	U32ByU32ToU32TestCase{9999u, 7777u, 77762223u},
	U32ByU32ToU32TestCase{0u, 0u, 0u},
	U32ByU32ToU32TestCase{0u, UINT32_MAX, 0u},
	U32ByU32ToU32TestCase{1u, UINT32_MAX, UINT32_MAX},
};

constexpr std::array u32ByU32ToU64TestCases = {
	U32ByU32ToU64TestCase{UINT32_MAX, UINT32_MAX, 0xfffffffe00000001},
	U32ByU32ToU64TestCase{0, UINT32_MAX, 0},
	U32ByU32ToU64TestCase{UINT32_MAX, 0, 0},
	U32ByU32ToU64TestCase{0xede36c3c, 0x62f7f975, 0x5bf77dab531ad36c},
	U32ByU32ToU64TestCase{0x446bdb29, 0x97efd078, 0x289bb6ae7ee70b38},
	U32ByU32ToU64TestCase{0xF8044FC9, 0x65E746AC, 0x62B9C3D61C15910C},
	U32ByU32ToU64TestCase{0x9EBB7800, 0xD46B3F47, 0x83B5BEF750864800},
	U32ByU32ToU64TestCase{0xECEE7A26, 0x8E368FF3, 0x839EC748F49D2C12},
};

constexpr std::array i32ByI32ToI64TestCases = {
	I32ByI32ToI64TestCase{INT32_MAX, INT32_MAX, 4611686014132420609},
	I32ByI32ToI64TestCase{INT32_MIN, INT32_MAX, -4611686016279904256},
	I32ByI32ToI64TestCase{INT32_MAX, INT32_MIN, -4611686016279904256},
	I32ByI32ToI64TestCase{INT32_MIN, INT32_MIN, 4611686018427387904},
	I32ByI32ToI64TestCase{-1408912876, 1132760601, -1595960996174398476},
};


}

void TestIMult::run() {
	for(const auto &tc : u32ByU32ToU32TestCases) {
		decltype(tc.product) product = tc.multiplicand * tc.multiplier;
		expectEq(tc.product, product);
	}

	for(const auto &tc : u32ByU32ToU32TestCases) {
		uint32_t productU32 = imultU32ByU32ToU32Arm32(tc.multiplicand, tc.multiplier);
		expectEq(tc.product, productU32);
	}

	for(const auto &tc : u32ByU32ToU64TestCases) {
		uint64_t multiplicandU64 = static_cast<uint64_t>(tc.multiplicand);
		decltype(tc.product) product = multiplicandU64 * tc.multiplier;
		// The above operation calls "__aeabi_lmul" from libgcc.
		// It computes the product of two 64-bit integer operands, and returns the 64-bit result.
		// Mathematically:
		// 	operands and return are long long
		// 	return = (operand1 × operand2) mod(2^64)
		//
		// int64_t __aeabi_lmul(int64_t i64op1, int64_t i64op2)
		//
		// The single function __aeabi_lmul is designed to handle both signed (long long) and
		// unsigned (unsigned long long) 64-bit multiplications because the low 64 bits of the
		// result are the same regardless of signedness.
		// The physical bit pattern resulting from an addition or multiplication is always the same,
		// regardless of whether the programmer interprets that pattern as a signed or unsigned
		// number.
		expectEq(tc.product, product);
	}

	for(const auto &tc : u32ByU32ToU64TestCases) {
		uint64_t productU64 = imultU32ByU32ToU64(tc.multiplicand, tc.multiplier);
		expectEq(tc.product, productU64);
	}

	for(const auto &tc : u32ByU32ToU64TestCases) {
		uint64_t productU64 = imultU32ByU32ToU64Arm32(tc.multiplicand, tc.multiplier);
		static_cast<void>(productU64);
		expectEq(tc.product, productU64);
	}

	for(const auto &tc : i32ByI32ToI64TestCases) {
		int64_t productI64 = imultI32ByI32ToI64(tc.multiplicand, tc.multiplier);
		expectEq(tc.product, productI64);
	}

	for(const auto &tc : i32ByI32ToI64TestCases) {
		int64_t productI64 = imultI32ByI32ToI64Arm32(tc.multiplicand, tc.multiplier);
		expectEq(tc.product, productI64);
	}
}
