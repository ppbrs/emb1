#pragma once
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string_view>

namespace io {

/*
This class resembles std::stringstream with some distinctions:
1) It uses the provided character buffer.
2) It doesn't allow this buffer to overflow.
*/
class CharStream {
	public:
	CharStream(char *buf_, std::size_t bufLen_) :
			buf(buf_),
			bufTop(buf_ + bufLen_),
			ptr(buf_),
			stateUnion({0}) {
	}
	CharStream &operator<<(int32_t);
	CharStream &operator<<(uint32_t);
	CharStream &operator<<(char);
	CharStream &operator<<(const char *) = delete;
	CharStream &operator<<(const std::string_view &);

	std::string_view view();

	bool good() {
		return stateUnion.byte == 0;
	}

	bool eof() {
		return stateUnion.state.eofBit;
	}

	struct State {
		uint8_t badBit : 1;
		uint8_t failBit : 1;
		uint8_t eofBit : 1;
	};
	static_assert(sizeof(State) == 1);

	private:
	void reverse(char *bufBefore, char *bufAfter);

	char *const buf;
	/* bufTop points to the first memory location beyond the buffer. */
	char *const bufTop;
	char *ptr;

	union StateUnion {
		uint8_t byte;
		State state;
	} stateUnion;
	static_assert(sizeof(StateUnion) == 1);
};
}
