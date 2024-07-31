#include "./option.h"
#include "3party/googletest/googletest/include/gtest/gtest.h"

template<protocol::Option::Type OptionType>
struct TestData {
	protocol::Option optionObj;
	const std::string_view paramStr;
	const bool parseResult;
	const uint32_t paramUint32;
};

using TestDataUint32 = TestData<protocol::Option::Type::UINT32>;
using TestDataBool = TestData<protocol::Option::Type::BOOL>;
using Option = protocol::Option;

class ProtocolOptionTestsUINT32 : public ::testing::TestWithParam<TestDataUint32> {};
class ProtocolOptionTestsBOOL : public ::testing::TestWithParam<TestDataBool> {};

TEST_P(ProtocolOptionTestsUINT32, Basic) {
	TestDataUint32 testData = GetParam();
	testData.optionObj.setParam(testData.paramStr);
	ASSERT_EQ(testData.optionObj.paramParse(), testData.parseResult);
	if(testData.parseResult) {
		ASSERT_EQ(testData.paramUint32, testData.optionObj.paramUint32);
	}
}

TEST_P(ProtocolOptionTestsBOOL, Basic) {
	TestDataBool testData = GetParam();
	testData.optionObj.setParam(testData.paramStr);
	ASSERT_EQ(testData.optionObj.paramParse(), testData.parseResult);
	if(testData.parseResult) {
		ASSERT_EQ(testData.paramUint32, testData.optionObj.paramUint32);
	}
}

INSTANTIATE_TEST_SUITE_P(
	X, ProtocolOptionTestsUINT32,
	::testing::Values(
		/* Some real values. */
		/* 0 */ TestDataUint32{Option("", "", "", Option::Type::UINT32), "1234", true, 1234},
		/* 1 */ TestDataUint32{Option("", "", "", Option::Type::UINT32), "0x1234", true, 0x1234},
		/* 2 */ TestDataUint32{Option("", "", "", Option::Type::UINT32), "1234h", true, 0x1234},

		/* Minimum uin32_t. */
		/* 3 */ TestDataUint32{Option("", "", "", Option::Type::UINT32), "0", true, 0},
		/* 4 */ TestDataUint32{Option("", "", "", Option::Type::UINT32), "0x00000000", true, 0},
		/* 5 */ TestDataUint32{Option("", "", "", Option::Type::UINT32), "00000000h", true, 0},

		/* Maximum uin32_t. */
		/* 6 */ TestDataUint32{Option("", "", "", Option::Type::UINT32), "4294967295", true, 4294967295},
		/* 7 */ TestDataUint32{Option("", "", "", Option::Type::UINT32), "0xFFFFFFFF", true, 0xFFFFFFFF},
		/* 8 */ TestDataUint32{Option("", "", "", Option::Type::UINT32), "FFFFFFFFh", true, 0xFFFFFFFF},

		/* Other types. */
		/* 9 */ TestDataUint32{Option("", "", "", Option::Type::UINT32), "qwerty", false, 0},
		/* 10 */ TestDataUint32{Option("", "", "", Option::Type::UINT32), "-1234", false, 0},

		/* More than can fit into uint32_t. */
		/* 11 */ TestDataUint32{Option("", "", "", Option::Type::UINT32), "4294967296", false, 0},
		/* 12 */ TestDataUint32{Option("", "", "", Option::Type::UINT32), "0x100000000", false, 0}));

INSTANTIATE_TEST_SUITE_P(
	X, ProtocolOptionTestsBOOL,
	::testing::Values(
		// -----------------------------------------------------------------------------------------
		/* Some real values. */
		/* 0 */ TestDataBool{Option("", "", "", Option::Type::BOOL), "1", true, 1},
		/* 1 */ TestDataBool{Option("", "", "", Option::Type::BOOL), "true", true, 1},
		/* 2 */ TestDataBool{Option("", "", "", Option::Type::BOOL), "y", true, 1},
		/* 3 */ TestDataBool{Option("", "", "", Option::Type::BOOL), "", true, 1},
		/* 4 */ TestDataBool{Option("", "", "", Option::Type::BOOL), "0", true, 0},
		/* 5 */ TestDataBool{Option("", "", "", Option::Type::BOOL), "false", true, 0},
		/* 6 */ TestDataBool{Option("", "", "", Option::Type::BOOL), "n", true, 0},

		// -----------------------------------------------------------------------------------------
		/* 7 */ TestDataBool{Option("", "", "", Option::Type::BOOL), "2", false, 0}));
