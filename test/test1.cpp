//
// Created by y on 2019-05-25.
//
#include <iostream>
#include <cassert>
#include <gtest/test1.h>
#include "../src/command/Sql.h"


TEST(Sql, SqlTest)
{
    Sql sql;
    sql.addLine("Hi");
    sql.addLine("there;");
    sql.combineLines();
    ASSERT_EQ(sql.getSql(), "Hi there ");

}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}