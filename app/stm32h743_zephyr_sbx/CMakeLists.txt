# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(z_h743_prj00)

target_include_directories(app PRIVATE ../../)

target_sources(
	app PRIVATE
	src/main.cpp
	src/error.cpp
	src/protocol.cpp
)
