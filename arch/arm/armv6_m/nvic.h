#pragma once

namespace armv6_m {
namespace nvic {
enum class ExceptionNumber : int8_t {
  NonMaskableInt         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  HardFault              = -13,    /*!< 3 Cortex-M Hard Fault Interrupt                                   */
  SVCall                 = -5,     /*!< 11 Cortex-M SV Call Interrupt                                     */
  DebugMonitor           = -4,     /*!< 12 Cortex-M Debug Monitor Interrupt                               */
  PendSV                 = -2,     /*!< 14 Cortex-M Pend SV Interrupt                                     */
  SysTick                = -1,     /*!< 15 Cortex-M System Tick Interrupt                                 */
};
}
}
