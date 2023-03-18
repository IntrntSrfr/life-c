cmake_minimum_required(VERSION 3.22)
project(life-c C)

#[[
# use if profiling
set(CMAKE_C_STANDARD 17 -Wall -Wextra -pg)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
]]

set(SOURCES main.c grid.c game.c)
set(GIF_SOURCES ${PROJECT_SOURCE_DIR}/../libs/gifenc/gifenc.c)

add_executable(life-c ${SOURCES} ${GIF_SOURCES})
target_include_directories(life-c PRIVATE ${PROJECT_SOURCE_DIR}/../libs/gifenc)
