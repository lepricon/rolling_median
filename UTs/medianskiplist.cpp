#include "../medianskiplist.h"

#include <gtest/gtest.h>
#include <chrono>
#include <random>
#include <set>

TEST(MultiSkipListTest, should_increase_len_on_some_value)
{
    MedianSkipList list;
    EXPECT_EQ(0, list.size());

    list.insert(1);
    EXPECT_EQ(1, list.size());
}

TEST(MultiSkipListTest, should_not_increase_len_on_same_value)
{
    MedianSkipList list;
    EXPECT_EQ(0, list.size());

    list.insert(1);
    EXPECT_EQ(1, list.size());
}

TEST(MultiSkipListTest, should_increase_len_on_values)
{
    MedianSkipList list;
    EXPECT_EQ(0, list.size());

    list.insert(1);
    EXPECT_EQ(1, list.size());

    list.insert(1);
    EXPECT_EQ(2, list.size());

    list.insert(2);
    EXPECT_EQ(3, list.size());
}

TEST(MultiSkipListTest, DISABLED_should_be_comparatively_fast) // use --gtest_also_run_disabled_tests to run performance test
{
    const std::size_t SIZE = 1000 * 1000;
    std::random_device rd;
    std::uniform_int_distribution<int> dist;

    std::chrono::milliseconds listDuration, setDuration;
    {
        auto start = std::chrono::high_resolution_clock::now();
        MedianSkipList list;
        EXPECT_EQ(0, list.size());

        for (std::size_t i = 0; i < SIZE; i++) {
            list.insert(dist(rd));
        }
        EXPECT_EQ(SIZE, list.size());

        listDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        std::cout << "list duration: " << listDuration.count() << " ms" << std::endl;
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        std::multiset<int> myset;
        EXPECT_EQ(0, myset.size());

        for (std::size_t i = 0; i < SIZE; i++) {
            myset.insert(dist(rd));
        }
        EXPECT_EQ(SIZE, myset.size());

        setDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        std::cout << "set duration: " << setDuration.count() << " ms" << std::endl;
    }

    auto list = static_cast<double>(listDuration.count());
    auto set = static_cast<double>(setDuration.count());
    auto relative = list / set;
    EXPECT_LT(relative, 1.2);
}
