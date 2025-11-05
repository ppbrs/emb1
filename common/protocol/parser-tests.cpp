
#include "./parse-result.h"
#include "./parser.h"
#include "./prog.h"
#include "3party/googletest/googletest/include/gtest/gtest.h"
#include "common/utility.h"
#include <iostream>
#include <optional>
#include <string_view>
#include <variant>

using std::cout, std::endl;

namespace protocol {

using ProgVar = std::variant<
	ProgUnknown,
	ProgMemory,
	ProgRandom>;
using OptProgVar = std::optional<ProgVar>;

template<class Prog>
struct TestData {
	std::string_view cmd;
	/* resultExpect is ignored for ProgUnknown tests. */
	ParseResult resultExpect;
	std::function<void(Prog)> checkFunc;
	TestData(
		std::string_view cmd,
		ParseResult resultExpect = ParseResult::UNKNOWN_COMMAND,
		std::function<void(Prog)> checkFunc = [](Prog) {}) :
			cmd(cmd), resultExpect(resultExpect), checkFunc(checkFunc) {};
};

class ProtocolParserTestsProgUnknown : public ::testing::TestWithParam<TestData<ProgUnknown>> {};
class ProtocolParserTestsProgMemory : public ::testing::TestWithParam<TestData<ProgMemory>> {};
class ProtocolParserTestsProgRandom : public ::testing::TestWithParam<TestData<ProgRandom>> {};
class ProtocolParserTestsEmpty : public ::testing::Test {};

/* TestFixtureName = ProtocolParserTestsProgUnknown, TestName = Basic */
TEST_P(ProtocolParserTestsProgUnknown, Basic) {
	const TestData<ProgUnknown> testData = GetParam();

	OptProgVar optProgVar = std::nullopt;
	ParseResult result = parseCmd(testData.cmd, optProgVar);

	const std::size_t type_index = get_variant_type_index<ProgUnknown, ProgVar>::value;
	ASSERT_EQ(type_index, optProgVar.value().index());

	ASSERT_EQ(ParseResult::UNKNOWN_COMMAND, result);
}

/* TestFixtureName = ProtocolParserTestsProgMemory, TestName = Basic */
TEST_P(ProtocolParserTestsProgMemory, Basic) {
	const TestData<ProgMemory> testData = GetParam();

	OptProgVar optProgVar = std::nullopt;
	ParseResult result = parseCmd(testData.cmd, optProgVar);

	const std::size_t type_index = get_variant_type_index<ProgMemory, ProgVar>::value;
	ASSERT_EQ(type_index, optProgVar.value().index());

	ASSERT_EQ(testData.resultExpect, result);
	if(result == ParseResult::SUCCESS) {
		ProgMemory prog = std::get<ProgMemory>(optProgVar.value());
		testData.checkFunc(prog);
	}
}

/* TestFixtureName = ProtocolParserTestsProgRandom, TestName = Basic */
TEST_P(ProtocolParserTestsProgRandom, Basic) {
	const TestData<ProgRandom> testData = GetParam();

	OptProgVar optProgVar = std::nullopt;
	ParseResult result = parseCmd(testData.cmd, optProgVar);

	const std::size_t type_index = get_variant_type_index<ProgRandom, ProgVar>::value;
	ASSERT_EQ(type_index, optProgVar.value().index());

	ASSERT_EQ(testData.resultExpect, result);
	if(result == ParseResult::SUCCESS) {
		ProgRandom prog = std::get<ProgRandom>(optProgVar.value());
		testData.checkFunc(prog);
	}
}


TEST_F(ProtocolParserTestsEmpty, Basic) {
	OptProgVar optProgVar = std::nullopt;
	ParseResult result = parseCmd("", optProgVar);
	ASSERT_EQ(result, ParseResult::EMPTY_COMMAND);
}

/* InstantiationName = X */

INSTANTIATE_TEST_SUITE_P(
	X, ProtocolParserTestsProgMemory,
	::testing::Values(
		// -----------------------------------------------------------------------------------------
		// Correct requests.
		/* 0 */ TestData<ProgMemory>{
			"memory --address 0x12345678 -f u32 -s 7", ParseResult::SUCCESS,
			[](ProgMemory prog) {
				ASSERT_EQ(prog.options.at(ProgMemory::OptionIndex::ADDRESS).paramUint32, 0x12345678u);
				ASSERT_EQ(prog.options.at(ProgMemory::OptionIndex::FORMAT).optParamStr.value(), "u32");
				ASSERT_EQ(prog.options.at(ProgMemory::OptionIndex::SIZE).paramUint32, 7u);
			}},
		/* 1 */ TestData<ProgMemory>{"memory --address 1 -f u16", ParseResult::SUCCESS, [](ProgMemory prog) {
										 ASSERT_EQ(prog.options.at(ProgMemory::OptionIndex::ADDRESS).paramUint32, 1u);
										 ASSERT_EQ(prog.options.at(ProgMemory::OptionIndex::FORMAT).optParamStr.value(), "u16");
										 ASSERT_EQ(prog.options.at(ProgMemory::OptionIndex::SIZE).paramUint32, 1u);
									 }},
		/* 2 */ TestData<ProgMemory>{"memory -a 2", ParseResult::SUCCESS, [](ProgMemory prog) {
										 ASSERT_EQ(prog.options.at(ProgMemory::OptionIndex::ADDRESS).paramUint32, 2u);
										 ASSERT_EQ(prog.options.at(ProgMemory::OptionIndex::FORMAT).optParamStr.value(), "u32");
										 ASSERT_EQ(prog.options.at(ProgMemory::OptionIndex::SIZE).paramUint32, 1u);
									 }},
		// -----------------------------------------------------------------------------------------
		// Commands with an missing option or option parameter.
		/* 3 */ TestData<ProgMemory>{
			"memory",
			ParseResult::OPTION_MISSING,
		},
		/* 4 */ TestData<ProgMemory>{
			"memory -a",
			ParseResult::OPTION_PARAMETER_MISSING,
		},
		// -----------------------------------------------------------------------------------------
		// Wrong option parameter.
		/* 5 */ TestData<ProgMemory>{
			"memory --address x -f u32 -s 7",
			ParseResult::OPTION_PARAMETER_ERROR,
		},
		// -----------------------------------------------------------------------------------------
		// Commands with an unknown option.
		/* 6 */ TestData<ProgMemory>{
			"memory --unknown-option --address 1 -f u8 -s 1",
			ParseResult::UNKNOWN_OPTION,
		},
		/* 7 */ TestData<ProgMemory>{
			"memory --address 1 -f u8 -s 1 --unknown-option 1234",
			ParseResult::UNKNOWN_OPTION,
		},
		// -----------------------------------------------------------------------------------------
		// Help requestst.
		/* 8 */ TestData<ProgMemory>{
			"memory -h", // Pure help request.
			ParseResult::HELP_REQUEST,
		},
		/* 9 */ TestData<ProgMemory>{
			"memory -h -a 0", // Help request with a known option.
			ParseResult::HELP_REQUEST,
		},
		/* 10 */ TestData<ProgMemory>{
			"memory -h -x 0", // Help request with an unknown option.
			ParseResult::HELP_REQUEST,
		}));

INSTANTIATE_TEST_SUITE_P(
	X, ProtocolParserTestsProgRandom,
	::testing::Values(
		// -----------------------------------------------------------------------------------------
		/* 0
		All options are provided. */
		TestData<ProgRandom>{
			"random -f u32 -s 3", ParseResult::SUCCESS,
			[](ProgRandom prog) {
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::FORMAT).optParamStr.value(), "u32");
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::SIZE).paramUint32, 3u);
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::CRYPTO).paramUint32, 0u);
			}},
		/* 1
		Only --format option is provided. */
		TestData<ProgRandom>{
			"random -f u8", ParseResult::SUCCESS,
			[](ProgRandom prog) {
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::FORMAT).optParamStr.value(), "u8");
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::SIZE).paramUint32, 1u);
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::CRYPTO).paramUint32, 0u);
			}},
		/* 2
		Only --size option is provided. */
		TestData<ProgRandom>{
			"random -s 4", ParseResult::SUCCESS,
			[](ProgRandom prog) {
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::FORMAT).optParamStr.value(), "u32");
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::SIZE).paramUint32, 4u);
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::CRYPTO).paramUint32, 0u);
			}},
		/* 3
		No options provided. Default size and format should be used. */
		TestData<ProgRandom>{
			"random", ParseResult::SUCCESS,
			[](ProgRandom prog) {
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::FORMAT).optParamStr.value(), "u32");
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::SIZE).paramUint32, 1u);
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::CRYPTO).paramUint32, 0u);
			}},
		/* 4
		--crypto is given with a parameter. */
		TestData<ProgRandom>{
			"random -c 1", ParseResult::SUCCESS,
			[](ProgRandom prog) {
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::FORMAT).optParamStr.value(), "u32");
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::SIZE).paramUint32, 1u);
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::CRYPTO).paramUint32, 1u);
			}},
		/* 5
		--crypto is given with a parameter, then another option follows. */
		TestData<ProgRandom>{
			"random -c 1 -s 6", ParseResult::SUCCESS,
			[](ProgRandom prog) {
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::FORMAT).optParamStr.value(), "u32");
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::SIZE).paramUint32, 6u);
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::CRYPTO).paramUint32, 1u);
			}},
		/* 6
		--crypto is given without a parameter. */
		TestData<ProgRandom>{
			"random -c", ParseResult::SUCCESS,
			[](ProgRandom prog) {
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::FORMAT).optParamStr.value(), "u32");
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::SIZE).paramUint32, 1u);
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::CRYPTO).paramUint32, 1u);
			}},
		/* 7
		--crypto is given without a parameter, then another option follows. */
		TestData<ProgRandom>{
			"random -c -s 7", ParseResult::SUCCESS,
			[](ProgRandom prog) {
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::FORMAT).optParamStr.value(), "u32");
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::SIZE).paramUint32, 7u);
				ASSERT_EQ(prog.options.at(ProgRandom::OptionIndex::CRYPTO).paramUint32, 1u);
			}},
		// -----------------------------------------------------------------------------------------
		/* 8
		Pure help request. */
		TestData<ProgRandom>{
			"random -h",
			ParseResult::HELP_REQUEST}));

INSTANTIATE_TEST_SUITE_P(
	X, ProtocolParserTestsProgUnknown,
	::testing::Values(
		/* 0 */ TestData<ProgUnknown>{"qwerty0"},
		/* 1 */ TestData<ProgUnknown>{"qwerty10 qwerty11"}));

} /* protocol */
