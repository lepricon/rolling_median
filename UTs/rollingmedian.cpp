#include "../rollingmedian.h"
#include "gtest/gtest.h"
#include <vector>

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
    EXPECT_EQ(i, expected.size());
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
    Params{"", {}},
    Params{"m", {}},
    Params{"q", {}},
    Params{"m q", {}},
    Params{"3 5 8 6 q", {}},
    Params{"5 m q", {5}},
    Params{"-3 5 -2 m q", {-2}},
    Params{"5 5 5 5 3 3 3 3 m q", {4}},
    Params{"5 5 3 m q", {5}},
    Params{"0 m m m q", {0, 0, 0}},
    Params{"-2 m 2 m -4 m 4 q", {-2, 0, -2}},
    Params{"1 m 1 1 1 1 1 1 m 1 q", {1, 1}},
    Params{"m 2147483647 m -2147483648 m q", {2147483647, -0.5}}
));
