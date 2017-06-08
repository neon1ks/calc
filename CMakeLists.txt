# calc
cmake_minimum_required(VERSION 2.8.12)

project(calc CXX)
add_compile_options(-Wall -std=c++11)

set(SOURCE main.cpp
           libs.cpp)

add_executable(calc ${SOURCE})

add_subdirectory (test)

