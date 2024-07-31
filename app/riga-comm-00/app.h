#pragma once
#include <cstdint>
#include <optional>

namespace app {
void init(void (*)(void));
void initFromTask();
void consumeByteFromISR(uint8_t);
void processLeds(void (*ledAssertFunc)(bool));
void pollFrom1HzTimer();
void pollFromTask();
std::optional<uint8_t> getNextTxByte();
}
