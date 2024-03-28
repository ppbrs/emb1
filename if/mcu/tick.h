#pragma once

#include <cstdint>

namespace tick {
/*
System time = systick
*/
extern const uint32_t systemTimerReloadValue;

void sysTickISR();


extern uint32_t sysTickCnt;

extern const uint32_t sysFreq;
extern const uint32_t apbFreq;
extern const uint32_t ahbFreq;

}
