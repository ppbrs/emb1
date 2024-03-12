
#include "arch/arm/armv7e_m//mmreg/itm.h"
#include "arch/arm/armv7e_m//mmreg/scb.h"
#include "if/mcu/chrono.h"
#include "if/mcu/nvic.h"
#include "if/mcu/tick.h"
#include <array>
#include <cstdint>

#if __STDC_HOSTED__ > 0
#error __STDC_HOSTED__ is not 0
#endif


/*================== function prototypes ==================*/
extern int main();
extern "C" void __libc_init_array();

void Default_Handler() __attribute__((weak));
extern "C" void Reset_Handler() __attribute__((weak));
void NMI_Handler() __attribute__((weak));
void HardFault_Handler() __attribute__((weak));
void MemManage_Handler() __attribute__((weak));
void BusFault_Handler() __attribute__((weak));
void UsageFault_Handler() __attribute__((weak));
// void SVC_Handler()                  __attribute__((weak));
void DebugMon_Handler() __attribute__((weak));
// void PendSV_Handler()               __attribute__((weak));
// void SysTick_Handler()              __attribute__((weak));

void WWDG_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void PVD_AVD_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TAMP_STAMP_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void RTC_WKUP_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void FLASH_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void RCC_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void EXTI0_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void EXTI1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void EXTI2_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void EXTI3_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void EXTI4_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA1_Stream0_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA1_Stream1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA1_Stream2_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA1_Stream3_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA1_Stream4_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA1_Stream5_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA1_Stream6_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void ADC_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void FDCAN1_IT0_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void FDCAN2_IT0_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void FDCAN1_IT1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void FDCAN2_IT1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void EXTI9_5_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM1_BRK_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM1_UP_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM1_TRG_COM_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM1_CC_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM2_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM3_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM4_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void I2C1_EV_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void I2C1_ER_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void I2C2_EV_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void I2C2_ER_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void SPI1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void SPI2_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void USART1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void USART2_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void USART3_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void EXTI15_10_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void RTC_Alarm_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM8_BRK_TIM12_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM8_UP_TIM13_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM8_TRG_COM_TIM14_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM8_CC_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA1_Stream7_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void FMC_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void SDMMC1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM5_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void SPI3_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void UART4_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void UART5_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM6_DAC_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM7_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA2_Stream0_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA2_Stream1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA2_Stream2_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA2_Stream3_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA2_Stream4_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void ETH_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void ETH_WKUP_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void FDCAN_CAL_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA2_Stream5_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA2_Stream6_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA2_Stream7_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void USART6_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void I2C3_EV_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void I2C3_ER_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void OTG_HS_EP1_OUT_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void OTG_HS_EP1_IN_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void OTG_HS_WKUP_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void OTG_HS_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DCMI_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void RNG_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void FPU_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void UART7_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void UART8_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void SPI4_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void SPI5_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void SPI6_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void SAI1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void LTDC_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void LTDC_ER_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMA2D_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void SAI2_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void QUADSPI_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void LPTIM1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void CEC_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void I2C4_EV_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void I2C4_ER_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void SPDIF_RX_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void OTG_FS_EP1_OUT_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void OTG_FS_EP1_IN_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void OTG_FS_WKUP_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void OTG_FS_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMAMUX1_OVR_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void HRTIM1_Master_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void HRTIM1_TIMA_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void HRTIM1_TIMB_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void HRTIM1_TIMC_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void HRTIM1_TIMD_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void HRTIM1_TIME_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void HRTIM1_FLT_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DFSDM1_FLT0_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DFSDM1_FLT1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DFSDM1_FLT2_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DFSDM1_FLT3_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void SAI3_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void SWPMI1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM15_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM16_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void TIM17_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void MDIOS_WKUP_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void MDIOS_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void JPEG_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void MDMA_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void SDMMC2_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void HSEM1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void ADC3_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void DMAMUX2_OVR_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void BDMA_Channel0_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void BDMA_Channel1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void BDMA_Channel2_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void BDMA_Channel3_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void BDMA_Channel4_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void BDMA_Channel5_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void BDMA_Channel6_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void BDMA_Channel7_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void COMP1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void LPTIM2_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void LPTIM3_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void LPTIM4_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void LPTIM5_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void LPUART1_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void CRS_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void SAI4_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));
void WAKEUP_PIN_IRQHandler() __attribute__((weak /*, alias("Default_Handler")*/));


