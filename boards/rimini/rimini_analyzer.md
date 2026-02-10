
STM32H743 Analyzer Report
=========================
  
Created on Fri 2026-03-20 at 14:03:04.872632.  
Target: stm32h743.rimini.cpu0, running.  
***  
Flash size = 2048 kB.  
Revision V  
Package = LQFP100.  
UID = 30383637 34305110 00490029  
***
# Clock
  
* HSI is ON and ready, 64Mhz / 1 = 64.0 MHz.  
* HSI48 is OFF or not ready  
* HSE is OFF or not ready  
* PLL1 is OFF.  
* PLL2 is OFF.  
* PLL3 is OFF.  
* System clock is from HSI: 64.0 MHz.  
* SysTick: 8.0 MHz.  
* CPU clock (D1) == system clock: 64.0 MHz.  
* AXI clock (D1): 64.0 MHz.  
* AHB1 clock (D2): 64.0 MHz.  
* AHB2 clock (D2): 64.0 MHz.  
* AHB3 clock (D1): 64.0 MHz.  
* AHB4 clock (D3): 64.0 MHz.  
* APB1 clock (D2): 64.0 MHz.  
* APB2 clock (D2): 64.0 MHz.  
* APB3 clock (D1): 64.0 MHz.  
* APB4 clock (D3): 64.0 MHz.  
* TIMx clock (D2, advanced-control timers, TIM1/TIM8): 64.0 MHz.  
* TIMy clock (D2, general-purpose timers, other than TIM1/TIM8): 64.0 MHz.  
* HRTIM clock (D2): 64.0 MHz.  
* MCO1 is OFF.  
* MCO2 is OFF.  
* PER clock: 64.0 MHz.  
***
# SysTick (System Timer)
  
* Timer enabled. Current value = 496.  
* Clock source = processor clock, 64.0 MHz  
* Reload frequency: 63936.06393606394 Hz.  
* Reload period: 1001 ticks = 15641 ns.  
* SysTick exception enabled.  
* Calibration: NOREF=0, SKEW=1, TENMS=1000  
***
# Core (ARM v7e-m)
  
* PC from PCSR = 0x080004d6  
* Core is running. Core must be halted for reading core registers.  
***  
* PC = Program Counter = R15 = 0x00000000  
* LR = Link Register = R14 = 0x00000000  
* SP = Stack Pointer = R13 = 0x00000000  
	* MSP = Main Stack Pointer = 0x00000000  
	* PSP = Process Stack Pointer = 0x00000000  
	* SPSEL = 0 = MSP is the current stack pointer.  
* nPRIV = 0 = Thread mode privilege level is Privileged.  
* FPCA = 0 = No floating-point context active.  
* Exceptions and interrupts:  
	* PRIMASK = 0 = No effect.  
	* FAULTMASK = 0 = No effect.  
	* BASEPRI = 0 = No effect.  
	* ISR_NUMBER = 0 = Thread mode.  
* APSR = Application status:  
	* N = Negative flag = 0  
	* Z = Zero flag = 0  
	* C = Carry or borrow flag = 0  
	* V = Overflow flag = 0  
	* Q = DSP overflow and saturation flag = 0  
	* GE = Greater than or Equal flags = 0  
* EPSR = Execution status:  
	* ICI/IT = Interruptible-continuable instruction / = IT instruction = 0  
	* T = Thumb state = 0  
***  
* I-Cache disabled  
* D-Cache disabled  
***
# MPU (ARM v7e-m)
  
* 16 MPU regions.  
* MPU disabled  
* MPU is disabled during hard fault, NMI, and FAULTMASK handlers, regardless of the value of the ENABLE bit.  
* If the MPU is enabled, the default memory map cannot be used as a background region for privileged software accesses.  
***
# ADC
  
