#include "ibasic.h"
#include "test.h"
#include <array>
#include <cstdint>

void TestIBasic::run() {
	expectEq(static_cast<uint64_t>(0x0123'4567'89AB'CDEF), makeU64(0x89AB'CDEF, 0x0123'4567));
	expectEq(static_cast<uint64_t>(0x89AB'CDEF'0123'4567), makeU64(0x0123'4567, 0x89AB'CDEF));
}
