#
# toolchain-specific settings:
#
ifeq ($(EMB1_TOOLCHAIN),llvm)
	host_toolchain_c := clang-14
	host_toolchain_cpp := clang++-14
	toolchain := $(EMB1_TOOLCHAIN)
else
	host_toolchain_c := gcc-12
	host_toolchain_cpp := g++-12
endif

host_tests_out := $(binaries_dir)/host-tests.$(toolchain).out
host_tests_objs_dir := ./obj/host-tests/$(toolchain)
lib_gtest_stem := gtest

gtest_dir := $(realpath ./3party/googletest)
gtest_temp_dir := $(temp_dir)/gtest/$(toolchain)
host_tests_bin_dir := $(binaries_dir)/host-tests

host_tests_srcs =
host_tests_srcs += arch/arm/stm32/dio.cpp
host_tests_srcs += arch/arm/stm32/mmreg/gpio-mock.cpp
host_tests_srcs += common/io/char-stream.cpp
host_tests_srcs += common/io/char-stream-tests.cpp
host_tests_srcs += common/memory/stack-allocator-tests.cpp
host_tests_srcs += common/protocol/option.cpp
host_tests_srcs += common/protocol/option-tests.cpp
host_tests_srcs += common/protocol/parser-tests.cpp
host_tests_srcs += common/protocol/parser.cpp
host_tests_srcs += common/protocol/prog.cpp
host_tests_srcs += common/protocol/splitter-tests.cpp
host_tests_srcs += host-tests/error.cpp
host_tests_srcs += if/mcu/dio-tests.cpp
host_tests_srcs += if/mcu/mmreg-tests.cpp

host_tests_objs = $(patsubst %.cpp,   $(host_tests_objs_dir)/%.cpp.o, $(filter %.cpp, $(host_tests_srcs)))
host_tests_objs +=  $(patsubst %.c,   $(host_tests_objs_dir)/%.c.o,   $(filter %.c,   $(host_tests_srcs)))
host_tests_deps = $(host_tests_objs:.o=.d)

host_tests_incs := ./
host_tests_incs += $(gtest_dir)/googletest/include

host_tests_cxxflags := $(common_cxxflags)
host_tests_cxxflags += -fstack-protector-strong

lib_gtest_path := $(host_tests_objs_dir)/lib$(lib_gtest_stem).a

host-tests-run: host-tests
	@echo
	$(info INFO: RUNNING `$(host_tests_out)` with arguments `$(ARGS)`.)
	$(host_tests_out) $(ARGS)

host-tests: $(host_tests_out)
	@echo
	$(info INFO: BUILDING `$@`.)

$(host_tests_out): host_tests_main $(lib_gtest_path) $(host_tests_objs) Makefile
	@mkdir -p $(binaries_dir)
	@$(host_toolchain_cpp) \
		$(host_tests_cxxflags) \
		-L$(host_tests_objs_dir) \
		$(host_tests_objs) \
		$(host_tests_objs_dir)/host-tests/main.o \
		-l$(lib_gtest_stem) \
		-o $(host_tests_out)

# Always rebuild main so that the build date and time and the build system version
# are always up to date.
.PHONY: host_tests_main
host_tests_main:
	@echo
	$(info INFO: BUILDING `host_tests_main` FROM `host-tests/main.cpp`.)
	@mkdir -p $(shell dirname $(host_tests_objs_dir)/host-tests/main.o)
	@$(host_toolchain_cpp) \
		$(host_tests_cxxflags) \
		$(foreach D, $(host_tests_incs), -I$(D)) \
		-c host-tests/main.cpp \
		-o $(host_tests_objs_dir)/host-tests/main.o


$(lib_gtest_path):
	@echo
	$(info INFO: BUILDING `$@`.)
	@mkdir -p $(gtest_temp_dir); \
		cd $(gtest_temp_dir) && \
		export CC=$(host_toolchain_c) CXX=$(host_toolchain_cpp) && \
		cmake $(gtest_dir) && \
		cmake --build . --target gtest

	$(info INFO: COPYING `$(gtest_temp_dir)/lib/libgtest.a` to `$(lib_gtest_path)`.)
	@mkdir -p $(host_tests_objs_dir)
	@cp $(gtest_temp_dir)/lib/libgtest.a $(lib_gtest_path)

$(host_tests_objs_dir)/%.cpp.o: %.cpp Makefile
	@echo
	$(info INFO: BUILDING `$@` FROM `$<`.)
	@mkdir -p $(shell dirname $@)
	@$(host_toolchain_cpp) \
		$(host_tests_cxxflags) \
		-MD \
		$(foreach D, $(host_tests_incs), -I$(D)) \
		-c $< -o $@

-include $(host_tests_deps)
