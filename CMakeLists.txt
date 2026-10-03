cmake_minimum_required(VERSION 3.16)
project(CrossSectionEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /O2 /arch:AVX2)
else()
    add_compile_options(-Wall -Wextra -O3 -march=native)
endif()

include_directories(include)

add_executable(cross_section_engine
    src/SearchEngine.cpp
    src/main.cpp
)