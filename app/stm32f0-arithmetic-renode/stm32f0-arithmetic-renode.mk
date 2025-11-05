# ==============================================================================
# stm32f0-arithmetic-renode.mk
#
# This file is included in the main Makefile.
# ==============================================================================

-include arch/arm/stm32/stm32.mk

app_name := stm32f0-arithmetic-renode
app_dir := ./app/$(app_name)
toolchain := $(EMB1_TOOLCHAIN)

# ------------------------------------------------------------------------------
# include directories

stm32f0_arithmetic_renode_incs := $(stm32_incs)

# ------------------------------------------------------------------------------
# source files

stm32f0_arithmetic_renode_srcs :=
stm32f0_arithmetic_renode_srcs += $(app_dir)/ibasic.cpp
stm32f0_arithmetic_renode_srcs += $(app_dir)/imult.cpp
stm32f0_arithmetic_renode_srcs += $(app_dir)/main.cpp
stm32f0_arithmetic_renode_srcs += $(app_dir)/nvic.cpp
stm32f0_arithmetic_renode_srcs += $(app_dir)/test_ibasic.cpp
stm32f0_arithmetic_renode_srcs += $(app_dir)/test_imult.cpp
stm32f0_arithmetic_renode_srcs += $(app_dir)/test.cpp
stm32f0_arithmetic_renode_srcs += ./arch/arm/armv6_m/stm32f0/stm32f051/startup.cpp

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

stm32f0_arithmetic_renode_ldflags += -L$(stm32_libgcc_dir)/thumb/v6-m/nofp/

# ------------------------------------------------------------------------------
# compiling

stm32f0_arithmetic_renode_cflags := $(stm32_cflags)
stm32f0_arithmetic_renode_cxxflags := $(stm32_cxxflags)

stm32f0_arithmetic_renode_c_cxx_flags :=
stm32f0_arithmetic_renode_c_cxx_flags += -mfloat-abi=soft  # STM32F0 do not have a hardware FPU, so software-based floating-point operations are required.
stm32f0_arithmetic_renode_c_cxx_flags += -mcpu=cortex-m0
stm32f0_arithmetic_renode_c_cxx_flags += -mthumb
stm32f0_arithmetic_renode_c_cxx_flags += -march=armv6-m
stm32f0_arithmetic_renode_c_cxx_flags += -fomit-frame-pointer  # to allow using r7/r11 in inline assembly
# stm32f0_arithmetic_renode_c_cxx_flags += -v  # verbose

ifneq ($(findstring gnu-arm-none-eabi,$(EMB1_TOOLCHAIN)),)
	stm32f0_arithmetic_renode_c_cxx_flags += -specs=nano.specs  # for newlib-nano
	stm32f0_arithmetic_renode_c_cxx_flags += -specs=nosys.specs # optional but recommended for bare-metal, 
	# This links in stubbed versions of system calls (like _sbrk, _write, etc.) that are needed by newlib
	# but are not implemented in a bare-metal environment. This prevents "undefined symbol" errors. 
	# Use libgcc
	stm32f0_arithmetic_renode_ldflags += -lgcc
endif

ifneq ($(findstring llvm,$(EMB1_TOOLCHAIN)),)
# 	stm32f0_arithmetic_renode_ldflags += --nolibc
	stm32f0_arithmetic_renode_ldflags += -lc_nano
	stm32f0_arithmetic_renode_ldflags += -lnosys
# 	stm32f0_arithmetic_renode_ldflags += -lm
# 	stm32f0_arithmetic_renode_c_cxx_flags += -specs=nano.specs  # for newlib-nano
# 	stm32f0_arithmetic_renode_c_cxx_flags += -specs=nosys.specs # optional but recommended for bare-metal, 
	stm32f0_arithmetic_renode_ldflags += -lgcc
endif

stm32f0_arithmetic_renode_cflags += $(stm32f0_arithmetic_renode_c_cxx_flags)
stm32f0_arithmetic_renode_cxxflags += $(stm32f0_arithmetic_renode_c_cxx_flags)

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

