#include <cstdint>
#include <cstring>

[[gnu::weak]] void *memset(void *dest, int ch, std::size_t count) {
	// Builtin doesn't work on F0 for yet unknown reasons.
	// return __builtin_memset(dest, ch, count);

	uint8_t *p = (uint8_t *)dest;
	for(std::size_t i = 0; i < count; i++) {
		*p++ = ch;
	}
	return dest;
}

[[gnu::weak]] void *memcpy(void *dest, const void *src, std::size_t count) {
	// Builtin doesn't work on F0 for yet unknown reasons.
	// return __builtin_memcpy(dest, src, count);

	uint8_t *pDest = (uint8_t *)dest;
	const uint8_t *pSrc = (uint8_t *)src;
	for(std::size_t i = 0; i < count; i++) {
		*pDest++ = *pSrc++;
	}
	return dest;
}
