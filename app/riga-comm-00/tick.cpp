// This source file belongs to riga-comm-00 project.
#include "../../if/mcu/tick.h"
#include "freertos/freertos.h"

uint32_t tick::sysTickCnt = 0;

const uint32_t tick::sysFreq = 48'000'000;
const uint32_t tick::apbFreq = sysFreq;
const uint32_t tick::ahbFreq = sysFreq;
