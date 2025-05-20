cmake_minimum_required(VERSION 3.20)

project(imageproc VERSION 1.0 LANGUAGES CXX)

add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wpedantic
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(contrib)
