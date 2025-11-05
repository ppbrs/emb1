# ==============================================================================
# stm32f0-arithmetic-renode
# ==============================================================================

app_name := stm32f0-arithmetic-renode
app_dir := ./app/$(app_name)
toolchain := $(EMB1_TOOLCHAIN)

# ------------------------------------------------------------------------------
# include directories

stm32f0_arithmetic_renode_incs := $(stm32_incs)

# ------------------------------------------------------------------------------
# source files

stm32f0_arithmetic_renode_srcs :=
stm32f0_arithmetic_renode_srcs += $(app_dir)/main.cpp
stm32f0_arithmetic_renode_srcs += $(app_dir)/nvic.cpp
stm32f0_arithmetic_renode_srcs += $(app_dir)/test.cpp
stm32f0_arithmetic_renode_srcs += $(app_dir)/test_imult.cpp
stm32f0_arithmetic_renode_srcs += ./arch/arm/armv6_m/stm32f0/stm32f051/startup.cpp
# stm32f0_arithmetic_renode_srcs += ./libc/stubs.cpp
# stm32f0_arithmetic_renode_srcs += ./libc/string.cpp

stm32f0_arithmetic_renode_objs =  $(patsubst %.c,   $(stm32f0_arithmetic_renode_build_dir)/%.c.o,   $(filter %.c,   $(stm32f0_arithmetic_renode_srcs)))
stm32f0_arithmetic_renode_objs += $(patsubst %.cpp, $(stm32f0_arithmetic_renode_build_dir)/%.cpp.o, $(filter %.cpp, $(stm32f0_arithmetic_renode_srcs)))
stm32f0_arithmetic_renode_deps := $(stm32f0_arithmetic_renode_objs:.o=.d)

# ------------------------------------------------------------------------------
# outputs

stm32f0_arithmetic_renode_elf := $(binaries_dir)/$(app_name).$(toolchain).elf
stm32f0_arithmetic_renode_disasm := $(binaries_dir)/$(app_name).$(toolchain).disasm
stm32f0_arithmetic_renode_ihex := $(binaries_dir)/$(app_name).$(toolchain).ihex
stm32f0_arithmetic_renode_map := $(binaries_dir)/$(app_name).$(toolchain).map
stm32f0_arithmetic_renode_sections := $(binaries_dir)/$(app_name).$(toolchain).sections
stm32f0_arithmetic_renode_segments := $(binaries_dir)/$(app_name).$(toolchain).segments
stm32f0_arithmetic_renode_symbols := $(binaries_dir)/$(app_name).$(toolchain).symbols

stm32f0_arithmetic_renode_build_dir := $(objects_dir)/$(app_name)/$(toolchain)

# ------------------------------------------------------------------------------
# linking

stm32f0_arithmetic_renode_lds := $(app_dir)/$(app_name).ld

stm32f0_arithmetic_renode_ldflags := $(stm32_ldflags)
# For verbose linking:
# stm32f0_arithmetic_renode_ldflags += --verbose

# ------------------------------------------------------------------------------
# compiling

stm32f0_arithmetic_renode_cflags := $(stm32_cflags)
stm32f0_arithmetic_renode_cxxflags := $(stm32_cxxflags)


stm32f0_arithmetic_renode_cflags += -mfloat-abi=soft
stm32f0_arithmetic_renode_cflags += -mcpu=cortex-m0
stm32f0_arithmetic_renode_cflags += -mthumb
stm32f0_arithmetic_renode_cflags += -march=armv6-m

stm32f0_arithmetic_renode_cxxflags += -mfloat-abi=soft
stm32f0_arithmetic_renode_cxxflags += -mcpu=cortex-m0
stm32f0_arithmetic_renode_cxxflags += -mthumb
stm32f0_arithmetic_renode_cxxflags += -march=armv6-m

# https://github.com/martinribelotta/cortex-m-llvm/blob/master/scripts/cortex-m0.mk
# ARCH_FLAGS := --target=thumbv6m-unknown-none-eabi
# ARCH_FLAGS += -mthumb
# ARCH_FLAGS += -march=armv6m
# ARCH_FLAGS += -mcpu=cortex-m0
# ARCH_FLAGS += -mfloat-abi=soft
# ARCH_FLAGS += -mfpu=none

