# ==============================================================================
#
# STM32H743-SANDBOX
#

-include 3party/freertos-kernel-1051.mk
-include arch/arm/stm32/stm32.mk

# ------------------------------------------------------------------------------
# include directories

stm32h743_freertos_kernel_1051_incl_dirs := $(freertos_kernel_1051_incl_dirs)
stm32h743_freertos_kernel_1051_incl_dirs += ./arch/arm/armv7e_m/stm32h7/stm32h743/freertos-10.5.1/

stm32h743_sbx_freertos_kernel_1051_incl_dirs := $(stm32h743_freertos_kernel_1051_incl_dirs)
stm32h743_sbx_freertos_kernel_1051_incl_dirs += ./app/stm32h743_sbx/freertos

stm32h743_sbx_incl_dirs := $(stm32_incl_dirs)
stm32h743_sbx_incl_dirs += $(stm32h743_sbx_freertos_kernel_1051_incl_dirs)

# ------------------------------------------------------------------------------
# source files

stm32h743_freertos_kernel_1051_srcs := $(freertos_kernel_1051_srcs)
stm32h743_freertos_kernel_1051_srcs += ./arch/arm/armv7e_m/stm32h7/stm32h743/freertos-10.5.1/port.cpp

stm32h743_sbx_freertos_kernel_1051_srcs := $(stm32h743_freertos_kernel_1051_srcs)
stm32h743_sbx_freertos_kernel_1051_srcs += ./app/stm32h743_sbx/freertos/freertos_custom.c
stm32h743_sbx_srcs =
stm32h743_sbx_srcs += $(stm32h743_srcs)
stm32h743_sbx_srcs += ./app/stm32h743_sbx/error.cpp
stm32h743_sbx_srcs += ./app/stm32h743_sbx/chrono.cpp
stm32h743_sbx_srcs += ./app/stm32h743_sbx/main.cpp
stm32h743_sbx_srcs += ./app/stm32h743_sbx/mcu-init.cpp
stm32h743_sbx_srcs += ./app/stm32h743_sbx/nvic.cpp
stm32h743_sbx_srcs += ./app/stm32h743_sbx/tick.cpp
stm32h743_sbx_srcs += ./arch/arm/armv7e_m/stm32h7/stm32h743/startup.cpp
stm32h743_sbx_srcs += ./app/stm32h743_sbx/app-chrono/app-chrono.cpp
stm32h743_sbx_srcs += ./app/stm32h743_sbx/app-containers/app-containers.cpp
# stm32h743_sbx_srcs += ./common/error.cpp
stm32h743_sbx_srcs += $(stm32h743_sbx_freertos_kernel_1051_srcs)

stm32h743_sbx_objs =  $(patsubst %.c,   $(stm32h743_sbx_build_dir)/%.c.o,   $(filter %.c,   $(stm32h743_sbx_srcs)))
stm32h743_sbx_objs += $(patsubst %.cpp, $(stm32h743_sbx_build_dir)/%.cpp.o, $(filter %.cpp, $(stm32h743_sbx_srcs)))
stm32h743_sbx_deps = $(stm32h743_sbx_objs:.o=.d)

# ------------------------------------------------------------------------------
# outputs

stm32h743_sbx_disasm = $(binaries_dir)/stm32h743-sbx.disasm
stm32h743_sbx_elf = $(binaries_dir)/stm32h743-sbx.elf
stm32h743_sbx_ihex = $(binaries_dir)/stm32h743-sbx.ihex
stm32h743_sbx_map = $(binaries_dir)/stm32h743-sbx.map
stm32h743_sbx_sections = $(binaries_dir)/stm32h743-sbx.sections
stm32h743_sbx_segments = $(binaries_dir)/stm32h743-sbx.segments
stm32h743_sbx_symbols = $(binaries_dir)/stm32h743-sbx.symbols

stm32h743_sbx_build_dir := $(objects_dir)/stm32h743_sbx

# ------------------------------------------------------------------------------
# linking

