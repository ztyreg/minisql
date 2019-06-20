#include <utility>

//
// Created by y on 2019-06-13.
//

#include "DbInterface.h"
#include "../buffer/TablePage.h"
#include "../buffer/TableMetaPage.h"
#include <iostream>

void DbInterface::init(string name)
{
    diskManager = new DiskManager(name);
    bufferPoolManager = new BufferPoolManager(BUFFER_POOL_SIZE, diskManager);
    // read page 0, which is used to store metadata

    dbMetaPage = new DbMetaPage(bufferPoolManager->fetchPage(0));
    if (!dbMetaPage->parsePage()) {
        //new db
        diskManager->clearFile();
        delete diskManager;
        diskManager = new DiskManager(name);
        diskManager->writePage(0, dbMetaPage->data);

        delete bufferPoolManager;
        bufferPoolManager = new BufferPoolManager(BUFFER_POOL_SIZE, diskManager);

    }

    //
    //test
    //


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
void DbInterface::writeTableMeta(const string &tableName, string data)
{
    if (dbMetaPage->entryExists(tableName)) {
        cerr << "table exists" << endl;
        return;
    }

    //meta pages could be directly accessed
    //new page to store table meta
    page_id_t metaId;
    //not the same page
    Page *page1 = bufferPoolManager->newPage(metaId);
    auto *tableMetaPage =
            new TableMetaPage(page1);

    //new table root page
    page_id_t rootId;
    Page *page2 = bufferPoolManager->newPage(rootId);
    auto *tablePage =
            new TablePage(page2);

    //add table metadata
    tableMetaPage->composePage(rootId, std::move(data));
    tableMetaPage->parsePage();
    cout << "\tnew table with tuple length "
         << tableMetaPage->getTupleLength() << endl;
    //add table data
    tablePage->composePage(rootId, INVALID_PAGE_ID, INVALID_PAGE_ID,
                           tableMetaPage->getTupleLength(),
                           tableMetaPage->calMaxNumOfTuples(), 0);

    //add db metadata
    dbMetaPage->entries.insert(make_pair(tableName, metaId));
    //write db metadata
    dbMetaPage->composePage();


    cout << "Wrting to " << metaId << endl;
    diskManager->writePage(metaId, tableMetaPage->data);
    memcpy(page1->data, tableMetaPage->data, PAGE_SIZE);
    if (DEBUG) strcpy(TEST_CHAR, page1->data);

    cout << "Wrting to " << rootId << endl;
    diskManager->writePage(rootId, tablePage->data);
    memcpy(page2->data, tablePage->data, PAGE_SIZE);

    cout << "Wrting to page 0" << endl;
    diskManager->writePage(0, dbMetaPage->data);


#ifdef TEST
    cout << "CREATE TABLE test ..." << endl;
    Page *pPage = bufferPoolManager->fetchPage(0);
    auto *testDbMetaPage =
            new DbMetaPage(pPage);
    testDbMetaPage->parsePage();
    cout << "\tsize of entries now: " << testDbMetaPage->getEntryNumber() << endl;

    Page *pPage2 = bufferPoolManager->fetchPage(metaId);
    if (DEBUG) cout << "DEBUG: #" << pPage2->pageId << " " << pPage2 << endl;
    auto *testTableMetaPage =
            new TableMetaPage(pPage2);
    if (DEBUG) cout << "DEBUG: #" << testTableMetaPage->pageId << " " << endl;
    if (DEBUG) cout << strcmp(TEST_CHAR, testTableMetaPage->data) << endl;
    testTableMetaPage->parsePage();
    cout << "\tDDL:" << testTableMetaPage->ddl << endl;

    delete testTableMetaPage;
    delete testDbMetaPage;
#endif

    delete tablePage;
    delete tableMetaPage;

}

void DbInterface::deleteTableMeta(const string &tableName)
{
    if (!dbMetaPage->entryExists(tableName)) {
        cerr << "table does not exist" << endl;
        return;
    }

    //lazy deletion: only db meta
    dbMetaPage->entries.erase(tableName);
    dbMetaPage->composePage();
    cout << "Wrting to page 0" << endl;
    diskManager->writePage(0, dbMetaPage->data);

    //
    //test
    //
    cout << "DROP TABLE test ..." << endl;
    auto *testDbMetaPage =
            new DbMetaPage(bufferPoolManager->fetchPage(0));
    testDbMetaPage->parsePage();
    cout << "\tsize of entries now: " << testDbMetaPage->getEntryNumber() << endl;
    delete testDbMetaPage;


}

void DbInterface::insertTuple(const string &tableName, vector<value_t> tuple)
{
    if (!dbMetaPage->entryExists(tableName)) {
        cerr << "table does not exist" << endl;
        return;
    }

    page_id_t metaId = dbMetaPage->entries[tableName];
    auto *tableMetaPage =
            new TableMetaPage(bufferPoolManager->fetchPage(metaId));
    tableMetaPage->parsePage();

#ifdef TEST
    cout << "INSERT test ..." << endl;
    for (const auto &item : tableMetaPage->columns) {
        if (item.dataType == "char") {
            cout << item.columnName << "(" << item.dataType << "[" << item.charLength << "])";
        } else {
            cout << item.columnName << "(" << item.dataType << ")";
        }
        cout << (item.isUnique ? "U" : "");
        cout << (item.isPrimaryKey ? "P" : "");
        cout << " ";
    }
    cout << endl;
#endif

    //check value type
    if (tableMetaPage->columns.size() != tuple.size()) {
        cerr << "wrong tuple size" << endl;
        return;
    }
    for (int i = 0; i < tuple.size(); ++i) {
        //int will be converted to float
        if (tableMetaPage->columns[i].dataType == "float" &&
            tuple[i].type == "int")
            continue;
        if (tableMetaPage->columns[i].dataType != tuple[i].type) {
            cerr << "wrong data type" << endl;
        }
    }


    //last table page
    page_id_t rootId = tableMetaPage->getRootId();
    auto *tablePage =
            new TablePage(bufferPoolManager->fetchPage(rootId));
    tablePage->parsePage();

    page_id_t nextId = tablePage->nextId;

    while (nextId != INVALID_PAGE_ID) {
        delete tablePage;
        tablePage = new TablePage(bufferPoolManager->fetchPage(nextId));
        tablePage->parsePage();
        nextId = tablePage->nextId;
    }

    cout << "\tlast page ID #" << tablePage->pageId
         << " count: " << tablePage->count << endl;

    //tuple size are the same


    //start pointer


    //if new page


    delete tableMetaPage;
    delete tablePage;
}

