#include "rollingmedians.h"
#include "gtest/gtest.h"

TEST(RollingMedian, test)
{
    const std::string input = "3 5 m 8 m 6 m q";
    const std::string expected = "4.0 5.0 5.5";
    EXPECT_EQ(expected, RollingMedians().getMedians(input));
}
