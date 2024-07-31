
ifeq ($(EMB1_TOOLCHAIN),llvm)
	stm32_toolchain_cpp:=clang++
	stm32_toolchain_c:=clang
	stm32_toolchain_objdump := llvm-objdump-14
	stm32_toolchain_readelf := llvm-readelf-14
	stm32_toolchain_objcopy := llvm-objcopy-14
	stm32_toolchain_size := llvm-size-14
# 	stm32_toolchain_ld := ld.lld-14
	stm32_toolchain_ld := arm-none-eabi-10.3-ld
else
	stm32_toolchain_cpp:=arm-none-eabi-10.3-g++
	stm32_toolchain_c:=arm-none-eabi-10.3-gcc
	stm32_toolchain_objdump := arm-none-eabi-10.3-objdump
	stm32_toolchain_readelf := arm-none-eabi-10.3-readelf
	stm32_toolchain_objcopy := arm-none-eabi-10.3-objcopy
	stm32_toolchain_size := arm-none-eabi-10.3-size
	stm32_toolchain_ld := arm-none-eabi-10.3-ld
endif



stm32_incs = ./

stm32_cflags := $(common_cflags)
stm32_cxxflags := $(common_cxxflags)
stm32_ldflags := $(common_ldflags)

ifeq ($(EMB1_TOOLCHAIN),gnu)

	stm32_cflags += -fcallgraph-info
	stm32_cflags += -fdump-rtl-expand

	stm32_cxxflags += -fcallgraph-info
	stm32_cxxflags += -fdump-rtl-expand

else ifeq ($(EMB1_TOOLCHAIN),llvm)
	stm32_cflags += --target=arm-none-eabi
	stm32_cxxflags += --target=arm-none-eabi

	stm32_cflags += --sysroot=/opt/gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi
	stm32_cxxflags += --sysroot=/opt/gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi

	# This is needed because <cstdint> uses <bits/c++config.h>:
	stm32_incs += /opt/gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi/include/c++/10.3.1/arm-none-eabi
endif

stm32_cflags += -fstack-usage
stm32_cflags += -nostdlib
stm32_cflags += -fno-exceptions
stm32_cflags += -ffreestanding
stm32_cflags += -ggdb -g3

stm32_cxxflags += -fstack-usage
stm32_cxxflags += -nostdlib
stm32_cxxflags += -fno-exceptions
stm32_cxxflags += -ffreestanding
stm32_cxxflags += -fno-rtti
stm32_cxxflags += -ggdb -g3
stm32_cxxflags += -ffunction-sections
stm32_cxxflags += -fdata-sections


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
