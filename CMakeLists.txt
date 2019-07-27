cmake_minimum_required(VERSION 2.8)

project(rolling_median)

add_subdirectory(UTs)
add_subdirectory(googletest)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(${PROJECT_NAME}
    main.cpp
    impl/rollingmedian.cpp
    impl/multiskiplist.cpp
)
