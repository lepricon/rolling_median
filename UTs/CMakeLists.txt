cmake_minimum_required(VERSION 2.8)

include_directories(..)

add_executable(ut-${PROJECT_NAME} test.cpp ../rollingmedians.cpp)
target_link_libraries(ut-${PROJECT_NAME} gtest gtest_main)