/*=================== Global variables ====================*/
/* Highest address of the user mode stack */
extern const volatile uint32_t _main_stack_end;
/* start address for the initialization values of the .data section.
defined in linker script */
extern uint32_t _data_fast_lma_start;
extern uint32_t _data_regular1_lma_start;
extern uint32_t _data_regular2_lma_start;
extern uint32_t _data_regular3_lma_start;
/* start and end addresses for the .data sections. defined in linker script */
extern uint32_t _data_fast_vma_start, _data_fast_vma_end;
extern uint32_t _data_regular1_vma_start, _data_regular1_vma_end;
extern uint32_t _data_regular2_vma_start, _data_regular2_vma_end;
extern uint32_t _data_regular3_vma_start, _data_regular3_vma_end;


/* start and end addresses for the .bss sections defined in linker script */
extern uint32_t _bss_fast_start, _bss_fast_end;
extern uint32_t _bss_regular1_start, _bss_regular1_end;
extern uint32_t _bss_regular2_start, _bss_regular2_end;
extern uint32_t _bss_regular3_start, _bss_regular3_end;

/* The Interrupt Vector Table

When reset is deasserted, execution restarts from the address provided by the reset entry in the vector table. Execution restarts as privileged execution in Thread mode.

The vector table contains the reset value of the stack pointer,
and the start addresses, also called exception vectors, for all exception handlers.

*/

struct Vectors {
	void *sp;
	std::array<void (*)(), 15> exceptionHandlers;
	std::array<void (*)(), 150> interruptHandlers;
};
static_assert(sizeof(Vectors) == 4 * (1 + 15 + 150));

