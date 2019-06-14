//
// Created by y on 2019-06-13.
//

#include "DbInterface.h"
#include "../buffer/TablePage.h"
#include "../common/Config.h"
#include <iostream>

void DbInterface::init(string name)
{
    diskManager = new DiskManager(name);
    bufferPoolManager = new BufferPoolManager(BUFFER_POOL_SIZE, diskManager);
    // read page 0, which is used to store metadata

    dbMetaPage = new DbMetaPage(*bufferPoolManager->fetchPage(0));
    dbMetaPage->parsePage();

//    Page *metaPage = bufferPoolManager->fetchPage(0);
//    if (metaPage == nullptr) {
//        metaPage = bufferPoolManager->newPage(0);
//    }

}

DbInterface::~DbInterface()
{


    delete dbMetaPage;
    delete bufferPoolManager;
    delete diskManager;
}

DbInterface::DbInterface()
{

}

void DbInterface::writeMeta(string tableName, string data)
{
    dbMetaPage->composePage();
    cout << "Writing db metadata ..." << dbMetaPage->data << endl;
    diskManager->replacePage(0, dbMetaPage->data);





}
