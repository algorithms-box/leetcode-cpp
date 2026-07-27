cmake_minimum_required(VERSION 3.20)
project(ValidParentheses LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest CONFIG REQUIRED)

include_directories(src)

set(SRC_FILES src/valid_parentheses.cpp)

add_library(ValidParentheses ${SRC_FILES})

add_executable(ValidParenthesesTest test/valid_parentheses_test.cpp)
target_link_libraries(ValidParenthesesTest ValidParentheses GTest::gtest GTest::gtest_main)

enable_testing()
add_test(NAME ValidParenthesesTest COMMAND ValidParenthesesTest)
