# ==============================================================================
# RIGA-COMM-00
# ==============================================================================
app_name := riga-comm-00
app_dir := ./app/$(app_name)
toolchain := $(EMB1_TOOLCHAIN)

# ------------------------------------------------------------------------------
# include directories

riga_comm_00_freertos_incs := $(freertos_kernel_1051_incs)
riga_comm_00_freertos_incs += ./arch/arm/armv6_m/stm32f0/freertos-10.5.1/
riga_comm_00_freertos_incs += $(app_dir)/freertos

riga_comm_00_incs := $(stm32_incs)
riga_comm_00_incs += $(riga_comm_00_freertos_incs)

# ------------------------------------------------------------------------------
# source files

riga_comm_00_freertos_srcs := $(freertos_kernel_1051_srcs)
riga_comm_00_freertos_srcs += ./arch/arm/armv6_m/stm32f0/freertos-10.5.1/port.cpp
riga_comm_00_freertos_srcs += $(app_dir)/freertos/freertos_custom.cpp

riga_comm_00_srcs :=
riga_comm_00_srcs += $(app_dir)/app.cpp
riga_comm_00_srcs += $(app_dir)/main.cpp
riga_comm_00_srcs += $(app_dir)/mcu-init.cpp
riga_comm_00_srcs += $(app_dir)/nvic.cpp
riga_comm_00_srcs += $(app_dir)/tick.cpp
riga_comm_00_srcs += $(riga_comm_00_freertos_srcs)
riga_comm_00_srcs += $(stm32f051_srcs)
riga_comm_00_srcs += ./common/io/char-stream.cpp
riga_comm_00_srcs += ./arch/arm/armv6_m/stm32f0/stm32f051/startup.cpp
riga_comm_00_srcs += ./libc/stubs.cpp
riga_comm_00_srcs += ./libc/string.cpp

riga_comm_00_objs =  $(patsubst %.c,   $(riga_comm_00_build_dir)/%.c.o,   $(filter %.c,   $(riga_comm_00_srcs)))
riga_comm_00_objs += $(patsubst %.cpp, $(riga_comm_00_build_dir)/%.cpp.o, $(filter %.cpp, $(riga_comm_00_srcs)))
riga_comm_00_deps := $(riga_comm_00_objs:.o=.d)

# ------------------------------------------------------------------------------
# outputs

riga_comm_00_elf := $(binaries_dir)/$(app_name).$(toolchain).elf
riga_comm_00_disasm := $(binaries_dir)/$(app_name).$(toolchain).disasm
riga_comm_00_ihex := $(binaries_dir)/$(app_name).$(toolchain).ihex
riga_comm_00_map := $(binaries_dir)/$(app_name).$(toolchain).map
riga_comm_00_sections := $(binaries_dir)/$(app_name).$(toolchain).sections
riga_comm_00_segments := $(binaries_dir)/$(app_name).$(toolchain).segments
riga_comm_00_symbols := $(binaries_dir)/$(app_name).$(toolchain).symbols

riga_comm_00_build_dir := $(objects_dir)/$(app_name)/$(toolchain)

# ------------------------------------------------------------------------------
# linking

riga_comm_00_lds := $(app_dir)/$(app_name).ld

riga_comm_00_ldflags := $(stm32_ldflags)

# ------------------------------------------------------------------------------
# compiling

riga_comm_00_cflags := $(stm32_cflags)
riga_comm_00_cxxflags := $(stm32_cxxflags)


riga_comm_00_cflags += -mfloat-abi=soft
riga_comm_00_cflags += -mcpu=cortex-m0
riga_comm_00_cflags += -mthumb
riga_comm_00_cflags += -march=armv6-m

riga_comm_00_cxxflags += -mfloat-abi=soft
riga_comm_00_cxxflags += -mcpu=cortex-m0
riga_comm_00_cxxflags += -mthumb
riga_comm_00_cxxflags += -march=armv6-m

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
$(app_name): $(riga_comm_00_elf) Makefile
	@echo
	$(info INFO: POST-BUILDING `$@`.)

# Disassemble executable sections:
	@$(stm32_toolchain_objdump) -d $(riga_comm_00_elf) > $(riga_comm_00_disasm)
# Create files with sections and symbols:
	@$(stm32_toolchain_readelf) --segments $(riga_comm_00_elf) > $(riga_comm_00_segments)
	@$(stm32_toolchain_readelf) --sections --wide $(riga_comm_00_elf) > $(riga_comm_00_sections)
	@$(stm32_toolchain_readelf) --symbols --wide $(riga_comm_00_elf) > $(riga_comm_00_symbols)
# Make HEX file:
	@$(stm32_toolchain_objcopy) -O ihex $(riga_comm_00_elf) $(riga_comm_00_ihex)
# List contents of ihex file in a human-readable form:
	@$(stm32_toolchain_objdump) --full-contents $(riga_comm_00_elf) > $(riga_comm_00_ihex).txt
# Print size:
	@$(stm32_toolchain_size) $(riga_comm_00_elf)
	$(info INFO: BUILDING `$@` DONE.)

#
# Linking
#
$(riga_comm_00_elf): $(riga_comm_00_objs) Makefile
	@echo
	$(info INFO: LINKING `$@`.)
	@mkdir -p $(shell dirname $@)

	@$(stm32_toolchain_ld) \
		$(riga_comm_00_objs) \
		$(foreach D, $(riga_comm_00_lds), -T$(D)) \
		-Map=$(riga_comm_00_map) \
		$(riga_comm_00_ldflags) \
		-L/opt/gcc-arm-none-eabi-10.3-2021.10/lib/gcc/arm-none-eabi/10.3.1/thumb/v6-m/nofp/ \
		-lgcc \
		-o $(riga_comm_00_elf)

#
# Building C++ source files
#
$(riga_comm_00_build_dir)/%.cpp.o: %.cpp Makefile
	@echo
	$(info INFO: BUILDING `$@` FROM `$<`.)
	@mkdir -p $(shell dirname $@)
	@$(stm32_toolchain_cpp) \
		$(riga_comm_00_cxxflags) \
		$(foreach D, $(riga_comm_00_incs), -I$(D)) \
		-c $< -o $@

#
# Building C source files
#
$(riga_comm_00_build_dir)/%.c.o: %.c Makefile
	@echo
	$(info INFO: BUILDING `$@` FROM `$<`.)
	@mkdir -p $(shell dirname $@)
	@$(stm32_toolchain_c) \
		$(riga_comm_00_cflags) \
		$(foreach D, $(riga_comm_00_incs), -I$(D)) \
		-c $< -o $@

-include $(riga_comm_00_deps)
