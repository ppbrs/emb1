#include "option.h"
#include <charconv>

bool protocol::Option::paramParse() {
	switch(type) {
		case Type::UINT32: {
			if(not optParamStr.has_value()) {
				return false;
			}
			std::from_chars_result res;
			std::string_view paramStr = optParamStr.value();
			if(paramStr.starts_with("0x")) {
				res = std::from_chars(paramStr.substr(2).data(), paramStr.data() + paramStr.size(), paramUint32, 16);
				if(res.ec == std::errc{}) {
					return true;
				}
			} else if(paramStr.ends_with("h")) {
				res = std::from_chars(paramStr.data(), paramStr.data() + paramStr.size() - 1, paramUint32, 16);
				if(res.ec == std::errc{}) {
					return true;
				}
			} else {
				res = std::from_chars(paramStr.data(), paramStr.data() + paramStr.size(), paramUint32, 10);
				if(res.ec == std::errc{}) {
					return true;
				}
			}
			break;
		}
		case Type::BOOL: {
			if(not optParamStr.has_value()) {
				return false;
			}
			if(nameReceived and not paramReceived) {
				// If the parameter is omitted with a boolean option, it is considered TRUE.
				paramUint32 = 1u;
				return true;
			}
			std::string_view paramStr = optParamStr.value();
			if((paramStr == "1") or (paramStr == "true") or (paramStr == "") or (paramStr == "y") or (paramStr == "Y")) {
				paramUint32 = 1;
				return true;
			} else if((paramStr == "0") or (paramStr == "false") or (paramStr == "n") or (paramStr == "N")) {
				paramUint32 = 0;
				return true;
			}
			break;
		}
		case Type::STRING:
			return optParamStr.has_value();
		default:
			break;
	}


	return false;
}
