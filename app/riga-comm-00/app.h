#pragma once
#include <cstdint>
#include <optional>

namespace app {
void init(void (&)(void));
void consumeByteFromISR(uint8_t);
void processLeds(void (*ledAssertFunc)(bool));
void pollFrom1HzTimer();
std::optional<uint8_t> getNextTxByte();
}
