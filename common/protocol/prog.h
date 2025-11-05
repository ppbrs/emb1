#pragma once

#include "option.h"
#include "parse-result.h"
#include <array>

namespace protocol {
/*
Base class for classes that hold parsed commands.
Each program has its own class.
*/
class ProgBase {
	public:
	ProgBase() :
			pCurOption(nullptr),
			helpRequest(false),
			unknownOption(false) {
	}
	/*
	Process one more token.
	*/
	virtual void collect(const std::string_view &) = 0;
	/*
	All tokens were collected.
	Now we can try to parse the program.
	*/
	virtual ParseResult parse() = 0;
	virtual void execute() = 0;

	// private:
	protected:
	Option *pCurOption;
	bool helpRequest;
	bool unknownOption;

	void _collect(
		const std::string_view &,
		std::array<Option, 0>::iterator optionsBegin,
		std::array<Option, 0>::iterator optionsEnd);
	ParseResult _parse(
		std::array<Option, 0>::iterator optionsBegin,
		std::array<Option, 0>::iterator optionsEnd);
};

class ProgUnknown final : public ProgBase {
	public:
	ProgUnknown() {};
	static constexpr std::string_view progToken = "";
	static constexpr std::string_view helpString = "";
	virtual void collect(const std::string_view &) override {};
	virtual ParseResult parse() override {
		return ParseResult::UNKNOWN_COMMAND;
	};
	virtual void execute() override {};
};

class ProgMemory final : public ProgBase {
	public:
	static constexpr std::string_view progToken = "memory";
	static constexpr std::string_view helpString = ("memory: Read and print memory contents.\n"
													"\t--address (-a): 0..0xFFFFFFFF\n"
													"\t--format(-f): u32|u32h|i32|u16|u16h|i16|u8|u8h|i8 = u32\n"
													"\t--size (-s): 1..8 = 1\n");
	static constexpr std::string_view sizeDefault = "1";
	static constexpr std::string_view formatDefault = "u32";
	enum OptionIndex : uint8_t {
		ADDRESS,
		FORMAT,
		SIZE,
		NUM_OPTIONS,
	};
	std::array<Option, OptionIndex::NUM_OPTIONS> options;
	ProgMemory() :
			ProgBase(),
			options({Option("a", "address", "", Option::Type::UINT32),
				Option("f", "format", formatDefault, Option::Type::STRING),
				Option("s", "size", sizeDefault, Option::Type::UINT32)}) {
	}

	virtual void collect(const std::string_view &token) override final;
	virtual ParseResult parse() override final;
	virtual void execute() override;

	private:
};

class ProgRandom final : public ProgBase {
	public:
	static constexpr std::string_view progToken = "random";
	static constexpr std::string_view helpString = ("random: Generate and print random numbers.\n"
													"\t--format(-f): u32|u32h|i32|u16|u16h|i16|u8|u8h|i8 = u32\n"
													"\t--size (-s): 1..8 = 1\n"
													"\t--crypto (-c): bool = false\n");
	static constexpr std::string_view sizeDefault = "1";
	static constexpr std::string_view formatDefault = "u32";
	static constexpr std::string_view cryptoDefault = "0";
	enum OptionIndex : uint8_t {
		FORMAT,
		SIZE,
		CRYPTO,
		NUM_OPTIONS,
	};
	std::array<Option, OptionIndex::NUM_OPTIONS> options;
	ProgRandom() :
			ProgBase(),
			options({Option("f", "format", formatDefault, Option::Type::STRING),
				Option("s", "size", sizeDefault, Option::Type::UINT32),
				Option("c", "crypto", cryptoDefault, Option::Type::BOOL)}) {
	}

	virtual void collect(const std::string_view &token) override final;
	virtual ParseResult parse() override final;
	virtual void execute() override;
};

}
