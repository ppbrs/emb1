# ==============================================================================
# stm32h7-arithmetic-renode.mk
#
# This file is included in the main Makefile.
# ==============================================================================

-include arch/arm/stm32/stm32.mk

app_name := stm32h7-arithmetic-renode
app_dir := ./app/$(app_name)
toolchain := $(EMB1_TOOLCHAIN)

# ------------------------------------------------------------------------------
# include directories

stm32h7_arithmetic_renode_incs := $(stm32_incs)

# ------------------------------------------------------------------------------
# source files

stm32h7_arithmetic_renode_srcs :=
# stm32h7_arithmetic_renode_srcs += $(app_dir)/ibasic.cpp
# stm32h7_arithmetic_renode_srcs += $(app_dir)/imult.cpp
stm32h7_arithmetic_renode_srcs += $(app_dir)/main.cpp
stm32h7_arithmetic_renode_srcs += $(app_dir)/nvic.cpp
# stm32h7_arithmetic_renode_srcs += $(app_dir)/test_ibasic.cpp
# stm32h7_arithmetic_renode_srcs += $(app_dir)/test_imult.cpp
# stm32h7_arithmetic_renode_srcs += $(app_dir)/test.cpp
stm32h7_arithmetic_renode_srcs += ./arch/arm/armv7e_m/stm32h7/stm32h743/startup.cpp
stm32h7_arithmetic_renode_srcs += $(stm32h743_srcs)

stm32h7_arithmetic_renode_objs =  $(patsubst %.c,   $(stm32h7_arithmetic_renode_build_dir)/%.c.o,   $(filter %.c,   $(stm32h7_arithmetic_renode_srcs)))
stm32h7_arithmetic_renode_objs += $(patsubst %.cpp, $(stm32h7_arithmetic_renode_build_dir)/%.cpp.o, $(filter %.cpp, $(stm32h7_arithmetic_renode_srcs)))
stm32h7_arithmetic_renode_deps := $(stm32h7_arithmetic_renode_objs:.o=.d)

# ------------------------------------------------------------------------------
# outputs

stm32h7_arithmetic_renode_elf := $(binaries_dir)/$(app_name).$(toolchain).elf
stm32h7_arithmetic_renode_disasm := $(binaries_dir)/$(app_name).$(toolchain).disasm
stm32h7_arithmetic_renode_ihex := $(binaries_dir)/$(app_name).$(toolchain).ihex
stm32h7_arithmetic_renode_map := $(binaries_dir)/$(app_name).$(toolchain).map
stm32h7_arithmetic_renode_sections := $(binaries_dir)/$(app_name).$(toolchain).sections
stm32h7_arithmetic_renode_segments := $(binaries_dir)/$(app_name).$(toolchain).segments
stm32h7_arithmetic_renode_symbols := $(binaries_dir)/$(app_name).$(toolchain).symbols

stm32h7_arithmetic_renode_build_dir := $(objects_dir)/$(app_name)/$(toolchain)

# ------------------------------------------------------------------------------
# linking

stm32h7_arithmetic_renode_lds := $(app_dir)/$(app_name).ld

stm32h7_arithmetic_renode_ldflags := $(stm32_ldflags)
# For verbose linking:
# stm32h7_arithmetic_renode_ldflags += --verbose

# stm32h7_arithmetic_renode_ldflags += -L$(stm32_libgcc_dir)/thumb/v7e-m+fp/hard/

# ------------------------------------------------------------------------------
# compiling

stm32h7_arithmetic_renode_cflags := $(stm32_cflags)
stm32h7_arithmetic_renode_cxxflags := $(stm32_cxxflags)

stm32h7_arithmetic_renode_c_cxx_flags :=
stm32h7_arithmetic_renode_c_cxx_flags += -mfloat-abi=hard
stm32h7_arithmetic_renode_c_cxx_flags += -mfpu=fpv5-d16
stm32h7_arithmetic_renode_c_cxx_flags += -mcpu=cortex-m7
stm32h7_arithmetic_renode_c_cxx_flags += -mthumb
stm32h7_arithmetic_renode_c_cxx_flags += -march=armv7e-m
# stm32h7_arithmetic_renode_c_cxx_flags += -flto=jobserver -flto-partition=one
# stm32h7_arithmetic_renode_c_cxx_flags += -fomit-frame-pointer  # to allow using r7/r11 in inline assembly
# stm32h7_arithmetic_renode_c_cxx_flags += -v  # verbose
stm32h7_arithmetic_renode_c_cxx_flags += -ffreestanding  # Note: This defines __STDC_HOSTED__ > 0


ifneq ($(findstring gnu-arm-none-eabi,$(EMB1_TOOLCHAIN)),)
# 	stm32h7_arithmetic_renode_c_cxx_flags += -specs=nano.specs  # for newlib-nano
# 	stm32h7_arithmetic_renode_c_cxx_flags += -specs=nosys.specs # optional but recommended for bare-metal, 
# 	# This links in stubbed versions of system calls (like _sbrk, _write, etc.) that are needed by newlib
# 	# but are not implemented in a bare-metal environment. This prevents "undefined symbol" errors. 
# 	# Use libgcc
# 	stm32h7_arithmetic_renode_ldflags += -lgcc
endif

stm32h7_arithmetic_renode_cflags += $(stm32h7_arithmetic_renode_c_cxx_flags)
stm32h7_arithmetic_renode_cxxflags += $(stm32h7_arithmetic_renode_c_cxx_flags)

