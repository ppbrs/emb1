#include "./rcc.h"
#include "./tim2-3.h"
#include "arch/arm/stm32/mmreg/gpio.h"
#include "arch/arm/stm32/mmreg/i2c.h"

[[gnu::section(".bss.mmreg.gpioa")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOA;
[[gnu::section(".bss.mmreg.gpiob")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOB;
[[gnu::section(".bss.mmreg.gpioc")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOC;
[[gnu::section(".bss.mmreg.gpiod")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOD;
[[gnu::section(".bss.mmreg.gpioe")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOE;
[[gnu::section(".bss.mmreg.gpiof")]] volatile struct stm32::mmreg::GPIO::GPIO stm32::mmreg::GPIO::GPIOF;
[[gnu::section(".bss.mmreg.rcc")]] volatile struct stm32f0::mmreg::RCC::RCC stm32f0::mmreg::RCC::RCC;
[[gnu::section(".bss.mmreg.tim2")]] volatile struct stm32f0::mmreg::TIM2::TIM2 stm32f0::mmreg::TIM2::TIM2;
[[gnu::section(".bss.mmreg.tim3")]] volatile struct stm32f0::mmreg::TIM3::TIM3 stm32f0::mmreg::TIM3::TIM3;
[[gnu::section(".bss.mmreg.i2c1")]] volatile struct stm32::mmreg::I2C::I2C stm32::mmreg::I2C::I2C1;
[[gnu::section(".bss.mmreg.i2c2")]] volatile struct stm32::mmreg::I2C::I2C stm32::mmreg::I2C::I2C2;
