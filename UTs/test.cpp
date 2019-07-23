#include "rollingmedians.h"
#include "gtest/gtest.h"

TEST(RollingMedian, test)
{
    EXPECT_EQ("4.0 5.0 5.5", RollingMedians().getMedians("3 5 m 8 m 6 m q"));
}
