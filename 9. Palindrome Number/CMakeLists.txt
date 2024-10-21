cmake_minimum_required(VERSION 3.10)

project(main VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main main.cpp)

target_compile_options(main PRIVATE -O3 -Wall -Wextra -pedantic)

# enable_testing()
# add_test(NAME MainTest COMMAND main_test)
