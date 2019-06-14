//
// Created by y on 2019-06-13.
//

#include "DbInterface.h"
#include "../buffer/TablePage.h"
#include "../buffer/DbMetaPage.h"
#include "../common/Config.h"
#include <iostream>

void DbInterface::init(string name)
{
    diskManager = new DiskManager(name);
    bufferPoolManager = new BufferPoolManager(BUFFER_POOL_SIZE, diskManager);
    // read page 0, which is used to store metadata

    Page *metaPage = bufferPoolManager->fetchPage(0);
    if (metaPage == nullptr) {
        metaPage = bufferPoolManager->newPage(0);
    }

}

DbInterface::~DbInterface()
{
    delete bufferPoolManager;
    delete diskManager;

}

DbInterface::DbInterface()
{

}

void DbInterface::writeMeta(string tableName, string data)
{
    char test[PAGE_SIZE] = "write test";
//    diskManager->writePage(0, test);


    auto *dbMetaPage = static_cast<DbMetaPage *>(bufferPoolManager->fetchPage(0));
    dbMetaPage->parsePage();



}
