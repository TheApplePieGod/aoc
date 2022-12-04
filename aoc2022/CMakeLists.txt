cmake_minimum_required(VERSION 3.12)

project(AOC)

add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)

#file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp" "*.h")
add_executable(AOC "Base.h" "Utils.h" "Utils.cpp" "Timer.h" "Day5/Part1.cpp")
target_include_directories(
    AOC
    PUBLIC
    "."
)

target_compile_features(AOC PUBLIC cxx_std_17)