$(app_name): $(stm32f0_arithmetic_renode_elf) Makefile
	@echo
	$(info I: POST-BUILDING `$@`.)

# Disassemble executable sections:
	@echo $(DATE_TIME_HEADER) > $(stm32f0_arithmetic_renode_disasm)
	@$(stm32_toolchain_objdump) $(disasm_options) $(stm32f0_arithmetic_renode_elf) >> $(stm32f0_arithmetic_renode_disasm)

# Create files with segments, sections, and symbols:
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
	@python3 app/stm32f0-arithmetic-renode/integration-tests/check_elf.py $(stm32f0_arithmetic_renode_elf)

	$(info I: BUILDING `$@` DONE.)

# --------------------------------------------------------------------------------------------------
#
# Linking
#
$(stm32f0_arithmetic_renode_elf): $(stm32f0_arithmetic_renode_objs) Makefile
	@echo
	$(info I: LINKING `$@`.)
	@mkdir -p $(shell dirname $@)
	$(info D: cxxflags: $(stm32f0_arithmetic_renode_cxxflags))
	$(info D: ldflags: $(stm32f0_arithmetic_renode_ldflags))

# Using the C++ compiler for linking instead of stm32_toolchain_ld.
# Every option must be prepended by -Wl.

# ifneq ($(findstring gnu-arm-none-eabi,$(EMB1_TOOLCHAIN)),)
	@$(stm32_toolchain_cpp_ld) \
		$(stm32f0_arithmetic_renode_objs) \
		$(foreach LinkerScript, $(stm32f0_arithmetic_renode_lds), -Wl,-T$(LinkerScript)) \
		-mthumb \
		-mcpu=cortex-m0 \
		$(foreach LinkerFlag, $(stm32f0_arithmetic_renode_ldflags), -Wl,$(LinkerFlag)) \
		-Wl,-Map=$(stm32f0_arithmetic_renode_map) \
		-o $(stm32f0_arithmetic_renode_elf)
# endif

# ifneq ($(findstring llvm,$(EMB1_TOOLCHAIN)),)
# 	@$(stm32_toolchain_ld) \
# 		$(foreach LinkerScript, $(stm32f0_arithmetic_renode_lds), -T$(LinkerScript)) \
# 		-Map=$(stm32f0_arithmetic_renode_map) \
# 		$(stm32f0_arithmetic_renode_ldflags) \
# 		--verbose \
# 		-o $(stm32f0_arithmetic_renode_elf)
# endif
	$(info I: OK)

# --------------------------------------------------------------------------------------------------
#
# Building C++ source files
#
$(stm32f0_arithmetic_renode_build_dir)/%.cpp.o: %.cpp Makefile
	@echo
	$(info I: BUILDING `$@` FROM `$<`.)
	@mkdir -p $(shell dirname $@)
# 	$(info D: cxxflags: $(stm32f0_arithmetic_renode_cxxflags))

	@$(stm32_toolchain_cpp) \
		$(stm32f0_arithmetic_renode_cxxflags) \
		$(foreach D, $(stm32f0_arithmetic_renode_incs), -I$(D)) \
		-c $< -o $@

	@$(stm32_toolchain_objdump) $(disasm_options) $@ > $@.disasm

	$(info I: OK)

# --------------------------------------------------------------------------------------------------
#
# Building C source files
#
$(stm32f0_arithmetic_renode_build_dir)/%.c.o: %.c Makefile
	@echo
	$(info I: BUILDING `$@` FROM `$<`.)
	@mkdir -p $(shell dirname $@)
	@$(stm32_toolchain_c) \
		$(stm32f0_arithmetic_renode_cflags) \
		$(foreach D, $(stm32f0_arithmetic_renode_incs), -I$(D)) \
		-c $< -o $@

-include $(stm32f0_arithmetic_renode_deps)
