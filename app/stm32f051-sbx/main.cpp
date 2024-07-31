#include "./freertos/freertos.h"
#include "./io.h"
#include "if/mcu/mcu-init.h"
#include "if/mcu/systick.h"
#include "if/mcu/tick.h"
#include <chrono>

/*
https://blog.aureliocolosimo.it/posts/stm32-bare-metal-made-easy/
https://catch22eu.github.io/website/baremetal/stm32f0xxgnu/
https://github.com/colosimo/stm32f0-baremetal/blob/master/init.c
https://github.com/hwengineer/STM32-startup/blob/master/STM32F0/stm32f051x8.s
*/

namespace {
uint32_t idleCnt = 0;
StaticTask_t task1TCB;
// StaticTask_t task2TCB;
constexpr uint32_t task1StackSizeBytes = 512;
// constexpr uint32_t task2StackSizeBytes = 128;
constexpr uint32_t task1StackSize = task1StackSizeBytes / sizeof(StackType_t);
// constexpr uint32_t task2StackSize = task2StackSizeBytes / sizeof(StackType_t);
StackType_t task1Stack[task1StackSize];
// StackType_t task2StackBuf[task1StackSize];

const uint32_t idleSTackSizeBytes = 512;
constexpr uint32_t idleSTackSize = idleSTackSizeBytes / sizeof(StackType_t);
StaticTask_t idleTCB;
StackType_t idleStack[idleSTackSize];

uint64_t task1DurSNs = 0;
uint64_t task1DurHNs = 0;
uint64_t task1DurSUs = 0;
uint64_t task1DurHUs = 0;


void task1Func(void *);

void dummyFunc0() {
	__asm__("nop");
}
void dummyFunc1() {
	__asm("nop");
	dummyFunc0();
}
void dummyFunc2() {
	__asm("nop");
	dummyFunc1();
}


extern "C" void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
	StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
	*ppxIdleTaskTCBBuffer = &idleTCB;
	*ppxIdleTaskStackBuffer = idleStack;
	*pulIdleTaskStackSize = idleSTackSize;
}


extern "C" void vApplicationIdleHook() {
	// __asm__ volatile("bkpt #0\n");
	idleCnt++;
	if(tick::sysTickCnt & (1 << 8)) {
		assertFuncLED4Blue(true);
	} else {
		assertFuncLED4Blue(false);
	}
	dummyFunc2();
}

void task1Func(void *) {
	// __asm__ volatile("bkpt #0\n");
	while(true) {
		using std::chrono::time_point, std::chrono::steady_clock, std::chrono::duration, std::chrono::nanoseconds, std::chrono::microseconds, std::chrono::high_resolution_clock;
		time_point<steady_clock> tpS0 = steady_clock::now();
		time_point<high_resolution_clock> tpH0 = high_resolution_clock::now();

		if(tick::sysTickCnt & (1 << 8)) {
			assertFuncLED3Green(true);
			// __asm("nop");
		} else {
			assertFuncLED3Green(false);
			// __asm("nop");
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
	// systick::init();

	// (void)task1Func; (void)task1Stack; (void)task1TCB;
	xTaskCreateStatic(task1Func,
		nullptr,
		task1StackSize,
		(void *)0,
		tskIDLE_PRIORITY,
		(uint32_t *)task1Stack,
		&task1TCB);

	// __asm__ volatile("bkpt #0\n");
	vTaskStartScheduler();

	__asm__ volatile("bkpt #0\n"); // In case we get here by mistake:
	while(true) {
		__asm("nop");
	}
}
