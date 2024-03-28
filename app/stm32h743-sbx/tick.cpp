#include "../../if/mcu/tick.h"

const uint32_t tick::systemTimerReloadValue = (64000000 / 1000);

uint32_t tick::sysTickCnt = 0;

// extern "C" void xPortSysTickHandler(void);  // defined in freertos/port.c

// void tick::sysTickISR() {
//   tick::sysTickCnt++;
//   xPortSysTickHandler();
// }
