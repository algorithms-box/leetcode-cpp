cmake_minimum_required(VERSION 3.10)
project(LongestPushTime)

# 设置 C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含 src 文件夹
include_directories(src)

# 添加源文件
set(SRC_FILES src/LongestPushTime.cpp)

# 添加测试文件
set(TEST_FILES test/LongestPushTimeTest.cpp)

# 创建库
add_library(LongestPushTime ${SRC_FILES})

# 创建测试可执行文件
add_executable(LongestPushTimeTest ${TEST_FILES})

# 链接库和 Google Test
target_link_libraries(LongestPushTimeTest LongestPushTime gtest gtest_main)

# 启用测试
enable_testing()
add_test(NAME LongestPushTimeTest COMMAND LongestPushTimeTest)