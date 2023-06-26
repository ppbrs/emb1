#pragma once

#include <cstdint>
namespace debug {

void swvInit(uint32_t sysFreq);
void swvSendChar(int8_t ch);

}