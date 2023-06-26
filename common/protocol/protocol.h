#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>
#include <variant>

namespace protocol {

constexpr std::size_t MAX_WORDS_NUM = 8;

enum class Error {
	OK,

	TOO_MANY_WORDS,
	UNKNOWN_COMMAND,

};

class CommandEmpty {
};


class CommandRead {
public:
	uint32_t address;
	uint32_t num_words;

	static constexpr std::string_view cmd {"read"};

	template<class W>
	Error parse(const W &words) {
		(void)words;

		State state = State::IDLE;
		for(size_t i = 1; i < words.size(); i++) {
			switch(state) {
				case State::IDLE:
					break;
			}
		}

		return Error::OK;
	}

private:
	enum class State {
		IDLE
	};

};


using CommandVariant = 	std::variant<CommandEmpty, CommandRead>;


}