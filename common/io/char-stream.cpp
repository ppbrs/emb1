#include "char-stream.h"
#include <algorithm>

io::CharStream &io::CharStream::operator<<(int32_t num) {
	constexpr uint32_t base = 10;
	char *ptrBefore = ptr;

	/* Handle 0 explicitly, otherwise empty string is printed for 0 */
	if(num == 0) {
		if(ptr == bufTop) {
			stateUnion.state.eofBit = 1;
			return *this;
		}
		*ptr++ = '0';
		return *this;
	}

	bool isNegative = num < 0;
	uint32_t absNum = static_cast<uint32_t>(isNegative ? -num : num);

	// Using repeated division by the given base, we get individual digits from the least
	// significant to the most significant digit.
	while(absNum != 0) {
		if(ptr == bufTop) {
			stateUnion.state.eofBit = 1;
			return *this;
		}
		int rem = absNum % base;
		*ptr++ = rem + '0';
		absNum = absNum / base;
	}

	if(isNegative) {
		if(ptr == bufTop) {
			stateUnion.state.eofBit = 1;
			return *this;
		}
		*ptr++ = '-';
	}

	reverse(ptrBefore, ptr - 1);
	return *this;
}

io::CharStream &io::CharStream::operator<<(uint32_t num) {
	constexpr uint32_t base = 10;
	char *ptrBefore = ptr;

	/* Handle 0 explicitly, otherwise empty string is printed for 0 */
	if(num == 0) {
		if(ptr == bufTop) {
			stateUnion.state.eofBit = 1;
			return *this;
		}
		*ptr++ = '0';
		return *this;
	}

	// Using repeated division by the given base, we get individual digits from the least
	// significant to the most significant digit.
	while(num != 0) {
		if(ptr == bufTop) {
			stateUnion.state.eofBit = 1;
			return *this;
		}
		int rem = num % base;
		*ptr++ = rem + '0';
		num = num / base;
	}

	reverse(ptrBefore, ptr - 1);
	return *this;
}

/* Reverse the string obtained after repeated division */
void io::CharStream::reverse(char *ptrBefore, char *ptrAfter) {
	while(ptrBefore < ptrAfter) {
		std::swap(*ptrBefore, *ptrAfter);
		ptrBefore++;
		ptrAfter--;
	}
}

io::CharStream &io::CharStream::operator<<(char ch) {
	if(ptr == bufTop) {
		stateUnion.state.eofBit = 1;
		return *this;
	}
	*ptr++ = ch;
	return *this;
}

io::CharStream &io::CharStream::operator<<(const std::string_view &sv) {
	if((ptr + sv.size()) > bufTop) {
		stateUnion.state.eofBit = 1;
		return *this;
	}
	memcpy(ptr, sv.data(), sv.size());
	ptr += sv.size();
	return *this;
}

std::string_view io::CharStream::view() {
	return std::string_view{buf, static_cast<size_t>(ptr - buf)};
}