stm32h743_sbx_lds := app/stm32h743_sbx/stm32h743-sbx.ld

stm32h743_sbx_ldflags := $(stm32_ldflags)

# ------------------------------------------------------------------------------
# compiling

stm32h743_sbx_cflags := $(stm32_cflags)
stm32h743_sbx_cxxflags := $(stm32_cxxflags)

stm32h743_sbx_cflags += -mfloat-abi=hard
stm32h743_sbx_cflags += -mcpu=cortex-m7
stm32h743_sbx_cflags += -mfpu=fpv5-d16
stm32h743_sbx_cflags += -march=armv7e-m

stm32h743_sbx_cxxflags += -mfloat-abi=hard
stm32h743_sbx_cxxflags += -mcpu=cortex-m7
stm32h743_sbx_cxxflags += -mfpu=fpv5-d16
stm32h743_sbx_cxxflags += -march=armv7e-m

# ------------------------------------------------------------------------------

#
# Getting additional information from the ELF file
#
stm32h743-sbx: $(stm32h743_sbx_elf) Makefile
	@echo
	$(info INFO: BUILDING `$@`.)

# Disassemble executable sections:
	@$(stm32_toolchain_objdump) -d $(stm32h743_sbx_elf) > $(stm32h743_sbx_disasm)
# Create files with sections and symbols:
	@$(stm32_toolchain_readelf) --segments $(stm32h743_sbx_elf) > $(stm32h743_sbx_segments)
	@$(stm32_toolchain_readelf) --sections --wide $(stm32h743_sbx_elf) > $(stm32h743_sbx_sections)
	@$(stm32_toolchain_readelf) --symbols --wide $(stm32h743_sbx_elf) > $(stm32h743_sbx_symbols)
# Make HEX file:
	@$(stm32_toolchain_objcopy) -O ihex $(stm32h743_sbx_elf) $(stm32h743_sbx_ihex)
# List contents of ihex file in a human-readable form:
	@$(stm32_toolchain_objdump) -s $(stm32h743_sbx_elf) > $(stm32h743_sbx_ihex).txt
# Print size:
	@$(stm32_toolchain_size) $(stm32h743_sbx_elf)
	$(info INFO: BUILDING `$@` DONE.)

#
# Linking
#
$(stm32h743_sbx_elf): $(stm32h743_sbx_objs) Makefile
	@echo
	$(info INFO: BUILDING `$(stm32h743_sbx_elf)`)
	@mkdir -p $(shell dirname $@)

	@$(stm32_toolchain_ld) \
		$(stm32h743_sbx_objs) \
		$(foreach D, $(stm32h743_sbx_lds), -T$(D)) \
		-Map=$(stm32h743_sbx_map) \
		$(stm32h743_sbx_ldflags) \
		-L/opt/gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi/lib/thumb/v7e-m+fp/hard/ \
		-L/opt/gcc-arm-none-eabi-10.3-2021.10/lib/gcc/arm-none-eabi/10.3.1/thumb/v7e-m+fp/hard/ \
		-o $(stm32h743_sbx_elf)

#
# Building C++ source files
#
$(stm32h743_sbx_build_dir)/%.cpp.o: %.cpp Makefile
	@echo
	$(info INFO: BUILDING `$@` FROM `$<`.)
	@mkdir -p $(shell dirname $@)
	@$(stm32_toolchain_cpp) \
		$(stm32h743_sbx_cxxflags) \
		$(foreach D, $(stm32h743_sbx_incl_dirs), -I$(D)) \
		-c $< -o $@

#
# Building C source files
#
$(stm32h743_sbx_build_dir)/%.c.o: %.c Makefile
	@echo
	$(info INFO: BUILDING `$@` FROM `$<`.)
	@mkdir -p $(shell dirname $@)
	@$(stm32_toolchain_c) \
		$(stm32h743_sbx_cflags) \
		$(foreach D, $(stm32h743_sbx_incl_dirs), -I$(D)) \
		-c $< -o $@

-include $(stm32h743_sbx_deps)
