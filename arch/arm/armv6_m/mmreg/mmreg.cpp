#include "nvic.h"
#include "scb.h"
#include "systick.h"

[[gnu::section(".bss.mmreg.nvic")]] volatile struct armv6_m::mmreg::NVIC::NVIC armv6_m::mmreg::NVIC::NVIC;
[[gnu::section(".bss.mmreg.scb")]] volatile struct armv6_m::mmreg::SCB::SCB armv6_m::mmreg::SCB::SCB;
[[gnu::section(".bss.mmreg.systick")]] volatile struct armv6_m::mmreg::SysTick::SYST armv6_m::mmreg::SysTick::SYST;
