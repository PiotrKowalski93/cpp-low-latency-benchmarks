cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(common)
add_subdirectory(benchmarks/lock_free_ring_buffer)
add_subdirectory(benchmarks/cpu_affinity)