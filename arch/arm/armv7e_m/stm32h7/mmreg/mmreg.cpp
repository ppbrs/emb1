#include "./debug.h"
#include "./rcc.h"
#include "./tim2-3-4-5.h"
#include "./usart.h"
#include "arch/arm/stm32/mmreg/gpio.h"

[[gnu::section(".bss.mmreg.gpioa")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOA;
[[gnu::section(".bss.mmreg.gpiob")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOB;
[[gnu::section(".bss.mmreg.gpioc")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOC;
[[gnu::section(".bss.mmreg.gpiod")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOD;
[[gnu::section(".bss.mmreg.gpioe")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOE;
[[gnu::section(".bss.mmreg.gpiof")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOF;
[[gnu::section(".bss.mmreg.gpiog")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOG;
[[gnu::section(".bss.mmreg.gpioh")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOH;
[[gnu::section(".bss.mmreg.gpioi")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOI;
[[gnu::section(".bss.mmreg.gpioj")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOJ;
[[gnu::section(".bss.mmreg.gpiok")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOK;
[[gnu::section(".bss.mmreg.rcc")]] volatile struct stm32h7::mmreg::RCC::RCC stm32h7::mmreg::RCC::RCC;
[[gnu::section(".bss.mmreg.tim2")]] volatile struct stm32h7::mmreg::TIM2::TIM2 stm32h7::mmreg::TIM2::TIM2;
[[gnu::section(".bss.mmreg.tim3")]] volatile struct stm32h7::mmreg::TIM3::TIM3 stm32h7::mmreg::TIM3::TIM3;
[[gnu::section(".bss.mmreg.tim4")]] volatile struct stm32h7::mmreg::TIM4::TIM4 stm32h7::mmreg::TIM4::TIM4;
[[gnu::section(".bss.mmreg.tim5")]] volatile struct stm32h7::mmreg::TIM5::TIM5 stm32h7::mmreg::TIM5::TIM5;

[[gnu::section(".bss.mmreg.dbg_swo")]] volatile struct stm32h7::mmreg::DEBUG::SWO::SWO stm32h7::mmreg::DEBUG::SWO::SWO;
[[gnu::section(".bss.mmreg.dbg_swtf")]] volatile struct stm32h7::mmreg::DEBUG::SWTF::SWTF stm32h7::mmreg::DEBUG::SWTF::SWTF;
[[gnu::section(".bss.mmreg.dbgmcu")]] volatile struct stm32h7::mmreg::DEBUG::DBGMCU::DBGMCU stm32h7::mmreg::DEBUG::DBGMCU::DBGMCU;

[[gnu::section(".bss.mmreg.usart1")]] volatile struct stm32h7::mmreg::USART::USART stm32h7::mmreg::USART::USART1;
[[gnu::section(".bss.mmreg.usart2")]] volatile struct stm32h7::mmreg::USART::USART stm32h7::mmreg::USART::USART2;
[[gnu::section(".bss.mmreg.usart3")]] volatile struct stm32h7::mmreg::USART::USART stm32h7::mmreg::USART::USART3;
[[gnu::section(".bss.mmreg.uart4")]] volatile struct stm32h7::mmreg::USART::USART stm32h7::mmreg::USART::UART4;
[[gnu::section(".bss.mmreg.uart5")]] volatile struct stm32h7::mmreg::USART::USART stm32h7::mmreg::USART::UART5;
[[gnu::section(".bss.mmreg.usart6")]] volatile struct stm32h7::mmreg::USART::USART stm32h7::mmreg::USART::USART6;
[[gnu::section(".bss.mmreg.uart7")]] volatile struct stm32h7::mmreg::USART::USART stm32h7::mmreg::USART::UART7;
[[gnu::section(".bss.mmreg.uart8")]] volatile struct stm32h7::mmreg::USART::USART stm32h7::mmreg::USART::UART8;
