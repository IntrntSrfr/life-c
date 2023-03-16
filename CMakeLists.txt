cmake_minimum_required(VERSION 3.22)
project(life-c)

set(CMAKE_C_STANDARD 11 -Wall -Wextra -pg)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
add_executable(life-c main.c grid.c game.c)
target_link_libraries(life-c m)
