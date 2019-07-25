cmake_minimum_required(VERSION 2.8)

project(rolling_median)
add_executable(${PROJECT_NAME} "main.cpp" "rollingmedians.cpp" "multiskiplist.cpp")

add_subdirectory(UTs)


add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
