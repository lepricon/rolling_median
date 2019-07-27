#include "../rollingmedian.h"
#include "gtest/gtest.h"
#include<vector>

TEST(RollingMedian, no_input)
{
    EXPECT_NO_THROW(RollingMedians().getMedians(""));
    EXPECT_NO_THROW(RollingMedians().getMedians("q"));
    EXPECT_THROW(RollingMedians().getMedians("m"), std::runtime_error);
    EXPECT_THROW(RollingMedians().getMedians("m q"), std::runtime_error);
}


void verifyResult(const std::string& medians, const std::vector<double>& expected)
{
    std::istringstream in(medians);
    std::size_t i = 0;
    double d;
    in >> d;
    while (not in.eof()) {
        EXPECT_DOUBLE_EQ(d, expected[i]);
        i++;
        in >> d;
    }
}

using Params = std::pair<const std::string, const std::vector<double>>;
using RollingMedianTestSuite = ::testing::TestWithParam<Params>;

TEST_P(RollingMedianTestSuite, test)
{
    const Params& p = GetParam();
    const std::string result = RollingMedians().getMedians(p.first);
    EXPECT_NO_FATAL_FAILURE(verifyResult(result, p.second));
}

INSTANTIATE_TEST_SUITE_P(RollingMedianTestSuiteInstance, RollingMedianTestSuite, ::testing::Values(
    Params{"3 5 m 8 m 6 m q", {4, 5, 5.5}},
    Params{"5 m q", {5}},
    Params{"-3 5 -2 m q", {-2}},
    Params{"5 5 5 5 3 3 3 3 m q", {4}},
    Params{"5 5 3 m q", {5}},
    Params{"9 8 7 6 5 4 3 2 1 m q", {5}},
    Params{"-2 -3 -4 -5 -6 -7 m q", {-4.5}}
));
