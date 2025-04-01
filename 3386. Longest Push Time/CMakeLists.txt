cmake_minimum_required(VERSION 3.14)

set(project_name longest_push_time)

project(${project_name} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${project_name}-lib
        src/LongestPushTime.cpp
)

find_package(GTest REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC GTest::GTest
        PUBLIC GTest::Main
)

add_executable(${project_name}-test
        test/LongestPushTimeTest.cpp
)

target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

enable_testing()
add_test(NAME LongestPushTimeTest COMMAND ${project_name}-test)