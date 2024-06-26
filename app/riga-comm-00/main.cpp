// This source file belongs to riga-comm-00 project.
#include "./freertos/freertos.h"
#include "./io.h"
#include "arch/arm/armv6_m/stm32f0/usart.h"
#include "common/console/console.h"
#include "if/mcu/mcu-init.h"
#include "if/mcu/systick.h"
#include "if/mcu/tick.h"
#include <chrono>

namespace {
StaticTask_t task1TCB;
constexpr uint32_t task1StackSizeBytes = 512;
constexpr uint32_t task1StackSize = task1StackSizeBytes / sizeof(StackType_t);
StackType_t task1Stack[task1StackSize];

// the memory for use by the RTOS Idle task
const uint32_t idleStackSizeBytes = 512;
constexpr uint32_t idleStackSize = idleStackSizeBytes / sizeof(StackType_t);
StaticTask_t idleTCB;
StackType_t idleStack[idleStackSize];

// the memory for use by the RTOS Daemon/Timer Service task
const uint32_t timersStackSizeBytes = 512;
constexpr uint32_t timersStackSize = timersStackSizeBytes / sizeof(StackType_t);
StaticTask_t timersTCB;
StackType_t timersStack[timersStackSize];

constinit StaticTimer_t timer1Buffer = {};

void task1Func(void *);
void timer1Callback(TimerHandle_t);

extern "C" void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
	StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
	*ppxIdleTaskTCBBuffer = &idleTCB;
	*ppxIdleTaskStackBuffer = idleStack;
	*pulIdleTaskStackSize = idleStackSize;
}

extern "C" void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
	StackType_t **ppxTimerTaskStackBuffer,
	uint32_t *pulTimerTaskStackSize) {
	*ppxTimerTaskTCBBuffer = &timersTCB;
	*ppxTimerTaskStackBuffer = timersStack;
	*pulTimerTaskStackSize = timersStackSize;
}

/*
Idle hook is used for not important tasks:
* Flashing the blue led when a byte was received by console.
*/
extern "C" void vApplicationIdleHook() {
	console::processLeds([](bool enable) { assertFuncLED4Blue(enable); });
}

void task1Func(void *) {
	xTimerCreateStatic(
		nullptr, // pcTimerName
		1000, // xTimerPeriod,
		true, // uxAutoReload,
		nullptr, // pvTimerID,
		timer1Callback, // pxCallbackFunction
		&timer1Buffer); // pxTimerBuffer

	while(true) {
		if(tick::sysTickCnt & (1 << 6)) {
			assertFuncLED3Green(true);
		} else {
			assertFuncLED3Green(false);
		}
		taskYIELD();
	}
}

void timer1Callback(TimerHandle_t) {
}

}


int main() {
	mcuInit::init();

	xTaskCreateStatic(task1Func,
		nullptr,
		task1StackSize,
		(void *)0,
		tskIDLE_PRIORITY,
		(uint32_t *)task1Stack,
		&task1TCB);

	vTaskStartScheduler();

	__asm__ volatile("bkpt #0\n"); // In case we get here by mistake:
	while(true) {
		__asm("nop");
	}
}