# --------------------------------------------------------------------------------------------------
#
# Getting additional information from the ELF file
#
DATE_TIME := $(shell date)
DATE_TIME_HEADER := GENERATED $(DATE_TIME)

disasm_options := --disassemble
disasm_options += --disassemble
disasm_options += --demangle
disasm_options += --wide  # no wrapping
disasm_options += --line-numbers
disasm_options += --source
disasm_options += -x
disasm_options += -M reg-names-std
# disasm_options += -M reg-names-apcs  # to show registers as a1-a4, v1-v6, ...

$(app_name): $(stm32h7_arithmetic_renode_elf) Makefile
	@echo
	$(info I: POST-BUILDING `$@`.)

# Disassemble executable sections:
	@echo $(DATE_TIME_HEADER) > $(stm32h7_arithmetic_renode_disasm)
	@$(stm32_toolchain_objdump) $(disasm_options) $(stm32h7_arithmetic_renode_elf) >> $(stm32h7_arithmetic_renode_disasm)

# Create files with segments, sections, and symbols:
	@echo $(DATE_TIME_HEADER) > $(stm32h7_arithmetic_renode_segments)
	@$(stm32_toolchain_readelf) --segments $(stm32h7_arithmetic_renode_elf) >> $(stm32h7_arithmetic_renode_segments)

	@echo $(DATE_TIME_HEADER) > $(stm32h7_arithmetic_renode_sections)
	@$(stm32_toolchain_readelf) --sections -g --wide $(stm32h7_arithmetic_renode_elf) >> $(stm32h7_arithmetic_renode_sections)

	@echo $(DATE_TIME_HEADER) > $(stm32h7_arithmetic_renode_symbols)
	@$(stm32_toolchain_readelf) --symbols --wide --demangle $(stm32h7_arithmetic_renode_elf) >> $(stm32h7_arithmetic_renode_symbols)

# Make HEX file:
	@$(stm32_toolchain_objcopy) -O ihex $(stm32h7_arithmetic_renode_elf) $(stm32h7_arithmetic_renode_ihex)

# List contents of ihex file in a human-readable form:
	@$(stm32_toolchain_objdump) --full-contents $(stm32h7_arithmetic_renode_elf) > $(stm32h7_arithmetic_renode_ihex).txt

# Print size:
	@$(stm32_toolchain_size) $(stm32h7_arithmetic_renode_elf)

# Check ELF contents:
# 	@python3 app/stm32f0-arithmetic-renode/integration-tests/check_elf.py $(stm32h7_arithmetic_renode_elf)

	$(info I: BUILDING `$@` DONE.)

# --------------------------------------------------------------------------------------------------
#
# Linking
#
$(stm32h7_arithmetic_renode_elf): $(stm32h7_arithmetic_renode_objs) Makefile
	@echo
	$(info I: LINKING `$@`.)
	@mkdir -p $(shell dirname $@)
	$(info D: cxxflags: $(stm32h7_arithmetic_renode_cxxflags))
	$(info D: ldflags: $(stm32h7_arithmetic_renode_ldflags))

# Using the C++ compiler for linking instead of stm32_toolchain_ld.
# Every option in stm32h7_arithmetic_renode_ldflags must be prepended by -Wl.

	@$(stm32_toolchain_cpp_ld) \
		$(stm32h7_arithmetic_renode_objs) \
		$(foreach LinkerScript, $(stm32h7_arithmetic_renode_lds), -Wl,-T$(LinkerScript)) \
		-mthumb \
		-ffreestanding \
		-mcpu=cortex-m7 \
		-mfloat-abi=hard \
		-mfpu=fpv5-d16 \
		-Wl,-Map=$(stm32h7_arithmetic_renode_map) \
		$(foreach LinkerFlag, $(stm32h7_arithmetic_renode_ldflags), -Wl,$(LinkerFlag)) \
		-o $(stm32h7_arithmetic_renode_elf)

	$(info I: OK)

# --------------------------------------------------------------------------------------------------
#
# Building C++ source files
#
$(stm32h7_arithmetic_renode_build_dir)/%.cpp.o: %.cpp Makefile
	@echo
	$(info I: BUILDING `$@` FROM `$<`.)
	@mkdir -p $(shell dirname $@)
	$(info D: cxxflags: $(stm32h7_arithmetic_renode_cxxflags))

	@$(stm32_toolchain_cpp) \
		$(stm32h7_arithmetic_renode_cxxflags) \
		$(foreach D, $(stm32h7_arithmetic_renode_incs), -I$(D)) \
		-c $< -o $@

	@$(stm32_toolchain_objdump) $(disasm_options) $@ > $@.disasm

	$(info I: OK)

# --------------------------------------------------------------------------------------------------
#
# Building C source files
#
$(stm32h7_arithmetic_renode_build_dir)/%.c.o: %.c Makefile
	@echo
	$(info I: BUILDING `$@` FROM `$<`.)
	@mkdir -p $(shell dirname $@)
	$(info D: cflags: $(stm32h7_arithmetic_renode_cflags))

	@$(stm32_toolchain_c) \
		$(stm32h7_arithmetic_renode_cflags) \
		$(foreach D, $(stm32h7_arithmetic_renode_incs), -I$(D)) \
		-c $< -o $@

	$(info I: OK)

-include $(stm32h7_arithmetic_renode_deps)
