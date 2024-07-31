#pragma once

#include <cstdint>
// #include <functional>
/*
Only one console per application.
*/

namespace console {

extern unsigned rxCnt;

void init();
void byteReceived(uint8_t b);
void processLeds(void (*ledAssertFunc)(bool));


}
