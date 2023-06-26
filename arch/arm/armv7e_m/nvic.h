#pragma once

namespace armv7e_m {
namespace nvic {
enum class ExceptionNumber {
	NonMaskableInt_IRQn = -14, /*!< 2 Non Maskable Interrupt                                          */
	HardFault_IRQn = -13, /*!< 3 Cortex-M Hard Fault Interrupt                                   */
	MemoryManagement_IRQn = -12, /*!< 4 Cortex-M Memory Management Interrupt                            */
	BusFault_IRQn = -11, /*!< 5 Cortex-M Bus Fault Interrupt                                    */
	UsageFault_IRQn = -10, /*!< 6 Cortex-M Usage Fault Interrupt                                  */
	SVCall_IRQn = -5, /*!< 11 Cortex-M SV Call Interrupt                                     */
	DebugMonitor_IRQn = -4, /*!< 12 Cortex-M Debug Monitor Interrupt                               */
	PendSV_IRQn = -2, /*!< 14 Cortex-M Pend SV Interrupt                                     */
	SysTick_IRQn = -1, /*!< 15 Cortex-M System Tick Interrupt                                 */
};
}
}
