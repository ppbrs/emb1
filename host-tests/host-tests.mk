#
# toolchain-specific settings:
#
ifeq ($(EMB1_TOOLCHAIN),llvm)
	host_toolchain_c := clang-14
	host_toolchain_cpp := clang++-14
	host_tests_out := $(binaries_dir)/host-tests.llvm.out
	lib_gtest_stem := gtest.llvm
	host_tests_objs_dir := ./obj/host-tests.llvm
else
	host_toolchain_c := gcc-12
	host_toolchain_cpp := g++-12
	host_tests_out := $(binaries_dir)/host-tests.gnu.out
	lib_gtest_stem := gtest.gnu
	host_tests_objs_dir := ./obj/host-tests.gnu
endif

gtest_dir := $(realpath ./3party/googletest)
gtest_temp_dir := $(temp_dir)/gtest
host_tests_bin_dir := $(binaries_dir)/host-tests

host_tests_srcs =
host_tests_srcs += arch/arm/stm32/dio.cpp
host_tests_srcs += arch/arm/stm32/mmreg/gpio-mock.cpp
host_tests_srcs += common/memory/stack-allocator-tests.cpp
host_tests_srcs += common/protocol/process-tests.cpp
host_tests_srcs += common/protocol/process.cpp
host_tests_srcs += host-tests/error.cpp
host_tests_srcs += if/mcu/dio-tests.cpp
host_tests_srcs += if/mcu/mmreg-tests.cpp

host_tests_objs = $(patsubst %.cpp,   $(host_tests_objs_dir)/%.cpp.o, $(filter %.cpp, $(host_tests_srcs)))
host_tests_objs +=  $(patsubst %.c,   $(host_tests_objs_dir)/%.c.o,   $(filter %.c,   $(host_tests_srcs)))
host_tests_deps = $(host_tests_objs:.o=.d)

host_tests_incl_dirs := ./
host_tests_incl_dirs += $(gtest_dir)/googletest/include

lib_gtest_path := $(host_tests_objs_dir)/lib$(lib_gtest_stem).a

host-tests-run: host-tests
	@echo
	$(info INFO: BUILDING `$@`.)
	$(host_tests_out)

host-tests: $(host_tests_out)
	@echo
	$(info INFO: BUILDING `$@`.)

$(host_tests_out): host_tests_main $(lib_gtest_path) $(host_tests_objs) Makefile
	@mkdir -p $(binaries_dir)
	@$(host_toolchain_cpp) \
		$(common_cxxflags) \
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
		$(common_cxxflags) \
		$(foreach D, $(host_tests_incl_dirs), -I$(D)) \
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
		$(common_cxxflags) \
		-MD \
		$(foreach D, $(host_tests_incl_dirs), -I$(D)) \
		-c $< -o $@

-include $(host_tests_deps)
