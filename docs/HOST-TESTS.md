# Overview

Host tests use the **googletest** framework.

***
# Writing host tests

TBD

***
# Running host tests

`$ bin/host-tests.gnu.out` runs all tests.

`$ bin/host-tests.gnu.out --gtest_list_tests` lists all tests.

Running individual tests:
`$ bin/host-tests.gnu.out --gtest_filter=DioTests.*`
`$ bin/host-tests.gnu.out --gtest_filter=X/ProtocolParserTestsProgMemory.Basic/1`

Making and running tests:
`$ make host-tests-run`
`$ make host-tests-run ARGS="--gtest_list_tests"`
`$ make host-tests-run ARGS="--gtest_filter=DioTests.*"`
`$ make host-tests-run ARGS="--gtest_filter=X/ProtocolParserTestsProgMemory.Basic/*"`

***
# Host tests internals

Build steps:
1. Build `libgtest.gnu.a` or `libgtest.llvm.a` and copy it to `obj/host-tests`.
2. Recompile `host-tests/main.cpp` so that the binary can report the build time.
3. Compile individual test modules.
4. Link everything above into `bin/host-tests.gnu.out` or `bin/host-tests.llvm.out`.

***
