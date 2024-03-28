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

const uint32_t idleSTackSizeBytes = 512;
constexpr uint32_t idleSTackSize = idleSTackSizeBytes / sizeof(StackType_t);
StaticTask_t idleTCB;
StackType_t idleStack[idleSTackSize];

uint64_t task1DurSNs = 0;
uint64_t task1DurHNs = 0;
uint64_t task1DurSUs = 0;
uint64_t task1DurHUs = 0;


void task1Func(void *);

extern "C" void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
	StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
	*ppxIdleTaskTCBBuffer = &idleTCB;
	*ppxIdleTaskStackBuffer = idleStack;
	*pulIdleTaskStackSize = idleSTackSize;
}

/*
Idle hook is used for not important tasks:
* Flashing the blue led when a byte was received by console.
*/
extern "C" void vApplicationIdleHook() {
	console::processLeds([](bool enable) { assertFuncLED4Blue(enable); });
}

void task1Func(void *) {
	while(true) {
		using std::chrono::time_point, std::chrono::steady_clock, std::chrono::duration, std::chrono::nanoseconds, std::chrono::microseconds, std::chrono::high_resolution_clock;
		time_point<steady_clock> tpS0 = steady_clock::now();
		time_point<high_resolution_clock> tpH0 = high_resolution_clock::now();

		if(tick::sysTickCnt & (1 << 6)) {
			assertFuncLED3Green(true);
		} else {
			assertFuncLED3Green(false);
			// usart::func();
		}
		taskYIELD();

		time_point<steady_clock> tpS1 = steady_clock::now();
		time_point<high_resolution_clock> tpH1 = high_resolution_clock::now();
		duration durS = tpS1 - tpS0;
		duration durH = tpH1 - tpH0;
		nanoseconds durSNs = duration_cast<nanoseconds>(durS);
		nanoseconds durHNs = duration_cast<nanoseconds>(durH);
		microseconds durSUs = duration_cast<microseconds>(durS);
		microseconds durHUs = duration_cast<microseconds>(durH);
		task1DurSNs = durSNs.count();
		task1DurHNs = durHNs.count();
		task1DurSUs = durSUs.count();
		task1DurHUs = durHUs.count();
	}
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
