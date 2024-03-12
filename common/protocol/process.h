#pragma once

#include "protocol.h"
#include <cstdint>
#include <string_view>
#include <vector>


namespace protocol {
namespace process {

template<class W>
Error split(const std::string_view &strv, W &words) {
	std::string_view delim = " ";

	size_t first = 0;
	while(first < strv.size()) {
		const auto second = strv.find_first_of(delim, first);
		if(first != second) {
			if(words.size() < words.capacity()) {
				words.emplace_back(strv.substr(first, second - first));
			} else {
				words.clear();
				return Error::TOO_MANY_WORDS;
			}
		}
		if(second == std::string_view::npos) {
			break;
		}
		first = second + 1;
	}
	return Error::OK;
}


template<class W>
Error parse(const W &words, CommandVariant &commandVariant) {
	Error error = Error::OK;

	commandVariant = CommandEmpty{};
	if(words.size() > 0) {
		if(words[0] == CommandRead::cmd) {
			commandVariant = CommandRead{};
			error = get<CommandRead>(commandVariant).parse(words);
		} else {
			error = Error::UNKNOWN_COMMAND;
		}
	}
	return error;
}

}
}
