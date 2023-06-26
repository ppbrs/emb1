
#include "../../if/mcu/nvic.h"

// extern "C" void vPortSVCHandler(void);  // defined in freertos/port.c
// extern "C" void xPortPendSVHandler(void);  // defined in freertos/port.c

void nvic::svcISR() {
  // vPortSVCHandler(); // Actually, it's an empty function and not used in FreeRTOS.
}

// [[gnu::naked]] void nvic::pendsvISR() {
//   xPortPendSVHandler();
// }
