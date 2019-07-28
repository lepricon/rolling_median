#include "../medianskiplist.h"

#include <random>
#include <gtest/gtest.h>

TEST(MultiSkipListTest, should_increase_len_on_some_value)
{
    MedianSkipList list;
    EXPECT_EQ(0, list.size());

    list.insert(1.0);
    EXPECT_EQ(1, list.size());
}

TEST(MultiSkipListTest, should_not_increase_len_on_same_value)
{
    MedianSkipList list;
    EXPECT_EQ(0, list.size());

    list.insert(1.0);
    EXPECT_EQ(1, list.size());
}

TEST(MultiSkipListTest, should_increase_len_on_values)
{
    MedianSkipList list;
    EXPECT_EQ(0, list.size());

    list.insert(1.0);
    EXPECT_EQ(1, list.size());

    list.insert(2.0);
    EXPECT_EQ(2, list.size());

    list.insert(1.5);
    EXPECT_EQ(3, list.size());
}

TEST(MultiSkipListTest, should_handle_lots_of_random_inserts)
{
    const std::size_t SIZE = 1000 * 1000;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, SIZE);

    MedianSkipList list;
    EXPECT_EQ(0, list.size());

    for (std::size_t i = 0; i < SIZE; i++) {
        list.insert(dist(rd) + 0.1);
    }

    EXPECT_EQ(SIZE, list.size());
}

#include <set>

TEST(MultiSkipListTest, set_should_handle_lots_of_random_inserts)
{
    const std::size_t SIZE = 1000 * 1000;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, SIZE);

    std::set<double> myset;
    EXPECT_EQ(0, myset.size());

    for (std::size_t i = 0; i < SIZE; i++) {
        myset.insert(dist(rd) + 0.1);
    }

    EXPECT_GT(myset.size(), 0);
}
