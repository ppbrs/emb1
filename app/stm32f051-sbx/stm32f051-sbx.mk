# ==============================================================================
# STM32F051-SBX (currently STM32F051x8)
# ==============================================================================
app_name := stm32f051-sbx
app_dir := ./app/$(app_name)
toolchain := $(EMB1_TOOLCHAIN)

# ------------------------------------------------------------------------------
# include directories

stm32f051_sbx_freertos_incs := $(freertos_kernel_1051_incs)
stm32f051_sbx_freertos_incs += ./arch/arm/armv6_m/stm32f0/freertos-10.5.1/
stm32f051_sbx_freertos_incs += $(app_dir)/freertos

stm32f051_sbx_incs := $(stm32_incs)
stm32f051_sbx_incs += $(stm32f051_sbx_freertos_incs)

# ------------------------------------------------------------------------------
# source files

stm32f051_sbx_freertos_srcs := $(freertos_kernel_1051_srcs)
stm32f051_sbx_freertos_srcs += ./arch/arm/armv6_m/stm32f0/freertos-10.5.1/port.cpp
stm32f051_sbx_freertos_srcs += $(app_dir)/freertos/freertos_custom.cpp

stm32f051_sbx_srcs :=
stm32f051_sbx_srcs += $(app_dir)/main.cpp
stm32f051_sbx_srcs += $(app_dir)/mcu-init.cpp
stm32f051_sbx_srcs += $(app_dir)/nvic.cpp
stm32f051_sbx_srcs += $(app_dir)/tick.cpp
stm32f051_sbx_srcs += $(stm32f051_sbx_freertos_srcs)
stm32f051_sbx_srcs += $(stm32f051_srcs)
stm32f051_sbx_srcs += ./arch/arm/armv6_m/stm32f0/chrono.cpp
stm32f051_sbx_srcs += ./arch/arm/armv6_m/stm32f0/stm32f051/startup.cpp

stm32f051_sbx_objs =  $(patsubst %.c,   $(stm32f051_sbx_build_dir)/%.c.o,   $(filter %.c,   $(stm32f051_sbx_srcs)))
stm32f051_sbx_objs += $(patsubst %.cpp, $(stm32f051_sbx_build_dir)/%.cpp.o, $(filter %.cpp, $(stm32f051_sbx_srcs)))
stm32f051_sbx_deps := $(stm32f051_sbx_objs:.o=.d)

# ------------------------------------------------------------------------------
# outputs

stm32f051_sbx_elf := $(binaries_dir)/$(app_name).$(toolchain).elf
stm32f051_sbx_disasm := $(binaries_dir)/$(app_name).$(toolchain).disasm
stm32f051_sbx_ihex := $(binaries_dir)/$(app_name).$(toolchain).ihex
stm32f051_sbx_map := $(binaries_dir)/$(app_name).$(toolchain).map
stm32f051_sbx_sections := $(binaries_dir)/$(app_name).$(toolchain).sections
stm32f051_sbx_segments := $(binaries_dir)/$(app_name).$(toolchain).segments
stm32f051_sbx_symbols := $(binaries_dir)/$(app_name).$(toolchain).symbols

stm32f051_sbx_build_dir := $(objects_dir)/$(app_name)/$(toolchain)
# ------------------------------------------------------------------------------
# linking

stm32f051_sbx_lds := $(app_dir)/stm32f051-sbx.ld

stm32f051_sbx_ldflags := $(stm32_ldflags)

# ------------------------------------------------------------------------------
# compiling

stm32f051_sbx_cflags := $(stm32_cflags)
stm32f051_sbx_cxxflags := $(stm32_cxxflags)


stm32f051_sbx_cflags += -mfloat-abi=soft
stm32f051_sbx_cflags += -mcpu=cortex-m0
stm32f051_sbx_cflags += -mthumb
stm32f051_sbx_cflags += -march=armv6-m

stm32f051_sbx_cxxflags += -mfloat-abi=soft
stm32f051_sbx_cxxflags += -mcpu=cortex-m0
stm32f051_sbx_cxxflags += -mthumb
stm32f051_sbx_cxxflags += -march=armv6-m

# https://github.com/martinribelotta/cortex-m-llvm/blob/master/scripts/cortex-m0.mk
# ARCH_FLAGS := --target=thumbv6m-unknown-none-eabi
# ARCH_FLAGS += -mthumb
# ARCH_FLAGS += -march=armv6m
# ARCH_FLAGS += -mcpu=cortex-m0
# ARCH_FLAGS += -mfloat-abi=soft
# ARCH_FLAGS += -mfpu=none

# ------------------------------------------------------------------------------

#
# Getting additional information from the ELF file
#
stm32f051-sbx: $(stm32f051_sbx_elf) Makefile
	@echo
	$(info INFO: POST-BUILDING `$@`.)

# Disassemble executable sections:
	@$(stm32_toolchain_objdump) -d $(stm32f051_sbx_elf) > $(stm32f051_sbx_disasm)
# Create files with sections and symbols:
	@$(stm32_toolchain_readelf) --segments $(stm32f051_sbx_elf) > $(stm32f051_sbx_segments)
	@$(stm32_toolchain_readelf) --sections --wide $(stm32f051_sbx_elf) > $(stm32f051_sbx_sections)
	@$(stm32_toolchain_readelf) --symbols --wide $(stm32f051_sbx_elf) > $(stm32f051_sbx_symbols)
# Make HEX file:
	@$(stm32_toolchain_objcopy) -O ihex $(stm32f051_sbx_elf) $(stm32f051_sbx_ihex)
# List contents of ihex file in a human-readable form:
	@$(stm32_toolchain_objdump) --full-contents $(stm32f051_sbx_elf) > $(stm32f051_sbx_ihex).txt
# Print size:
	@$(stm32_toolchain_size) $(stm32f051_sbx_elf)
	$(info INFO: BUILDING `$@` DONE.)

#
# Linking
#
$(stm32f051_sbx_elf): $(stm32f051_sbx_objs) Makefile
	@echo
	$(info INFO: LINKING `$@`.)
	@mkdir -p $(shell dirname $@)

	@$(stm32_toolchain_ld) \
		$(stm32f051_sbx_objs) \
		$(foreach D, $(stm32f051_sbx_lds), -T$(D)) \
		-Map=$(stm32f051_sbx_map) \
		$(stm32f051_sbx_ldflags) \
		-L/opt/gcc-arm-none-eabi-10.3-2021.10/lib/gcc/arm-none-eabi/10.3.1/thumb/v6-m/nofp/ \
		-lgcc \
		-o $(stm32f051_sbx_elf)

#
# Building C++ source files
#
$(stm32f051_sbx_build_dir)/%.cpp.o: %.cpp Makefile
	@echo
	$(info INFO: BUILDING `$@` FROM `$<`.)
	@mkdir -p $(shell dirname $@)
	@$(stm32_toolchain_cpp) \
		$(stm32f051_sbx_cxxflags) \
		$(foreach D, $(stm32f051_sbx_incs), -I$(D)) \
		-c $< -o $@

#
# Building C source files
#
$(stm32f051_sbx_build_dir)/%.c.o: %.c Makefile
	@echo
	$(info INFO: BUILDING `$@` FROM `$<`.)
	@mkdir -p $(shell dirname $@)
	@$(stm32_toolchain_c) \
		$(stm32f051_sbx_cflags) \
		$(foreach D, $(stm32f051_sbx_incs), -I$(D)) \
		-c $< -o $@

-include $(stm32f051_sbx_deps)
