#include "./char-stream.h"
#include "3party/googletest/googletest/include/gtest/gtest.h"
#include <cstdint>
#include <sstream>
#include <string_view>
#include <vector>

using namespace std::string_view_literals;

/* This structure is used for testing overflows. */
template<typename T>
struct OverflowTestParam {
	size_t bufLen;
	std::vector<T> values;
	/* Last value in values causes eof. */
	bool lastValueOverflows;
};

class CharStreamTestsInt32 : public ::testing::TestWithParam<int32_t> {};
class CharStreamTestsUint32 : public ::testing::TestWithParam<uint32_t> {};
class CharStreamTestsChar : public ::testing::TestWithParam<char> {};
class CharStreamTestsStringView : public ::testing::TestWithParam<std::string_view> {};

class CharStreamTestsMultipleData : public ::testing::Test {};

class CharStreamTestsInt32Overflow : public ::testing::TestWithParam<OverflowTestParam<int32_t>> {};
class CharStreamTestsUint32Overflow : public ::testing::TestWithParam<OverflowTestParam<uint32_t>> {};
class CharStreamTestsCharOverflow : public ::testing::TestWithParam<OverflowTestParam<char>> {};
class CharStreamTestsStringViewOverflow : public ::testing::TestWithParam<OverflowTestParam<std::string_view>> {};

template<typename T>
void charStreamTest(T &testData) {
	char buf[32] = {}; // The buffer is big enough to not worry about overflow.
	io::CharStream objUnderTest(buf, sizeof(buf));
	objUnderTest << testData;
	auto objUnderTestView = objUnderTest.view();

	ASSERT_TRUE(objUnderTest.good());
	ASSERT_FALSE(objUnderTest.eof());

	std::stringstream ss;
	ss << testData;
	auto ssView = ss.view();

	ASSERT_EQ(ssView.size(), objUnderTestView.size()) << "Length: expected " << ssView.size() << ", got " << objUnderTestView.size() << ".";
	ASSERT_EQ(ssView.compare(objUnderTestView), 0) << "Char array: expected `" << ssView << "`, got `" << objUnderTestView << "`.";
}

TEST_P(CharStreamTestsInt32, SingleData) {
	auto param = GetParam();
	static_assert(std::is_same<decltype(param), int32_t>::value);
	charStreamTest(GetParam());
}

TEST_P(CharStreamTestsUint32, SingleData) {
	charStreamTest(GetParam());
}

TEST_P(CharStreamTestsChar, SingleData) {
	charStreamTest(GetParam());
}

TEST_P(CharStreamTestsStringView, SingleData) {
	charStreamTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
	X, CharStreamTestsInt32,
	::testing::Values(
		-2147483648, // min(int32_t)
		-12345,
		-9,
		0,
		9,
		12345,
		2147483647)); // max(int32_t)

INSTANTIATE_TEST_SUITE_P(
	X, CharStreamTestsUint32,
	::testing::Values(
		0u, // min(uint32_t)
		1u,
		4294967295u)); // max(int32_t)

INSTANTIATE_TEST_SUITE_P(
	X, CharStreamTestsChar,
	::testing::Values(
		'a'));

INSTANTIATE_TEST_SUITE_P(
	X, CharStreamTestsStringView,
	::testing::Values("", "one", "abracadabra"));

TEST_F(CharStreamTestsMultipleData, NoOverflow) {
	char buf[128] = {}; // The buffer is big enough to not worry about overflow.
	io::CharStream objUnderTest(buf, sizeof(buf));

	objUnderTest << 1234 << ' ' << 9876u << "string_view constant"sv;
	auto objUnderTestView = objUnderTest.view();
	ASSERT_TRUE(objUnderTest.good());
	ASSERT_FALSE(objUnderTest.eof());

	std::stringstream ss;
	ss << 1234 << ' ' << 9876u << "string_view constant"sv;
	auto ssView = ss.view();

	ASSERT_EQ(ssView.size(), objUnderTestView.size()) << "Length: expected " << ssView.size() << ", got " << objUnderTestView.size() << ".";
	ASSERT_EQ(ssView.compare(objUnderTestView), 0) << "Char array: expected `" << ssView << "`, got `" << objUnderTestView << "`.";
}

template<typename T>
void charStreamTestOverflow(T &param) {
	std::vector<char> buf(param.bufLen);
	io::CharStream objUnderTest(buf.data(), param.bufLen);

	for(auto value : param.values) {
		ASSERT_TRUE(objUnderTest.good()) << "Expected good before pushing " << value;
		ASSERT_FALSE(objUnderTest.eof()) << "Expected !eof before pushing " << value;
		objUnderTest << value;
	}
	if(param.lastValueOverflows) {
		ASSERT_FALSE(objUnderTest.good()) << "Expected !good after pushing " << param.values[param.values.size() - 1];
		ASSERT_TRUE(objUnderTest.eof()) << "Expected eof after pushing " << param.values[param.values.size() - 1];
	} else {
		ASSERT_TRUE(objUnderTest.good()) << "Expected good after pushing " << param.values[param.values.size() - 1];
		;
		ASSERT_FALSE(objUnderTest.eof()) << "Expected !eof after pushing " << param.values[param.values.size() - 1];
		;
	}
}

TEST_P(CharStreamTestsInt32Overflow, Y) {
	charStreamTestOverflow(GetParam());
}

TEST_P(CharStreamTestsUint32Overflow, Y) {
	charStreamTestOverflow(GetParam());
}

TEST_P(CharStreamTestsCharOverflow, Y) {
	charStreamTestOverflow(GetParam());
}

TEST_P(CharStreamTestsStringViewOverflow, Y) {
	charStreamTestOverflow(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
	X, CharStreamTestsInt32Overflow,
	::testing::Values(
		OverflowTestParam<int32_t>{2, {0, 0}, false},
		OverflowTestParam<int32_t>{2, {0, 0, 0}, true},
		OverflowTestParam<int32_t>{8, {1234, 6789}, false},
		OverflowTestParam<int32_t>{8, {12345, 67890}, true},
		OverflowTestParam<int32_t>{4, {-1234}, true}));

INSTANTIATE_TEST_SUITE_P(
	X, CharStreamTestsUint32Overflow,
	::testing::Values(
		OverflowTestParam<uint32_t>{10, {123456u, 6789u}, false},
		OverflowTestParam<uint32_t>{10, {123456u, 67890u}, true},
		OverflowTestParam<uint32_t>{2, {0, 0}, false},
		OverflowTestParam<uint32_t>{3, {0, 0, 0, 0}, true}));

INSTANTIATE_TEST_SUITE_P(
	X, CharStreamTestsCharOverflow,
	::testing::Values(
		OverflowTestParam<char>{2, {'a', 'b'}, false},
		OverflowTestParam<char>{2, {'a', 'b', 'c'}, true}));

INSTANTIATE_TEST_SUITE_P(
	X, CharStreamTestsStringViewOverflow,
	::testing::Values(
		OverflowTestParam<std::string_view>{6, {"one"sv, "two"sv}, false},
		OverflowTestParam<std::string_view>{10, {"one"sv, "two"sv, "three"sv}, true}));