* Analog switches  
	* PA0 (ADC1_INP16) <---> PA0_C (ADC12_INN1, ADC12_INP0)  
	* PA1 (ADC1_INN16, ADC1_INP17) <---> PA1_C (ADC12_INP1)  
	* PC2 (ADC123_INN11, ADC123_INP12) <---> PC2_C (ADC3_INN1, ADC3_INP0)  
	* PC3 (ADC12_INN12, ADC12_INP13) <---> PC3_C (ADC3_INP1)  
	* Supply voltage booster disabled.  
* ADC kernel clock is from PLL2.P which is OFF.
# DAC1
  
* DAC1 disabled  
***
# DAC2
  
* DAC2 disabled  
***
# GPIO

## GPIOA

|Pin|Mode|Pull up/down|Output type|Alternate|Output speed|Input|Output|Lock|
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
|PA0|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PA1|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PA2|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PA3|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PA4|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PA5|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PA6|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PA7|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PA8|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PA9|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PA10|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PA11|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PA12|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PA13|2: Alternate|2: Pull-down|1: open-drain|15: TBD-A-13-15|2: High|1|1|1|
|PA14|2: Alternate|2: Pull-down|1: open-drain|11: TBD-A-14-11|2: High|1|1|1|
|PA15|2: Alternate|2: Pull-down|1: open-drain|10: TBD-A-15-10|2: High|1|1|1|
  
***
## GPIOB

|Pin|Mode|Pull up/down|Output type|Alternate|Output speed|Input|Output|Lock|
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
|PB0|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PB1|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PB2|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PB3|2: Alternate|2: Pull-down|1: open-drain|15: TBD-B-3-15|2: High|1|1|1|
|PB4|2: Alternate|2: Pull-down|1: open-drain|15: TBD-B-4-15|2: High|1|1|1|
|PB5|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PB6|3: Analog|3: |0: |-|3: Very high|0|0|Unlocked|
|PB7|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PB8|3: Analog|3: |0: |-|3: Very high|0|0|Unlocked|
|PB9|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PB10|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PB11|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PB12|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PB13|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PB14|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PB15|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
  
***
## GPIOC

|Pin|Mode|Pull up/down|Output type|Alternate|Output speed|Input|Output|Lock|
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
|PC0|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PC1|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PC2|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PC3|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PC4|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PC5|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PC6|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PC7|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PC8|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PC9|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PC10|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PC11|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PC12|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PC13|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PC14|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PC15|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
  
***
## GPIOD

|Pin|Mode|Pull up/down|Output type|Alternate|Output speed|Input|Output|Lock|
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
|PD0|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PD1|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PD2|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PD3|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PD4|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PD5|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PD6|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PD7|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PD8|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PD9|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PD10|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PD11|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PD12|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PD13|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PD14|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PD15|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
  
***
## GPIOF

|Pin|Mode|Pull up/down|Output type|Alternate|Output speed|Input|Output|Lock|
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
|PF0|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PF1|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PF2|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PF3|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PF4|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PF5|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PF6|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PF7|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PF8|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PF9|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PF10|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PF11|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PF12|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PF13|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PF14|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
|PF15|3: Analog|3: |1: open-drain|-|3: Very high|1|1|1|
  
***
# Advanced-control timers
  
* TIMx clock: 64.0 MHz.
## TIM1 (disabled)
  
***
## TIM8 (disabled)
  
***
# HRTIM
  
* Master timer disabled  
* Timer A disabled  
* Timer B disabled  
* Timer C disabled  
* Timer D disabled  
* Timer E disabled  
***
# TIM6
  
* clock disabled  
***
# TIM7
  
* clock disabled  
***
# DMA

|DMA|Str|En|Direction|Circular|Double|Target|Priority|MSIZE|PSIZE|MINC|PINC|NDT|PAR|M0A|M1A|Mode|Bufferable|Interrupts|
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
|DMA1|S0|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
|DMA1|S1|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
|DMA1|S2|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
|DMA1|S3|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
|DMA1|S4|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
|DMA1|S5|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
|DMA1|S6|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
|DMA1|S7|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
|DMA2|S0|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
|DMA2|S1|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
|DMA2|S2|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
|DMA2|S3|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
|DMA2|S4|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
|DMA2|S5|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
|DMA2|S6|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
|DMA2|S7|-|Per-to-Mem|-|-|0|Low|8-bit|8-bit|-|-|0||||Direct|-|-|
  
