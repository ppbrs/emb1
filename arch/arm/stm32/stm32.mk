# ==================================================================================================
# stm32.mk
#
# This file is included at the beginning of individual project makefiles,
# e.g. stm32f0-arithmetic-renode.mk
# ==================================================================================================

# Note: common_cflags, common_cxxflags, common_ldflags are defined in Makefile.
stm32_incs := ./
stm32_cflags := $(common_cflags)
stm32_cxxflags := $(common_cxxflags)
stm32_ldflags := $(common_ldflags)


# --------------------------------------------------------------------------------------------------
# LLVM

ifeq ($(EMB1_TOOLCHAIN),llvm-18)

# 	stm32_toolchain_root_dir := 
	stm32_toolchain_cpp := /usr/bin/clang++-18
	stm32_toolchain_c := /usr/bin/clang-18
	stm32_toolchain_objdump := /usr/bin/llvm-objdump-18
	stm32_toolchain_readelf := /usr/bin/llvm-readelf-18
	stm32_toolchain_objcopy := /usr/bin/llvm-objcopy-18
	stm32_toolchain_size := /usr/bin/llvm-size-18

# Clang is often a "bare" compiler without a built-in C library.
# We need usually borrow it from the GNU Arm Toolchain.
	stm32_toolchain_gnu_root_dir := ../emb1-tools-infra/toolchains/gnu-arm-none-eabi-14.3/

	stm32_libgcc_dir = $(stm32_toolchain_gnu_root_dir)/lib/gcc/arm-none-eabi/14.3.1/

	stm32_c_cxx_flags := --target=arm-none-eabi

#	How to find my GNU sysroot?
#	$ ./arm-none-eabi-c++ -print-sysroot
#		emb1-tools-infra/toolchains/gnu-arm-none-eabi-14.3/bin/../arm-none-eabi
	stm32_c_cxx_flags += --sysroot=$(stm32_toolchain_gnu_root_dir)/arm-none-eabi/

	stm32_incs += $(stm32_toolchain_gnu_root_dir)/arm-none-eabi/include/c++/14.3.1
#	The following is needed because <cstdint> (residing in the directory above)
#	uses <bits/c++config.h>:
	stm32_incs += $(stm32_toolchain_gnu_root_dir)/arm-none-eabi/include/c++/14.3.1/arm-none-eabi

	stm32_cflags += $(stm32_c_cxx_flags)
	stm32_cxxflags += $(stm32_c_cxx_flags)

# Linking with GCC 14.3:
	stm32_toolchain_cpp_ld := $(stm32_toolchain_gnu_root_dir)/bin/arm-none-eabi-g++

# 	stm32_cxxflags += -fuse-ld=lld
# 	stm32_toolchain_ld := /usr/bin/ld.lld-18
# 	stm32_toolchain_ld := arm-none-eabi-14.3-ld

endif
# --------------------------------------------------------------------------------------------------
# GNU

ifeq ($(EMB1_TOOLCHAIN),gnu-arm-none-eabi-10.3)
	stm32_toolchain_root_dir := ../emb1-tools-infra/toolchains/gnu-arm-none-eabi-10.3
	stm32_toolchain_cpp := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-g++
	stm32_toolchain_cpp_ld := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-g++
	stm32_toolchain_c := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-gcc
	stm32_toolchain_objdump := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-objdump
	stm32_toolchain_readelf := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-readelf
	stm32_toolchain_objcopy := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-objcopy
	stm32_toolchain_size := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-size
	stm32_toolchain_ld := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-ld
	stm32_libgcc_dir = $(stm32_toolchain_root_dir)/lib/gcc/arm-none-eabi/10.3.1
endif

ifeq ($(EMB1_TOOLCHAIN),gnu-arm-none-eabi-14.3)
	stm32_toolchain_root_dir := ../emb1-tools-infra/toolchains/gnu-arm-none-eabi-14.3
	stm32_toolchain_cpp := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-g++
	stm32_toolchain_cpp_ld := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-g++
	stm32_toolchain_c := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-gcc
	stm32_toolchain_objdump := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-objdump
	stm32_toolchain_readelf := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-readelf
	stm32_toolchain_objcopy := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-objcopy
	stm32_toolchain_size := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-size
	stm32_toolchain_ld := $(stm32_toolchain_root_dir)/bin/arm-none-eabi-ld
	stm32_libgcc_dir = $(stm32_toolchain_root_dir)/lib/gcc/arm-none-eabi/14.3.1
endif

