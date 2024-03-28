# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(stm32h743_zephyr_sbx)

target_include_directories(app PRIVATE ../../)

target_sources(
	app PRIVATE
	../../arch/arm/armv7e_m/stm32h7/stm32h743/memory.cpp
	../../common/protocol/option.cpp
	../../common/protocol/parser.cpp
	../../common/protocol/prog.cpp
	src/error.cpp
	src/main.cpp
	src/protocol.cpp
)
