
# stm32h743_lds :=
# stm32h743_lds += ./arch/arm/armv7e_m/armv7e_m.ld
# stm32h743_lds += ./arch/arm/armv7e_m/stm32h7/stm32h743/stm32h743.ld  # should be linked before stm32h.ld
# stm32h743_lds += ./arch/arm/armv7e_m/stm32h7/stm32h7.ld

stm32h743_srcs := 
stm32h743_srcs += ./if/mcu/mcu-init.cpp
stm32h743_srcs += ./arch/arm/stm32/dio.cpp
stm32h743_srcs += ./arch/arm/armv7e_m/systick.cpp
stm32h743_srcs += ./arch/arm/armv7e_m/debug.cpp
stm32h743_srcs += $(wildcard ./arch/arm/armv7e_m/mmreg/*.cpp)
stm32h743_srcs += $(wildcard ./arch/arm/armv7e_m/stm32h7/mmreg/*.cpp)
