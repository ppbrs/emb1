#
# LINKER SCRIPTS
#
# stm32f051_lds :=
# Order of linker scripts matters.
#
# stm32f051.ld: apb=0x40000000, ahb1=0x40020000, ahb2=0x48000000
#
# stm32f051_lds += ./arch/arm/armv6_m/stm32f0/stm32f051/stm32f051.ld
#
# armv6_m.ld: 0xE0000000
#
# stm32f051_lds += ./arch/arm/armv6_m/armv6_m.ld
#
# stm32f0.ld: flash, sram
#
# stm32f051_lds += ./arch/arm/armv6_m/stm32f0/stm32f0.ld

# ==================================================================================================
#
# SOURCE FILES
#
stm32f051_srcs = 
stm32f051_srcs += ./arch/arm/armv6_m/stm32f0/usart.cpp
stm32f051_srcs += ./arch/arm/armv6_m/systick.cpp
stm32f051_srcs += ./arch/arm/stm32/dio.cpp
stm32f051_srcs += ./arch/arm/stm32/i2c.cpp
stm32f051_srcs += ./arch/arm/stm32/pio.cpp
stm32f051_srcs += ./if/mcu/mcu-init.cpp
stm32f051_srcs += $(wildcard ./arch/arm/armv6_m/mmreg/*.cpp)
stm32f051_srcs += $(wildcard ./arch/arm/armv6_m/stm32f0/mmreg/*.cpp)
stm32f051_srcs += $(wildcard ./libc/*.cpp)