# TODO: fix this generic gnu
ifeq ($(EMB1_TOOLCHAIN),gnu)
# use $(findstring find,in)
	stm32_cflags += -fcallgraph-info
	stm32_cflags += -fdump-rtl-expand

	stm32_cxxflags += -fcallgraph-info
	stm32_cxxflags += -fdump-rtl-expand
endif
# --------------------------------------------------------------------------------------------------

stm32_cflags += -mabi=aapcs
stm32_cflags += -fstack-usage
stm32_cflags += -nostdlib
stm32_cflags += -fno-exceptions
stm32_cflags += -ggdb -g3
stm32_cflags += -ffunction-sections  # Instructs the compiler to place each function into its own linker section.
stm32_cflags += -fdata-sections  # Instructs the compiler to place each data variable into its own linker section.

stm32_cxxflags += -mabi=aapcs  # Use ARM Procedure Call Standard (AAPCS)
stm32_cxxflags += -fstack-usage
stm32_cxxflags += -nostdlib
stm32_cxxflags += -fno-exceptions
stm32_cxxflags += -fno-rtti
stm32_cxxflags += -ggdb -g3
stm32_cxxflags += -ffunction-sections  # Instructs the compiler to place each function into its own linker section.
stm32_cxxflags += -fdata-sections  # Instructs the compiler to place each data variable into its own linker section.


# TODO: check https://blog.aureliocolosimo.it/posts/stm32-bare-metal-made-easy
#  arm-none-eabi-gcc -c -mthumb -Wall -Werror -Os -mcpu=cortex-m0 -ggdb -nodefaultlibs -nostdlib -nostartfiles -ffreestanding -Iinclude -o init.o init.c
#  arm-none-eabi-gcc -c -mthumb -Wall -Werror -Os -mcpu=cortex-m0 -ggdb -nodefaultlibs -nostdlib -nostartfiles -ffreestanding -Iinclude -o kprint.o kprint.c
#  arm-none-eabi-gcc -c -mthumb -Wall -Werror -Os -mcpu=cortex-m0 -ggdb -nodefaultlibs -nostdlib -nostartfiles -ffreestanding -Iinclude -o main.o main.c
#  arm-none-eabi-ld init.o kprint.o main.o -Tstm32f4xx.ld -o stm32f0-demo.elf
#  arm-none-eabi-objcopy -O binary stm32f0-demo.elf stm32f0-demo.bin

# common_allflags := -O3 -ggdb -g3 -Werror -Wno-error=deprecated-declarations -Wall -Wextra -Wformat=2 -Wno-format-nonliteral -Wconversion -Wmissing-declarations -Wpointer-arith -Wsign-compare -Wundef -Wduplicated-branches -Wduplicated-cond -Wshadow=local -fno-common -fno-math-errno -fstrict-aliasing -ftabstop=4 $(debug_allflags) $(segger_rtt_allflags) -freorder-blocks-algorithm=simple
# common_cflags := -std=c2x -Wmissing-prototypes
# common_cxxflags := -std=c++2a -Wold-style-cast -Wsuggest-override -Wuseless-cast -Wzero-as-null-pointer-constant -fconcepts
# common_ldflags := -std=c++2a
# arm_allflags := -nostdlib -mabi=aapcs -fno-exceptions -ffreestanding -Wdouble-promotion -mslow-flash-data -flto=jobserver -flto-partition=one -fvisibility=hidden

# -O3 -ggdb -g3 -Werror -Wno-error=deprecated-declarations -Wall -Wextra -Wformat=2 -Wno-format-nonliteral -Wconversion -Wmissing-declarations -Wpointer-arith -Wsign-compare -Wundef -Wduplicated-branches -Wduplicated-cond -Wshadow=local -fno-common -fno-math-errno -fstrict-aliasing -ftabstop=4 -DDEBUG_ENABLED -freorder-blocks-algorithm=simple -std=c++2a -Wold-style-cast -Wsuggest-override -Wuseless-cast -Wzero-as-null-pointer-constant -fconcepts -DMULTICORE=1 -fpic -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=2 -fno-sanitize-recover=all -DMULTIPLE_MOTION_AXES -fsanitize=undefined -DPLATFORM_NAME=hut -DPLATFORM_REV=0 -Wno-conversion -Wno-useless-cast -isystem /usr/include/mit-krb5 -I/usr/include/pgm-5.3 -I/usr/include/libxml2

# stm32_ldflags
# 		-error-limit=0 \
# 		--verbose \
# 		--enable-non-contiguous-regions \