__attribute__((section(".isr_vector"), used)) /* 'used' attribute is similar to KEEP() */
constexpr Vectors vectors = {
	(void *)&_main_stack_end,
	{
		Reset_Handler, // Exception number = 1
		NMI_Handler, // IRQ number = -14
		HardFault_Handler,
		MemManage_Handler,
		BusFault_Handler,
		UsageFault_Handler,
		0, // reserved
		0,
		0,
		0,
		nvic::svcISR,
		DebugMon_Handler,
		0,
		nvic::pendsvISR,
		tick::sysTickISR, // SysTick_Handler,  // IRQ number = -1
	},
	{
		/* External Interrupts (IRQ0 ... IRQ239) */
		WWDG_IRQHandler, // IRQ0
		PVD_AVD_IRQHandler,
		TAMP_STAMP_IRQHandler,
		RTC_WKUP_IRQHandler,
		FLASH_IRQHandler,
		RCC_IRQHandler,
		EXTI0_IRQHandler,
		EXTI1_IRQHandler,
		EXTI2_IRQHandler,
		EXTI3_IRQHandler,
		EXTI4_IRQHandler,
		DMA1_Stream0_IRQHandler,
		DMA1_Stream1_IRQHandler,
		DMA1_Stream2_IRQHandler,
		DMA1_Stream3_IRQHandler,
		DMA1_Stream4_IRQHandler,
		DMA1_Stream5_IRQHandler,
		DMA1_Stream6_IRQHandler,
		ADC_IRQHandler,
		FDCAN1_IT0_IRQHandler,
		FDCAN2_IT0_IRQHandler,
		FDCAN1_IT1_IRQHandler,
		FDCAN2_IT1_IRQHandler,
		EXTI9_5_IRQHandler,
		TIM1_BRK_IRQHandler,
		TIM1_UP_IRQHandler,
		TIM1_TRG_COM_IRQHandler,
		TIM1_CC_IRQHandler,
		chrono::steady_clock::overflow, /*TIM2_IRQHandler*/ // IRQ28
		chrono::high_resolution_clock::overflow, /*TIM3_IRQHandler*/ // IRQ29
		TIM4_IRQHandler,
		I2C1_EV_IRQHandler,
		I2C1_ER_IRQHandler,
		I2C2_EV_IRQHandler,
		I2C2_ER_IRQHandler,
		SPI1_IRQHandler,
		SPI2_IRQHandler,
		USART1_IRQHandler,
		USART2_IRQHandler,
		USART3_IRQHandler,
		EXTI15_10_IRQHandler,
		RTC_Alarm_IRQHandler,
		0,
		TIM8_BRK_TIM12_IRQHandler,
		TIM8_UP_TIM13_IRQHandler,
		TIM8_TRG_COM_TIM14_IRQHandler,
		TIM8_CC_IRQHandler,
		DMA1_Stream7_IRQHandler,
		FMC_IRQHandler,
		SDMMC1_IRQHandler,
		TIM5_IRQHandler,
		SPI3_IRQHandler,
		UART4_IRQHandler,
		UART5_IRQHandler,
		TIM6_DAC_IRQHandler,
		TIM7_IRQHandler,
		DMA2_Stream0_IRQHandler,
		DMA2_Stream1_IRQHandler,
		DMA2_Stream2_IRQHandler,
		DMA2_Stream3_IRQHandler,
		DMA2_Stream4_IRQHandler,
		ETH_IRQHandler,
		ETH_WKUP_IRQHandler,
		FDCAN_CAL_IRQHandler,
		0,
		0,
		0,
		0,
		DMA2_Stream5_IRQHandler,
		DMA2_Stream6_IRQHandler,
		DMA2_Stream7_IRQHandler,
		USART6_IRQHandler,
		I2C3_EV_IRQHandler,
		I2C3_ER_IRQHandler,
		OTG_HS_EP1_OUT_IRQHandler,
		OTG_HS_EP1_IN_IRQHandler,
		OTG_HS_WKUP_IRQHandler,
		OTG_HS_IRQHandler,
		DCMI_IRQHandler,
		0,
		RNG_IRQHandler,
		FPU_IRQHandler,
		UART7_IRQHandler,
		UART8_IRQHandler,
		SPI4_IRQHandler,
		SPI5_IRQHandler,
		SPI6_IRQHandler,
		SAI1_IRQHandler,
		LTDC_IRQHandler,
		LTDC_ER_IRQHandler,
		DMA2D_IRQHandler,
		SAI2_IRQHandler,
		QUADSPI_IRQHandler,
		LPTIM1_IRQHandler,
		CEC_IRQHandler,
		I2C4_EV_IRQHandler,
		I2C4_ER_IRQHandler,
		SPDIF_RX_IRQHandler,
		OTG_FS_EP1_OUT_IRQHandler,
		OTG_FS_EP1_IN_IRQHandler,
		OTG_FS_WKUP_IRQHandler,
		OTG_FS_IRQHandler,
		DMAMUX1_OVR_IRQHandler,
		HRTIM1_Master_IRQHandler,
		HRTIM1_TIMA_IRQHandler,
		HRTIM1_TIMB_IRQHandler,
		HRTIM1_TIMC_IRQHandler,
		HRTIM1_TIMD_IRQHandler,
		HRTIM1_TIME_IRQHandler,
		HRTIM1_FLT_IRQHandler,
		DFSDM1_FLT0_IRQHandler,
		DFSDM1_FLT1_IRQHandler,
		DFSDM1_FLT2_IRQHandler,
		DFSDM1_FLT3_IRQHandler,
		SAI3_IRQHandler,
		SWPMI1_IRQHandler,
		TIM15_IRQHandler,
		TIM16_IRQHandler,
		TIM17_IRQHandler,
		MDIOS_WKUP_IRQHandler,
		MDIOS_IRQHandler,
		JPEG_IRQHandler,
		MDMA_IRQHandler,
		0,
		SDMMC2_IRQHandler,
		HSEM1_IRQHandler,
		0,
		ADC3_IRQHandler,
		DMAMUX2_OVR_IRQHandler,
		BDMA_Channel0_IRQHandler,
		BDMA_Channel1_IRQHandler,
		BDMA_Channel2_IRQHandler,
		BDMA_Channel3_IRQHandler,
		BDMA_Channel4_IRQHandler,
		BDMA_Channel5_IRQHandler,
		BDMA_Channel6_IRQHandler,
		BDMA_Channel7_IRQHandler,
		COMP1_IRQHandler,
		LPTIM2_IRQHandler,
		LPTIM3_IRQHandler,
		LPTIM4_IRQHandler,
		LPTIM5_IRQHandler,
		LPUART1_IRQHandler,
		0,
		CRS_IRQHandler,
		0,
		SAI4_IRQHandler,
		0,
		0,
		WAKEUP_PIN_IRQHandler // IRQ149
	}};
