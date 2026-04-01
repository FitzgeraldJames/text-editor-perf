cmake_minimum_required(VERSION 3.20)
project(TextEditorBench CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Release build for benchmarks
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Fetch dependencies
include(FetchContent)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.8.3
)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)

set(BENCHMARK_ENABLE_TESTING OFF)
FetchContent_MakeAvailable(googlebenchmark googletest)

# Implementation library
add_library(editor_impls
  src/implementations/naive_array.cpp
)
target_include_directories(editor_impls PUBLIC include src src/implementations)

# Benchmark executable
add_executable(benchmarks
  benchmarks/bench_main.cpp
  benchmarks/bench_insert.cpp
)
target_link_libraries(benchmarks PRIVATE editor_impls benchmark::benchmark)

# Test executable
add_executable(tests tests/correctness_tests.cpp)
target_link_libraries(tests PRIVATE editor_impls GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
