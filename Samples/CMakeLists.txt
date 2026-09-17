cmake_minimum_required(VERSION 3.20)

project(MatrixSIMD LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------------------------------
# Main app
# --------------------------------------------------

add_executable(matrix_simd
    src/main.cpp
    src/matrix.cpp
    SIMD/dot_product.cpp
)

target_include_directories(matrix_simd PRIVATE
    src
    SIMD
)

target_compile_options(matrix_simd PRIVATE
    -O3
    -mavx2
)

# --------------------------------------------------
# GOOGLE Benchmark
# --------------------------------------------------
include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.4
)

FetchContent_MakeAvailable(googlebenchmark)

# --------------------------------------------------
# Benchmarks
# --------------------------------------------------
add_executable(dot_product_benchmark
    benchmarks/dot_product_benchmark.cpp
    SIMD/dot_product.cpp
)

target_include_directories(dot_product_benchmark PRIVATE
    SIMD
)

target_link_libraries(dot_product_benchmark PRIVATE
    benchmark::benchmark
)

target_compile_options(dot_product_benchmark PRIVATE
    -O3
    -mavx2
)