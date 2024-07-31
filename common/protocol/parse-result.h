#pragma once

namespace protocol {

enum class ParseResult {
	SUCCESS,
	EMPTY_COMMAND,
	UNKNOWN_COMMAND,
	UNKNOWN_OPTION,
	/*
	An obligatory option was not provided.
	*/
	OPTION_MISSING,
	/*
	An obligatory option parameter was not provided.
	*/
	OPTION_PARAMETER_MISSING,
	/*
	Option parameter error.
	For example, a string that is supposed to represent a numeric value
	could not be parsed.
	*/
	OPTION_PARAMETER_ERROR,
	HELP_REQUEST,
};

}
