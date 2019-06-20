//
// Created by y on 2019-06-11.
//

#include <cstdio>

#include "../../src/buffer/LruReplacer.h"
#include "../../src/buffer/LruReplacer.cpp"
#include "../../src/disk/DiskManager.h"
#include "../../src/disk/DiskManager.cpp"
#include "../../src/buffer/BufferPoolManager.h"
#include "../../src/buffer/BufferPoolManager.cpp"
#include "../../src/common/Config.h"
#include "gtest/gtest.h"

TEST(BufferPoolManagerTest, SampleTest)
{
    DiskManager *diskManager = new DiskManager("testdb");
    BufferPoolManager *bufferPoolManager =
            new BufferPoolManager(5, diskManager);

    page_id_t id0 = 0;
    page_id_t id1 = 1;
    page_id_t id2 = 2;
    page_id_t id3 = 3;
    page_id_t id4 = 4;
    page_id_t id5 = 5;
    page_id_t id6 = 6;
    page_id_t id7 = 7;
    page_id_t id8 = 8;
    page_id_t id9 = 9;

    Page *page0 = bufferPoolManager->newPage(id0);
    Page *page1 = bufferPoolManager->newPage(id1);
    Page *page2 = bufferPoolManager->newPage(id2);
    Page *page3 = bufferPoolManager->newPage(id3);
    Page *page4 = bufferPoolManager->newPage(id4);
    Page *page5 = bufferPoolManager->newPage(id5);

    Page *f0 = bufferPoolManager->fetchPage(id0);

}
