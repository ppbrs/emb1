

#include "./process.h"
#include "./protocol.h"
#include "gtest/gtest.h"

#include <string_view>
#include <array>
#include <vector>

namespace protocol{
namespace process{
class ProtocolProcessTests : public ::testing::Test {
};

TEST_F(ProtocolProcessTests, split) {

	struct Input {
		const std::string_view strv;
		std::vector<std::string_view> words;
		protocol::Error error;
		Input(std::string_view strv, std::vector<std::string_view> words, protocol::Error error) :
			strv(strv), words(words), error(error) {}
	};

	const std::array inputs {
		Input(std::string_view {"ab cd ef gh ij kl mn op"},
			std::vector<std::string_view> {"ab", "cd", "ef", "gh", "ij", "kl", "mn", "op"},
			protocol::Error::OK),
		Input(std::string_view {"ab cd ef gh ij kl mn op qr"},
			std::vector<std::string_view> {},
			protocol::Error::TOO_MANY_WORDS),
		Input(std::string_view {""},
			std::vector<std::string_view> {},
			protocol::Error::OK),
	};

	for(auto &input: inputs) {
		std::vector<std::string_view> words;
		words.reserve(protocol::MAX_WORDS_NUM);
		auto error = split(input.strv, words);
		ASSERT_EQ(input.words.size(), words.size());
		ASSERT_EQ(input.error, error);
	}

//https://www.cppstories.com/2018/07/string-view-perf/
}

TEST_F(ProtocolProcessTests, parse) {

	struct TestData {
		std::vector<std::string_view> words;
		protocol::Error error;
		CommandVariant command;
	};

	const std::array testDataArray {
		TestData {
			std::vector<std::string_view> {},
			protocol::Error::OK,
			CommandEmpty {}
		},
		TestData {
			std::vector<std::string_view> {"qwerty"},
			protocol::Error::UNKNOWN_COMMAND,
			CommandEmpty {}
		},
		TestData {
			std::vector<std::string_view> {"read"},
			protocol::Error::OK,
			CommandRead {}
		},
	};

	for(auto &testData: testDataArray) {
		CommandVariant command;
		auto error = parse(testData.words, command);
		ASSERT_EQ(testData.error, error);
		ASSERT_EQ(testData.command.index(), command.index());
	}
}
}
}
