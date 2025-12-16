#include <gtest/gtest.h>
#include "../functions.h"
#include <vector>
#include <tuple>
#include <string>

// Тест: split на пустой строке
TEST(SplitTest, EmptyString)
{
    auto result = split("", '.');
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "");
}

// Тест: split без разделителя
TEST(SplitTest, NoDelimiter)
{
    auto result = split("192", '.');
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "192");
}

// Тест: split с несколькими частями
TEST(SplitTest, MultipleParts)
{
    auto result = split("192.168.0.1", '.');
    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], "192");
    EXPECT_EQ(result[1], "168");
    EXPECT_EQ(result[2], "0");
    EXPECT_EQ(result[3], "1");
}

// Тест: сортировка IP-адресов в порядке убывания (лексикографически по кортежу)
TEST(IpSortTest, DescendingOrder)
{
    std::vector<std::tuple<int, int, int, int>> ips = {
        {1, 2, 3, 4},
        {1, 10, 1, 1},
        {2, 0, 0, 0},
        {1, 2, 3, 5}};
    mainSort(ips);

    EXPECT_EQ(ips[0], std::make_tuple(2, 0, 0, 0));
    EXPECT_EQ(ips[1], std::make_tuple(1, 10, 1, 1));
    EXPECT_EQ(ips[2], std::make_tuple(1, 2, 3, 5));
    EXPECT_EQ(ips[3], std::make_tuple(1, 2, 3, 4));
}