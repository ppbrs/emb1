#pragma once
#include "if/error.h"
#include <string_view>

namespace protocol {
class Splitter {
	private:
	const std::string_view sv;

	size_t first;
	size_t second;
	std::string_view now;

	const std::string_view delim = " ";

	public:
	Splitter(const std::string_view sv) :
			sv(sv) {
		if(sv == "") {
			first = std::string_view::npos;
		} else {
			first = 0;
			second = sv.find_first_of(delim, first); // returns std::string_view::npos if ...
			now = sv.substr(first, second - first);
			if(now.empty()) {
				++*this;
			}
		}
	}
	Splitter(const Splitter &) = default;
	~Splitter() = default;

	const Splitter &begin() {
		return *this;
	}

	const Splitter &end() {
		this->first = std::string_view::npos;
		return *this;
	}

	bool operator!=(const Splitter &other) const {
		bool result = first != other.first;
		return result;
	}

	const std::string_view operator*() const {
		return now;
	}

	void operator++() {
		do {
			if(first == std::string_view::npos) {
				error::fatal(false);
			}
			if(second != std::string_view::npos) {
				first = second + 1;
				second = sv.find_first_of(delim, first);
				now = sv.substr(first, second - first);
			} else {
				first = std::string_view::npos;
			}
		} while(now.empty() and first != std::string_view::npos);
	}
};
}