static_assert(sizeof(vectors) == 4 * (1 + 15 + 150));

/*================= Function definitions ==================*/
void Default_Handler() {
	while(1) {
		__asm("nop");
	}
}

void Reset_Handler() {
	/* The processor starts in privileged mode */

	/* Set stack pointer */
	__asm("ldr sp, =_main_stack_end"); // Is it necessary?

	/* The FPU is disabled from reset. Here we enable it by writing to CPACR. */
	__asm("ldr r0, =0xE000ED88\n" /* TODO: use CPACR address from scb.h */
		  "ldr r1, [r0]\n" // read CPACR
		  "orr r1, r1, #(0xF << 20)\n" // enable CP11 CP11
		  "str r1, [r0]\n" // write back to CPACR
		  "dsb\n"
		  "isb\n");

	/* Enable configurable fault handlers: */
	armv7e_m::mmreg::SCB::SCB.SHCSR.bits.MEMFAULTENA = 1;
	armv7e_m::mmreg::SCB::SCB.SHCSR.bits.BUSFAULTENA = 1;
	armv7e_m::mmreg::SCB::SCB.SHCSR.bits.USGFAULTENA = 1;

	/* Copy the data segment initializers from flash to SRAM */
	{
		uint32_t *src_fast = &_data_fast_lma_start;
		for(uint32_t *dst = &_data_fast_vma_start; dst < &_data_fast_vma_end;) {
			*dst++ = *src_fast++;
		}
		uint32_t *src_regular1 = &_data_regular1_lma_start;
		for(uint32_t *dst = &_data_regular1_vma_start; dst < &_data_regular1_vma_end;) {
			*dst++ = *src_regular1++;
		}
		uint32_t *src_regular2 = &_data_regular2_lma_start;
		for(uint32_t *dst = &_data_regular2_vma_start; dst < &_data_regular2_vma_end;) {
			*dst++ = *src_regular2++;
		}
		uint32_t *src_regular3 = &_data_regular3_lma_start;
		for(uint32_t *dst = &_data_regular3_vma_start; dst < &_data_regular3_vma_end;) {
			*dst++ = *src_regular3++;
		}
	}

	/* Zero fill the bss segment */
	__asm("ldr r0, =_bss_fast_start\n"
		  "ldr r1, =_bss_fast_end\n"
		  "mov r2, #0\n"
		  ".thumb_func\n"
		  "bss_fast_loop:\n"
		  "cmp r0, r1\n"
		  "it lt\n"
		  "strlt r2, [r0], #4\n"
		  "blt bss_fast_loop");
	__asm("ldr r0, =_bss_regular1_start\n"
		  "ldr r1, =_bss_regular1_end\n"
		  "mov r2, #0\n"
		  ".thumb_func\n"
		  "bss_regular1_loop:\n"
		  "cmp r0, r1\n"
		  "it lt\n"
		  "strlt r2, [r0], #4\n"
		  "blt bss_regular1_loop");
	__asm("ldr r0, =_bss_regular2_start\n"
		  "ldr r1, =_bss_regular2_end\n"
		  "mov r2, #0\n"
		  ".thumb_func\n"
		  "bss_regular2_loop:\n"
		  "cmp r0, r1\n"
		  "it lt\n"
		  "strlt r2, [r0], #4\n"
		  "blt bss_regular2_loop");
	__asm("ldr r0, =_bss_regular3_start\n"
		  "ldr r1, =_bss_regular3_end\n"
		  "mov r2, #0\n"
		  ".thumb_func\n"
		  "bss_regular3_loop:\n"
		  "cmp r0, r1\n"
		  "it lt\n"
		  "strlt r2, [r0], #4\n"
		  "blt bss_regular3_loop");

	/* Call static constructors

	https://stackoverflow.com/questions/15265295/understanding-the-libc-init-array
	*/
	__libc_init_array();

	/* Call the application's entry point */
	main();
}


/*

https://stackoverflow.com/questions/13734745/why-do-i-have-an-undefined-reference-to-init-in-libc-init-array

*/
extern "C" void _init(void) { ; }

