cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cpu_affinity LANGUAGES CXX)
project(queues LANGUAGES CXX)

add_executable (cpu_affinity 
    benchmarks/cpu_affinity/main.cpp
)

add_executable (queues 
    benchmarks/lock_free_ring_buffer/queue.cpp
    benchmarks/lock_free_ring_buffer/program.cpp
)

add_subdirectory(common)

target_link_libraries(cpu_affinity
    PRIVATE
        libcommon
)

target_link_libraries(queues
    PRIVATE
        libcommon
)