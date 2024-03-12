#include "app-chrono.h"
#include "./../freertos/freertos.h"
#include "./../io.h"
#include "common/linker.h"
#include "if/mcu/debug.h"
#include <chrono>
#include <cstdint>

namespace {
SECTION_DATA_REGULAR StaticTask_t xTaskBuffer;
StackType_t xStackBuffer[configMINIMAL_STACK_SIZE] SECTION_BSS_FAST;

uint64_t task1DurSNs = 0;
uint64_t task1DurHNs = 0;
uint64_t task1DurSUs = 0;
uint64_t task1DurHUs = 0;

void dummy_func() {
	__asm("nop");
	__asm("nop");
}

void task_func(void *pvParameters);
}

void app_chrono::start() {
	xTaskCreateStatic(task_func,
		nullptr,
		configMINIMAL_STACK_SIZE,
		(void *)0,
		tskIDLE_PRIORITY,
		(uint32_t *)&xStackBuffer,
		&xTaskBuffer);
}

namespace {
void task_func(void *pvParameters) {
	(void)pvParameters;
	bool b = false;
	while(true) {
		using std::chrono::time_point, std::chrono::steady_clock, std::chrono::duration, std::chrono::nanoseconds, std::chrono::microseconds, std::chrono::high_resolution_clock;
		time_point<steady_clock> tpS0 = steady_clock::now();
		time_point<high_resolution_clock> tpH0 = high_resolution_clock::now();

		if(b) {
			dummy_func();
			// stm32::reg::GPIO::GPIOB.BSRR.bits.BS14 = 1;
			// dioLED2.setLogicLow();
			// dioLED3.setLogicLow();
			assertFuncLED2(true);
			b = false;
			debug::swvSendChar('a');
		} else {
			dummy_func();
			// stm32::reg::GPIO::GPIOB.BSRR.bits.BR14 = 1;
			// dioLED2.setLogicHigh();
			// dioLED3.setLogicHigh();
			assertFuncLED2(false);
			b = true;
			debug::swvSendChar('A');
		}

		// dummy_data_0[0]++;
		// dummy_data_1[1]++;
		// dummy_data_2[1]++;
		// dummy_data_3[1]++;
		// dummy_bss_0 += dummy_rodata[0] + reinterpret_cast<uint64_t>(&dummy_rodata[0]);
		// dummy_bss_1 += dummy_rodata[1];
		// dummy_bss_2 += dummy_rodata[2];
		// dummy_bss_3 += dummy_rodata[3];

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

		vTaskDelay(1000);
	}
}
}