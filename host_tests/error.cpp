#include "if/error.h"
#include <stdexcept>

void error::fatal(bool cond) {
	if(not cond) {
		throw std::runtime_error("Runtime error.");
	}
}
