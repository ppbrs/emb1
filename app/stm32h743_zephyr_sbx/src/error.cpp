
#include "if/error.h"

void error::fatal(bool cond) {
	if(not cond) {
		asm("bkpt");
	}
}

namespace std {
	// Temporary solution
	// https://forum.arduino.cc/t/arduino-due-warning-std-__throw_length_error-char-const/308515
	void __throw_length_error(char const*) {
		while(1) {
			asm("nop");
		}
	}
}
