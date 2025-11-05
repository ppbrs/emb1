#include "common/protocol/prog.h"

void protocol::ProgBase::_collect(
	const std::string_view &token,
	std::array<Option, 0>::iterator optionsBegin,
	std::array<Option, 0>::iterator optionsEnd) {
	// Check a specific scenario, such as $ random -c -s 7.
	// A boolean option name (-s) was received and its parameter is omitted, which implies it is TRUE.
	// Then one more option follows (-s 7).
	bool tokenMayBeOption = (token.starts_with("--") or token.starts_with("-"));
	bool prevOptionIsBool = pCurOption != nullptr and pCurOption->type == Option::Type::BOOL;
	if(prevOptionIsBool and tokenMayBeOption) {
		pCurOption = nullptr;
	}

	if(not pCurOption) {
		if(token.starts_with("--")) {
			// This is a long option.
			std::string_view nameLong = token.substr(2);
			for(auto option = optionsBegin; option != optionsEnd; ++option) {
				if(option->nameLong == nameLong) {
					pCurOption = &(*option);
					pCurOption->nameReceived = true;
					break;
				}
			}
			if(not pCurOption) {
				if(nameLong == "help") {
					helpRequest = true;
				} else {
					unknownOption = true;
				}
			}
		} else if(token.starts_with("-")) {
			// This is a short option.
			std::string_view nameShort = token.substr(1);
			for(auto option = optionsBegin; option != optionsEnd; ++option) {
				if(option->nameShort == nameShort) {
					pCurOption = &(*option);
					pCurOption->nameReceived = true;
					break;
				}
			}
			if(not pCurOption) {
				if(nameShort == "h") {
					helpRequest = true;
				} else {
					unknownOption = true;
				}
			}
		}
	} else {
		pCurOption->setParam(token);
		pCurOption = nullptr;
	}
}


protocol::ParseResult protocol::ProgBase::_parse(
	std::array<Option, 0>::iterator optionsBegin,
	std::array<Option, 0>::iterator optionsEnd) {
	if(helpRequest) {
		return protocol::ParseResult::HELP_REQUEST;
	}
	if(unknownOption) {
		return protocol::ParseResult::UNKNOWN_OPTION;
	}
	// Check that all options were received.
	// Convert all option parameter strings to values
	for(auto option = optionsBegin; option != optionsEnd; ++option) {
		if(not option->optParamStr.has_value() or option->optParamStr.value() == "") {
			if(option->nameReceived) {
				return protocol::ParseResult::OPTION_PARAMETER_MISSING;
			} else {
				return protocol::ParseResult::OPTION_MISSING;
			}
		}
		if(not option->paramParse()) {
			return protocol::ParseResult::OPTION_PARAMETER_ERROR;
		}
	}
	return protocol::ParseResult::SUCCESS;
};

void protocol::ProgMemory::collect(const std::string_view &token) {
	_collect(token, options.begin(), options.end());
}

protocol::ParseResult protocol::ProgMemory::parse() {
	return _parse(options.begin(), options.end());
};

void protocol::ProgRandom::collect(const std::string_view &token) {
	_collect(token, options.begin(), options.end());
}

protocol::ParseResult protocol::ProgRandom::parse() {
	return _parse(options.begin(), options.end());
};

/*
This function is supposed to be overriden in the application.
*/
[[gnu::weak]] void protocol::ProgMemory::execute() {};

/*
This function is supposed to be overriden in the application.
*/
[[gnu::weak]] void protocol::ProgRandom::execute() {};
