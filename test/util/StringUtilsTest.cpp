//
// Created by y on 2019-06-20.
//

#include <cstdio>

#include "../../src/util/StringUtils.h"
#include "../../src/util/StringUtils.cpp"
#include "gtest/gtest.h"

using namespace std;

TEST(StringUtilsTest, SampleTest) {
    string bin1 = "00000000000000000000000000000100";
    int n1 = bstring_to_int(bin1);
    EXPECT_EQ(n1, 4);
    bin1 = "00000000000000000000000000010000";
    n1 = bstring_to_int(bin1);
    EXPECT_EQ(n1, 16);

    int n2 = 4;
    string bin2 = int_to_bstring(n2);
    EXPECT_EQ(bin2, "00000000000000000000000000000100");

    string bin3 = "10111111010000000000000000000000";
    float n3 = bstring_to_float(bin3);
    EXPECT_EQ(n3, -0.75);

    float n4 = -0.75;
    string bin4 = float_to_bstring(n4);
    EXPECT_EQ(bin4, "10111111010000000000000000000000");

    char mem[4];
    int m1;
    memwrite_int(mem, 12345);
    memread_int(mem, &m1);
    EXPECT_EQ(m1, 12345);

    float m2;
    //loss of precision!
    memwrite_float(mem, 98.5);
    memread_float(mem, &m2);
    EXPECT_EQ(m2, 98.5);
}
