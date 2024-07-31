#pragma once

#include <optional>
#include <string_view>

namespace protocol {
class Option {
	public:
	enum class Type {
		UINT32, // uint32_t
		STRING,
		// TODO: INTEGRAL, FLOAT

		/*
		 */
		BOOL,
	};

	// std::string_view defaultToken;
	/*

	@param optParamStr Optional option parameter.
		nullopt - No paramter is needed for this option.
		empty string - A parameter is needed and it has no default value.
		non-empty string - A parameter is needed and this is its default value.
	*/
	Option(
		const std::string_view nameShort,
		const std::string_view nameLong,
		std::optional<const std::string_view> optParamStr,
		const Type type) :
			nameShort(nameShort),
			nameLong(nameLong),
			optParamStr(optParamStr),
			type(type),
			nameReceived(false),
			paramReceived(false) {
	}

	void setParam(const std::string_view &token) {
		this->optParamStr = token;
		paramReceived = true;
	}

	bool paramParse();

	// private:
	std::string_view nameShort;
	std::string_view nameLong;
	/* The option parameter.

	*/
	std::optional<std::string_view> optParamStr;
	/* The data type of the option parameter.*/
	Type type;

	/* The opton name was received */
	bool nameReceived;
	/* The opton parameter was received */
	bool paramReceived;

	/*
	Parsed value for types UINT32 and BOOL is saved in this variable.
	*/
	uint32_t paramUint32;
};
}
