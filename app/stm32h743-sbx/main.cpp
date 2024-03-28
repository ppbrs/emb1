
#include "./freertos/freertos.h"
#include "./io.h"
#include "./tick.h"
#include "app-chrono/app-chrono.h"
#include "app-containers/app-containers.h"
#include "common/linker.h"
#include "if/mcu/debug.h"
#include "if/mcu/mcu-init.h"
#include "if/mcu/systick.h"
#include "if/mcu/tick.h"
#include <chrono>
#include <cstdint>

namespace {
SECTION_DATA_REGULAR StaticTask_t xTask0Buffer;
StackType_t xStack0Buffer[configMINIMAL_STACK_SIZE] SECTION_BSS_FAST;

// SECTION_DATA_FAST uint64_t dummy_data_0[4] = {12345678ULL, 1, 1, 1};
// SECTION_DATA_REGULAR1 uint64_t dummy_data_1[4] = {12345678ULL, 1, 1, 1};
// SECTION_DATA_REGULAR2 uint64_t dummy_data_2[4] = {12345678ULL, 1, 1, 1};
// SECTION_DATA_REGULAR3 uint64_t dummy_data_3[4] = {12345678ULL, 1, 1, 1};
// SECTION_BSS_FAST uint64_t dummy_bss_0;
// SECTION_BSS_REGULAR1 uint64_t dummy_bss_1;
// SECTION_BSS_REGULAR2 uint64_t dummy_bss_2;
// SECTION_BSS_REGULAR3 uint64_t dummy_bss_3;
// const uint64_t dummy_rodata[4] = {99ULL, 98ULL, 97ULL, 96ULL};


void dummy_func() {
	__asm("nop");
	__asm("nop");
}


void task_func_0(void *pvParameters) {
	(void)pvParameters;
	while(true) {
		// dummy_func();
		if(tick::sysTickCnt & (1 << 8)) {
			dummy_func();
			assertFuncLED3(true);
			__asm("nop");
		} else {
			dummy_func();
			assertFuncLED3(false);
			__asm("nop");
		}
	}
}


}

int main() {
	mcuInit::init();
	systick::init();
	debug::swvInit(tick::sysFreq);

	xTaskCreateStatic(task_func_0,
		nullptr,
		configMINIMAL_STACK_SIZE / 2,
		(void *)0,
		tskIDLE_PRIORITY,
		(uint32_t *)&xStack0Buffer,
		&xTask0Buffer);

	app_chrono::start();
	app_containers::start();

	vTaskStartScheduler();

	// In case we get here by mistake:
	while(true) {
		__asm("nop");
	}
}
