cmake_minimum_required(VERSION 3.28)

project(AdventOfCode2025 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(AdventOfCode2025
    src/main.cpp
)

target_include_directories(AdventOfCode2025 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)