***
# DMAMUX

## DMAMUX1

|channel|input request|
| :--- | :--- |
|0 (DMA1, stream 0)||
|1 (DMA1, stream 1)||
|2 (DMA1, stream 2)||
|3 (DMA1, stream 3)||
|4 (DMA1, stream 4)||
|5 (DMA1, stream 5)||
|6 (DMA1, stream 6)||
|7 (DMA1, stream 7)||
|8 (DMA2, stream 0)||
|9 (DMA2, stream 1)||
|10 (DMA2, stream 2)||
|11 (DMA2, stream 3)||
|12 (DMA2, stream 4)||
|13 (DMA2, stream 5)||
|14 (DMA2, stream 6)||
|15 (DMA2, stream 7)||
  
***
## DMAMUX2
  
***
# Clock reset/enabled D1

|Peripheral|Bus|RST|EN|
| :--- | :--- | :--- | :--- |
|SDMMC1 and SDMMC1 Delay|AHB3|?|-|
|QUADSPI and QUADSPI Delay|AHB3|?|-|
|FMC|AHB3|?|-|
|JPGDEC|AHB3|?|-|
|DMA2D|AHB3|?|-|
|MDMA|AHB3|?|-|
  
***
# Clock reset/enabled D2

|Peripheral|Bus|RST|EN|
| :--- | :--- | :--- | :--- |
|ADC12|AHB1|?|-|
|DAC12|APB1|?|-|
|DMA1|AHB1|?|-|
|DMA2|AHB1|?|-|
|Ethernet Reception|AHB1|?|-|
|Ethernet Transmission|AHB1|?|-|
|Ethernet MAC bus interface|AHB1|?|-|
|USB1 PHY|AHB1|?|-|
|USB1 OTG Peripheral|AHB1|?|-|
|USB2 PHY|AHB1|?|-|
|USB2 OTG Peripheral|AHB1|?|-|
|HRTIM|APB2|?|-|
|TIM6|APB1|?|-|
|TIM7|APB1|?|-|
|SPI1|APB2|?|-|
|SPI2|APB1|?|-|
|SPI3|APB1|?|-|
|SPI4|APB2|?|-|
|SPI5|APB2|?|-|
|I2C1|APB1|?|-|
|I2C2|APB1|?|-|
|I2C3|APB1|?|-|
|USART1|APB2|?|-|
|USART2|APB1|?|-|
|USART3|APB1|?|-|
|UART4|APB1|?|-|
|UART5|APB1|?|-|
|USART6|APB2|?|-|
|UART7|APB1|?|-|
|UART8|APB1|?|-|
|DFSDM1|APB2|?|-|
  
***
# Clock reset/enabled D3

|Peripheral|Bus|RST|EN|
| :--- | :--- | :--- | :--- |
|ADC3|AHB4|?|-|
|GPIOA|AHB4|?|-|
|GPIOB|AHB4|?|-|
|GPIOC|AHB4|?|-|
|GPIOD|AHB4|?|-|
|GPIOE|AHB4|?|-|
|GPIOF|AHB4|?|-|
|GPIOG|AHB4|?|-|
|GPIOH|AHB4|?|-|
|GPIOI|AHB4|?|-|
|GPIOJ|AHB4|?|-|
|GPIOK|AHB4|?|-|
|SYSCFG|APB4|?|-|
|SPI6|APB4|?|-|
|I2C4|APB4|?|-|
|LPUART1|APB4|?|-|
  
***
# QUADSPI
  
* QUADSPI kernel input clock is from AHB3: 64.0 MHz.  
* Disabled.  
* QUADSPI CLK frequency = 64.0 MHz / 1 = 64.0 MHz.  
* size = 2^(0+1) = 2 B = 0.0 MB  
***
# USB
  
* Kernel clock disabled.  
* USB regulator disabled = external USB supply  
* USB33RDY: 0  
* USB33DEN: 0  
***