# --------------------------------------------------------------------------------------------------
#
# Getting additional information from the ELF file
#
DATE_TIME := $(shell date)
DATE_TIME_HEADER := GENERATED $(DATE_TIME)
$(app_name): $(stm32f0_arithmetic_renode_elf) Makefile
	@echo
	$(info INFO: POST-BUILDING `$@`.)

# Disassemble executable sections:
	@echo $(DATE_TIME_HEADER) > $(stm32f0_arithmetic_renode_disasm)
	@$(stm32_toolchain_objdump) -d $(stm32f0_arithmetic_renode_elf) >> $(stm32f0_arithmetic_renode_disasm)
# Create files with segments, sections and symbols:
	@echo $(DATE_TIME_HEADER) > $(stm32f0_arithmetic_renode_segments)
	@$(stm32_toolchain_readelf) --segments $(stm32f0_arithmetic_renode_elf) >> $(stm32f0_arithmetic_renode_segments)

	@echo $(DATE_TIME_HEADER) > $(stm32f0_arithmetic_renode_sections)
	@$(stm32_toolchain_readelf) --sections -g --wide $(stm32f0_arithmetic_renode_elf) >> $(stm32f0_arithmetic_renode_sections)

	@echo $(DATE_TIME_HEADER) > $(stm32f0_arithmetic_renode_symbols)
	@$(stm32_toolchain_readelf) --symbols --wide --demangle $(stm32f0_arithmetic_renode_elf) >> $(stm32f0_arithmetic_renode_symbols)
# Make HEX file:
	@$(stm32_toolchain_objcopy) -O ihex $(stm32f0_arithmetic_renode_elf) $(stm32f0_arithmetic_renode_ihex)
# List contents of ihex file in a human-readable form:
	@$(stm32_toolchain_objdump) --full-contents $(stm32f0_arithmetic_renode_elf) > $(stm32f0_arithmetic_renode_ihex).txt
# Print size:
	@$(stm32_toolchain_size) $(stm32f0_arithmetic_renode_elf)
# Check ELF contents:
	@python3 app/stm32f0-arithmetic-renode/integration-tests/elf_check.py $(stm32f0_arithmetic_renode_elf)

	$(info INFO: BUILDING `$@` DONE.)

#
# Linking
#
$(stm32f0_arithmetic_renode_elf): $(stm32f0_arithmetic_renode_objs) Makefile
	@echo
	$(info INFO: LINKING `$@`.)
	@mkdir -p $(shell dirname $@)

	@$(stm32_toolchain_ld) \
		$(stm32f0_arithmetic_renode_objs) \
		$(foreach D, $(stm32f0_arithmetic_renode_lds), -T$(D)) \
		-Map=$(stm32f0_arithmetic_renode_map) \
		$(stm32f0_arithmetic_renode_ldflags) \
		-L/opt/gcc-arm-none-eabi-10.3-2021.10/lib/gcc/arm-none-eabi/10.3.1/thumb/v6-m/nofp/ \
		-lgcc \
		-o $(stm32f0_arithmetic_renode_elf)

#
# Building C++ source files
#
$(stm32f0_arithmetic_renode_build_dir)/%.cpp.o: %.cpp Makefile
	@echo
	$(info INFO: BUILDING `$@` FROM `$<`.)
	@mkdir -p $(shell dirname $@)
	@$(stm32_toolchain_cpp) \
		$(stm32f0_arithmetic_renode_cxxflags) \
		$(foreach D, $(stm32f0_arithmetic_renode_incs), -I$(D)) \
		-c $< -o $@

#
# Building C source files
#
$(stm32f0_arithmetic_renode_build_dir)/%.c.o: %.c Makefile
	@echo
	$(info INFO: BUILDING `$@` FROM `$<`.)
	@mkdir -p $(shell dirname $@)
	@$(stm32_toolchain_c) \
		$(stm32f0_arithmetic_renode_cflags) \
		$(foreach D, $(stm32f0_arithmetic_renode_incs), -I$(D)) \
		-c $< -o $@

-include $(stm32f0_arithmetic_renode_deps)
