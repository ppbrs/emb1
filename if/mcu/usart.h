#pragma once

#include "pio.h"
#include <ranges>


namespace usart {

template<typename USART, typename GPIO>
struct UsartDef {
	USART &regs;
	const pio::PioDef<GPIO> &txPioDef;
	const pio::PioDef<GPIO> &rxPioDef;
	void (*initFunc)();
	void (*isrRxFunc)(uint8_t);
};


// This function is defined separately for each architecture.
template<typename USART, typename GPIO>
void configure(const UsartDef<USART, GPIO> &usartDef);

template<std::ranges::range T>
void configure(const T &usartDefs) {
	for(auto &usartDef : usartDefs) {
		configure(usartDef);
	}
}


}
