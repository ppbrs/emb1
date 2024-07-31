#pragma once

#include "pio.h"
#include <optional>
#include <ranges>


namespace usart {

/* Callback to the driver when application needs to send sth. */
using NotifyDataReady = void (*)();

using InitFunc = void (*)(NotifyDataReady);

/* Function called by the driver when a byte is received. */
using ConsumeByteFromISR = void (*)(uint8_t);

using GetNextByte = std::optional<uint8_t> (*)();


template<typename USART, typename GPIO>
struct UsartDef {
	USART &regs;
	const pio::PioDef<GPIO> &txPioDef;
	const pio::PioDef<GPIO> &rxPioDef;

	/* A function that initializes USART client.
	This function is called before RTOS.
	*/
	InitFunc initFunc;

	/* A function that consumes data received by USART.
	This function is called from ISR. */
	ConsumeByteFromISR consumeByteFromISR;

	/* A function that requests data for transmission by USART. */
	GetNextByte getNextByte;
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
