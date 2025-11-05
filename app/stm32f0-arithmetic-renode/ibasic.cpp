#include "ibasic.h"
/* Make a uint64_t using inline assembly. */
// [[gnu::used,gnu::noinline]]
uint64_t makeU64(uint32_t lo, uint32_t hi) {
	uint64_t result;
	asm volatile(
		"movs r0, %[lo]\n\r"
		"movs r1, %[hi]\n\r"
		: "=r"(result)
		: [lo] "r"(lo), [hi] "r"(hi)
		: "r0", "r1");
	return result;
}
