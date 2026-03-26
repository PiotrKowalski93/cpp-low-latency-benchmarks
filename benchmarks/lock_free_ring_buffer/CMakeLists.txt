cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lock_free_ring_buffer LANGUAGES CXX)

add_executable (lock_free_ring_buffer 
    queue.cpp
    program.cpp
)

target_link_libraries(lock_free_ring_buffer
    PRIVATE
        libcommon
)