void NMI_Handler() {
	while(1) {
		__asm("nop");
	}
}

struct FrameBasic {
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r12;
	uint32_t lr;
	uint32_t pc;
	uint32_t xpsr;
};
static_assert(sizeof(FrameBasic) == 8 * 4);

/*
Useful articles:
	https://interrupt.memfault.com/blog/cortex-m-hardfault-debug
	https://www.segger.com/downloads/application-notes/AN00016
	https://www.freertos.org/Debugging-Hard-Faults-On-Cortex-M-Microcontrollers.html
	https://www.iar.com/knowledge/support/technical-notes/debugger/debugging-a-hardfault-on-cortex-m/
	https://www.embeddedrelated.com/showarticle/912.php

When a hard fault exception occurs, the CPU saves the following register on the current stack,
which can be either main stack or process stack:
				<previous> <-- SP points here before exception
	SP + 0x1C	xPSR
	SP + 0x18	PC
	SP + 0x14	LR
	SP + 0x10	R12
	SP + 0x0C	R3
	SP + 0x08	R2
	SP + 0x04	R1
	SP + 0x00	R0 <-- SP points here after exception

When entering an exception handler, the LR register is updated to a special value
called EXC_RETURN with the upper 28 bits all set to 1. This value, when loaded into
the PC at the end of the exception handler execution, will cause the CPU to perform
an exception return sequence.
Bit 2 of the LR register determines the used stack before entering the exception:
	0 = main stack
	1 = process stack

Encoding of The EXC_RETURN Value
EXC_RETURN 5 low-order bits:
				Stack Pointer	Frame Type (extended = uses floating-point state)
												Execution Mode (where to return)
11101 (0x1D)	Process stack	Basic frame		Thread mode
11001 (0x19)	Main stack		Basic frame		Thread mode
10001 (0x11)	Main stack		Basic frame		Handler mode
01101 (0x0D)	Process stack	Extended frame	Thread mode
01001 (0x09)	Main stack		Extended frame	Thread mode
00001 (0x01)	Main stack		Extended frame	Handler mode

GDB:
	p/x $lr&(1<<2)
	p/a *(uint32_t[8] *)$psp

*/
void HardFault_Handler() {
	uint32_t lr, sp;
	__asm__ volatile("mov %0, LR\n"
					 : "=r"(lr));
	if(lr & (1 << 2)) {
		__asm__ volatile("mrs %0, PSP\n"
						 : "=r"(sp)); // process stack was used
	} else {
		__asm__ volatile("mrs %0, MSP\n"
						 : "=r"(sp)); // main stack was used
	}
	armv7e_m::mmreg::SCB::CFSR cfsr;
	cfsr.word = armv7e_m::mmreg::SCB::SCB.CFSR.word;
	(void)cfsr;
	FrameBasic &frameBasic = *(FrameBasic *)sp;
	(void)frameBasic;
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

/*
MemManage: detects memory access violations to regions that are defined in the Memory
Management Unit (MPU); for example, code execution from a memory region with read/write access
only.
*/
void MemManage_Handler() {
	uint32_t lr, sp;
	__asm__ volatile("mov %0, LR\n"
					 : "=r"(lr));
	if(lr & (1 << 2)) {
		__asm__ volatile("mrs %0, PSP\n"
						 : "=r"(sp)); // process stack was used
	} else {
		__asm__ volatile("mrs %0, MSP\n"
						 : "=r"(sp)); // main stack was used
	}
	armv7e_m::mmreg::SCB::CFSR cfsr;
	cfsr.word = armv7e_m::mmreg::SCB::SCB.CFSR.word;
	(void)cfsr;
	FrameBasic &frameBasic = *(FrameBasic *)sp;
	(void)frameBasic;
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

/*
BusFault: detects memory access errors on instruction fetch, data read/write, interrupt vector fetch,
and register stacking (save/restore) on interrupt (entry/exit).

Cache maintenance operations can result in an asynchronous (imprecise) BusFault.

Due to the design in the bus interface, the bus error in Cortex-M7 can be imprecise
if the memory operation is a write to a strongly ordered memory region. In such case,
the stacked PC could be showing a different context (for example, an IRQ handler that was triggered
shortly after the buffered write took place). As a result, on Cortex-M7 the BusFault handler
cannot rely on stacked PC to determine the fault location if the BusFault is asynchronous.

*/
void BusFault_Handler() {
	uint32_t lr, sp;
	__asm__ volatile("mov %0, LR\n"
					 : "=r"(lr));
	if(lr & (1 << 2)) {
		__asm__ volatile("mrs %0, PSP\n"
						 : "=r"(sp)); // process stack was used
	} else {
		__asm__ volatile("mrs %0, MSP\n"
						 : "=r"(sp)); // main stack was used
	}
	armv7e_m::mmreg::SCB::CFSR cfsr;
	cfsr.word = armv7e_m::mmreg::SCB::SCB.CFSR.word;
	(void)cfsr;
	FrameBasic &frameBasic = *(FrameBasic *)sp;
	(void)frameBasic;
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

/*
UsageFault: detects execution of undefined instructions, unaligned memory access for load/store
multiple. When enabled, divide-by-zero and other unaligned memory accesses are detected.
*/
void UsageFault_Handler() {
	uint32_t lr, sp;
	__asm__ volatile("mov %0, LR\n"
					 : "=r"(lr));
	if(lr & (1 << 2)) {
		__asm__ volatile("mrs %0, PSP\n"
						 : "=r"(sp)); // process stack was used
	} else {
		__asm__ volatile("mrs %0, MSP\n"
						 : "=r"(sp)); // main stack was used
	}
	armv7e_m::mmreg::SCB::CFSR cfsr;
	cfsr.word = armv7e_m::mmreg::SCB::SCB.CFSR.word;
	(void)cfsr;
	FrameBasic &frameBasic = *(FrameBasic *)sp;
	(void)frameBasic;
	__asm__ volatile("bkpt #0\n");
	while(1) {
		__asm("nop");
	}
}

// void SVC_Handler() {
//     while(1) {
//         __asm("nop");
//     }
// }

void DebugMon_Handler() {
	while(1) {
		__asm("nop");
	}
}

// void PendSV_Handler() {
//     while(1) {
//         __asm("nop");
//     }
// }

// void SysTick_Handler() {
//     while(1) {
//         __asm("nop");
//     }
// }

#if 0
static void SystemInit(void) {

		/* Enable the floating-point unit. Any configuration of the
		floating-point unit must be done here prior to it being enabled */
		HWREG(0xE000ED88) = ((HWREG(0xE000ED88) & ~0x00F00000) | 0x00F00000);

		/*------- Reset the RCC clock configuration to the default reset state -------*/
		/* Set HSION bit */
		RCC->CR |= 0x00000001;
		/* Reset CFGR register */
		RCC->CFGR = 0x00000000;
		/* Reset HSEON, CSSON , CSION,RC48ON, CSIKERON PLL1ON, PLL2ON and PLL3ON bits */
		RCC->CR &= (uint32_t)0xEAF6ED7F;
		/* Reset D1CFGR register */
		RCC->D1CFGR = 0x00000000;
		/* Reset D2CFGR register */
		RCC->D2CFGR = 0x00000000;
		/* Reset D3CFGR register */
		RCC->D3CFGR = 0x00000000;
		/* Reset PLLCKSELR register */
		RCC->PLLCKSELR = 0x00000000;
		/* Reset PLLCFGR register */
		RCC->PLLCFGR = 0x00000000;
		/* Reset PLL1DIVR register */
		RCC->PLL1DIVR = 0x00000000;
		/* Reset PLL1FRACR register */
		RCC->PLL1FRACR = 0x00000000;
		/* Reset PLL2DIVR register */
		RCC->PLL2DIVR = 0x00000000;
		/* Reset PLL2FRACR register */
		RCC->PLL2FRACR = 0x00000000;
		/* Reset PLL3DIVR register */
		RCC->PLL3DIVR = 0x00000000;
		/* Reset PLL3FRACR register */
		RCC->PLL3FRACR = 0x00000000;
		/* Reset HSEBYP bit */
		RCC->CR &= (uint32_t)0xFFFBFFFF;
		/* Disable all interrupts */
		RCC->CIER = 0x00000000;

		/* Change the switch matrix read issuing capability to 1 for the AXI SRAM target (Target 7) */
		HWREG(0x51008108) = 0x000000001;
}
#endif