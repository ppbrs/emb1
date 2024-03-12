#include <cstdint>
#include <cstring>

void *memset(void *dest, int ch, std::size_t count) {
	uint8_t *p = (uint8_t *)dest;
	for(std::size_t i = 0; i < count; i++) {
		*p++ = ch;
	}
	return dest;
}
