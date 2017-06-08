# calc-test

cmake_minimum_required(VERSION 2.8.12)
project(calc-test CXX)

add_compile_options(-Wall -std=c++11)

include_directories(../)
set(SOURCE_LIB ../libs.cpp)

################################
# GTest
################################
add_subdirectory (gtest-1.8.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

################################
# Unit Tests
################################
# Add test cpp file
add_executable( runUnitTests UnitTests.cpp ${SOURCE_LIB})

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main)
add_test( runUnitTests runUnitTests )
