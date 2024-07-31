
#include "3party/googletest/googletest/include/gtest/gtest.h"
#include "splitter.h"
#include <string_view>
#include <vector>

struct TestData {
	std::string_view cmd;
	std::vector<std::string_view> splitted;
};

class ProtocolSplitterTests : public ::testing::TestWithParam<TestData> {};

INSTANTIATE_TEST_SUITE_P(
	X, ProtocolSplitterTests,
	::testing::Values(
		TestData{" abc def  ghi   jkl ", {"abc", "def", "ghi", "jkl"}},
		TestData{"", {}}));

TEST_P(ProtocolSplitterTests, Basic) {
	const TestData testData = GetParam();

	std::vector<std::string_view> splitted;
	for(auto i : protocol::Splitter(testData.cmd)) {
		splitted.push_back(i);
	}
	ASSERT_EQ(splitted, testData.splitted);
}
