#include "imult.h"
#include <cmath>

/* Modulo 2^32 multiplication */
uint32_t imultU32ByU32ToU32Arm32(uint32_t a, uint32_t b) {
	uint32_t product = 0;
	static_cast<void>(a);
	static_cast<void>(b);
	__asm__ __volatile__(
		".syntax unified			\n\t" // Enable Unified Assembly Language (UAL)
		".thumb						\n\t" // Switch to Thumb mode (UAL for Thumb)
		"muls %[p], %[a], %[b]		\n\r"
		: [p] "=r"(product)
		: [a] "r"(a), [b] "r"(b)
		: "cc"); /* "condition codes", meaning flags in PSR are modified ("dirty"). */
	return product;
}

/*
Full unsigned multiplication.

The full product A × B is:
P = A × B
= (AH × 2^16 + AL) × (BH × 2^16 + BL)

Expanding this gives 4 partial products, which are all 32-bit values:
AH × BH × 2^32 = PHH × 2^32
AH × BL × 2^16 = PHL × 2^16
AL × BH × 2^16 = PLH × 2^16
AL × BL = PLL

Let's introduce PX or P-cross:
PX = PHL + PLH

The result will be composed from the above partial products:
PL = PLL + PHL × 2^16 + PLH × 2^16
PH = PHH + hi-of-PHL + hi-of-PLH + carry-from-PLL
*/
template<bool useBuiltinAddOverflow>
uint64_t imultU32ByU32ToU64(uint32_t a, uint32_t b) {
	uint32_t al = a & 0x0000'FFFF;
	uint32_t bl = b & 0x0000'FFFF;
	uint32_t ah = a >> 16;
	uint32_t bh = b >> 16;

	uint32_t pl = al * bl;
	uint32_t ph = ah * bh;

	uint32_t phl = ah * bl;
	uint32_t carry;

	if constexpr(useBuiltinAddOverflow) {
		// On AArch32, 'uint32_t' is equivalent to 'unsigned long'.
		// For portable code, you may use __builtin_add_overflow here - the compiler will
		// choose the right implementation automatically.
		carry = __builtin_add_overflow(pl, (phl << 16), &pl);
	} else {
		pl += (phl << 16);
		carry = pl < (phl << 16);
	}
	ph += (phl >> 16) + carry;

	uint32_t plh = al * bh;

	if constexpr(useBuiltinAddOverflow) {
		carry = __builtin_add_overflow(pl, (plh << 16), &pl);
	} else {
		pl += (plh << 16);
		carry = pl < (plh << 16);
	}
	ph += (plh >> 16) + carry;

	return (static_cast<uint64_t>(ph) << 32) + pl;
}

uint64_t imultU32ByU32ToU64Arm32(uint32_t a, uint32_t b) {
	uint32_t pl, ph;
	pl = a;
	ph = b;
	__asm__ __volatile__(
		".syntax unified			\n\t" // Enable Unified Assembly Language (UAL)
		".thumb						\n\t" // Switch to Thumb mode (UAL for Thumb)
		// Prepare al, ah, bl, bh
		"uxth	r4, r0				\n\t" // r4 = al
		// UXTH extracts bits[15:0] and zero extends to 32 bits.
		"lsrs	r2, r0, #16			\n\t" // r2 = ah
		"uxth	r5, r1				\n\t" // r5 = bl
		"lsrs	r3, r1, #16			\n\t" // r3 = bh
		// Calculate partial products
		"mov	r6, r4				\n\t"
		"muls	r6, r5				\n\t" // r6 = r4 * r5 = al * bl = ppl
		"mov	r7, r2				\n\t"
		"muls	r7, r5				\n\t" // r7 = r2 * r5 = ah * bl = pphl
		"muls	r4, r3				\n\t" // r4 = r4 * r3 = al * bh = pplh
		"muls	r2, r3				\n\t" // r2 = r2 + r3 = ah * bh = pph
		// Combine partial products
		"lsrs	r3, r7, #16			\n\t" // r3 = (pphl >> 16)
		"lsls	r7, r7, #16			\n\t" // r7 = (pphl << 16)
		//
		"adds	r6, r6, r7			\n\t" // r6 = ppl + (pphl << 16), carry1
		"adcs	r2, r2, r3			\n\t" // r2 = pph + (pphl >> 16) + carry1
		//
		"lsrs	r3, r4, #16			\n\t" // r3 = (pplh >> 16)
		"lsls	r4, r4, #16			\n\t" // r4 = (pplh << 16)
		//
		"adds	%[pl], r6, r4		\n\t" // pl = ppl + (pphl << 16) + (pplh << 16), carry2
		"adcs	r2, r2, r3			\n\t" // ph = pph + (pphl >> 16) + carry1 + (pplh >> 16) + carry2
		"mov	%[ph], r2			\n\t"
		//
		: [pl] "=&r"(pl), [ph] "=&r"(ph)
		: [a] "r"(a), [b] "r"(b)
		: "cc", "r2", "r3", "r4", "r5", "r6", "r7");
	// cc = condition codes, meaning flags in PSR are modified ("dirty")
	// WARNING: using r7 requires -fomit-frame-pointer
	return (static_cast<uint64_t>(ph) << 32) + pl;
}

/* Full signed multiplication. */
int64_t imultI32ByI32ToI64(int32_t a, int32_t b) {
	uint32_t aU32 = static_cast<uint32_t>(std::abs(a));
	uint32_t bU32 = static_cast<uint32_t>(std::abs(b));
	bool signA = a < 0;
	bool signB = b < 0;
	auto pU64 = imultU32ByU32ToU64(aU32, bU32);
	return (signA != signB) ? -static_cast<int64_t>(pU64) : static_cast<int64_t>(pU64);
}

/* Full signed multiplication. */
int64_t imultI32ByI32ToI64Arm32(int32_t a, int32_t b) {
	uint32_t aU32 = static_cast<uint32_t>(std::abs(a));
	uint32_t bU32 = static_cast<uint32_t>(std::abs(b));
	bool signA = a < 0;
	bool signB = b < 0;
	auto pU64 = imultU32ByU32ToU64Arm32(aU32, bU32);
	return (signA != signB) ? -static_cast<int64_t>(pU64) : static_cast<int64_t>(pU64);
}
