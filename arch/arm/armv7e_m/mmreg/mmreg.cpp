#include "cache.h"
#include "debug.h"
#include "fpu.h"
#include "itm.h"
#include "mpu.h"
#include "nvic.h"
#include "scb.h"
#include "systick.h"

[[gnu::section(".bss.mmreg.cache")]] volatile struct armv7e_m::mmreg::cache::Cache armv7e_m::mmreg::cache::cache;
[[gnu::section(".bss.mmreg.debug2")]] volatile struct armv7e_m::mmreg::DEBUG::DEBUG armv7e_m::mmreg::DEBUG::DEBUG;
[[gnu::section(".bss.mmreg.fpu")]] volatile struct armv7e_m::mmreg::SCB::FP armv7e_m::mmreg::SCB::FP;
[[gnu::section(".bss.mmreg.itm")]] volatile struct armv7e_m::mmreg::ITM::ITM armv7e_m::mmreg::ITM::ITM;
[[gnu::section(".bss.mmreg.mpu")]] volatile struct armv7e_m::mmreg::MPU::MPU armv7e_m::mmreg::MPU::MPU;
[[gnu::section(".bss.mmreg.nvic")]] volatile struct armv7e_m::mmreg::NVIC::NVIC armv7e_m::mmreg::NVIC::NVIC;
[[gnu::section(".bss.mmreg.nvic_stir")]] volatile uint32_t armv7e_m::mmreg::NVIC::STIR;
[[gnu::section(".bss.mmreg.scb")]] volatile struct armv7e_m::mmreg::SCB::SCB armv7e_m::mmreg::SCB::SCB;
[[gnu::section(".bss.mmreg.systick")]] volatile struct armv7e_m::mmreg::SysTick::SYST armv7e_m::mmreg::SysTick::SYST;
