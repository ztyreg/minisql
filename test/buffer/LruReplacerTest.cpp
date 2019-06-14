//
// Created by y on 2019-06-11.
//

#include <cstdio>

#include "../../src/buffer/LruReplacer.h"
#include "../../src/buffer/LruReplacer.cpp"
#include "gtest/gtest.h"


TEST(LruReplacerTest, SampleTest) {
    LruReplacer<int> lruReplacer;

    EXPECT_EQ(0, lruReplacer.size());

    lruReplacer.insert(5);
    lruReplacer.insert(6);
    lruReplacer.insert(7);
    lruReplacer.insert(8);
    lruReplacer.insert(9);
    EXPECT_EQ(5, lruReplacer.size());
    EXPECT_EQ(5, lruReplacer.getTracker()[0].first);
    EXPECT_EQ(0, lruReplacer.getTracker()[0].second);

    int victim = 0;
    lruReplacer.victim(victim);
    EXPECT_EQ(5, victim);
    lruReplacer.victim(victim);
    EXPECT_EQ(6, victim);

    lruReplacer.erase(7);
    lruReplacer.victim(victim);
    EXPECT_EQ(8, victim);
}
