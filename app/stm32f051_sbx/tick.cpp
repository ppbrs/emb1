
#include "../../if/mcu/tick.h"
#include "freertos/freertos.h"

// const uint32_t tick::systemTimerReloadValue = (48000000 / 1000) - 1;
// TODO: 
// static_assert(tick::systemTimerReloadValue > 0);
// static_assert(tick::systemTimerReloadValue <= 0xFFFFFF);


uint32_t tick::sysTickCnt = 0;



// extern "C" void xPortSysTickHandler(void);  // defined in freertos/port.c

// void tick::sysTickISR() {
//   tick::sysTickCnt++;
//   xPortSysTickHandler();
// }
