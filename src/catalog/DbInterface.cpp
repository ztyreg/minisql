//
// Created by y on 2019-06-13.
//

#include "DbInterface.h"
#include "../buffer/TablePage.h"
#include "../buffer/TableMetaPage.h"
#include "../common/Config.h"
#include <iostream>

void DbInterface::init(string name)
{
    diskManager = new DiskManager(name);
    bufferPoolManager = new BufferPoolManager(BUFFER_POOL_SIZE, diskManager);
    // read page 0, which is used to store metadata

    dbMetaPage = new DbMetaPage(*bufferPoolManager->fetchPage(0));
    if (!dbMetaPage->parsePage()) {
        //new db
        diskManager->clearFile();
        delete diskManager;
        diskManager = new DiskManager(name);
        diskManager->writePage(0, dbMetaPage->data);

        delete bufferPoolManager;
        bufferPoolManager = new BufferPoolManager(BUFFER_POOL_SIZE, diskManager);

    }



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

/**
 * new table/index meta page
 */
void DbInterface::writeTableMeta(string tableName, string data)
{
    //meta pages could be directly accessed
    //new page to store table meta
    page_id_t metaId;
    auto *tableMetaPage =
            new TableMetaPage(*bufferPoolManager->newPage(metaId));

    //new table root page
    page_id_t rootId;
    auto *tablePage =
            new TablePage(*bufferPoolManager->newPage(rootId));

    //add table metadata
    tableMetaPage->composePage(rootId, data);
    //add table data
    tablePage->composePage(rootId, INVALID_PAGE_ID, INVALID_PAGE_ID);

    //add db metadata
    dbMetaPage->entries.insert(make_pair(tableName, metaId));
    //write db metadata
    dbMetaPage->composePage();



    cout << "Wrting " << tableMetaPage->data << " to " << metaId << endl;
    diskManager->writePage(metaId, tableMetaPage->data);
    cout << "Wrting " << tablePage->data << " to " << rootId << endl;
    diskManager->writePage(rootId, tablePage->data);
    cout << "Wrting to page 0" << endl;
    diskManager->writePage(0, dbMetaPage->data);



}
