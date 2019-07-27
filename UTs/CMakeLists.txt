cmake_minimum_required(VERSION 2.8)

set(UT_PREFIX "ut_")

add_executable(${UT_PREFIX}${PROJECT_NAME}
    ../impl/medianskiplist.cpp
    ../impl/rollingmedian.cpp

    rollingmedian.cpp
    medianskiplist.cpp
)
target_link_libraries(${UT_PREFIX}${PROJECT_NAME} gtest gtest_main)
