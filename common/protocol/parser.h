#pragma once

#include "common/utility.h"
#include "option.h"
#include "parse-result.h"
#include "prog.h"
#include "splitter.h"
#include <iostream>
#include <optional>
#include <string_view>
#include <variant>

namespace protocol {

class ProgUnknown;
/*
PV is an std::optional<std::variant<>>.

I = 0 is always for an unknown program (ProgUnknown), so iteration starts with I = 1.
*/
template<class OptProgVar, std::size_t I = 1>
typename OptProgVar::value_type getOptProgVar(const std::string_view &progToken) {
	using ProgVar = typename OptProgVar::value_type;
	static_assert(std::variant_size_v<ProgVar> > 1);
	static_assert(0 == get_variant_type_index<ProgUnknown, ProgVar>::value);

	// std::cout << "getOptProgVar: " << progToken << std::endl;
	if constexpr(I < std::variant_size_v<ProgVar>) {
		auto progTokenI = std::variant_alternative_t<I, ProgVar>::progToken;
		if(progTokenI == progToken) {
			// std::cout << "getOptProgVar: done " << I << std::endl;
			return std::variant_alternative_t<I, ProgVar>();
		}
		// std::cout << "getOptProgVar: next" << std::endl;
		return getOptProgVar<OptProgVar, I + 1>(progToken);
	}
	// std::cout << "getOptProgVar: done 0" << std::endl;
	return std::variant_alternative_t<0, ProgVar>();
}

/*
Try to parse the command line.
Fill the provided optional variant with data.
*/
template<class OptProgVar>
ParseResult parseCmd(const std::string_view &cmd, OptProgVar &optProgVar) {
	using ProgVar = typename OptProgVar::value_type;
	static_assert(std::variant_size_v<ProgVar> > 1);
	static_assert(0 == get_variant_type_index<ProgUnknown, ProgVar>::value);

	optProgVar = std::nullopt;
	for(auto token : Splitter(cmd)) {
		if(not optProgVar.has_value()) {
			optProgVar = getOptProgVar<OptProgVar>(token);
			if(optProgVar.value().index() == 0) {
				break;
			}
		} else {
			std::visit([&token](auto &arg) { arg.collect(token); }, optProgVar.value());
		}
	}
	if(optProgVar != std::nullopt) {
		ParseResult parseResult = std::visit([](auto &arg) -> ParseResult { return arg.parse(); }, optProgVar.value());
		return parseResult;
	} else {
		return ParseResult::EMPTY_COMMAND;
	}
}

}
