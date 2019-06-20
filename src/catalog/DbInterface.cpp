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
    Page *ptableMetaPage = bufferPoolManager->newPage(metaId);
    auto *tableMetaPage =
            new TableMetaPage(ptableMetaPage);

    //new table root page
    page_id_t rootId;
    Page *ptablePage = bufferPoolManager->newPage(rootId);
    auto *tablePage =
            new TablePage(ptablePage);

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
    memcpy(ptableMetaPage->data, tableMetaPage->data, PAGE_SIZE);
    if (DEBUG) strcpy(TEST_CHAR, ptableMetaPage->data);

    cout << "Wrting to " << rootId << endl;
    diskManager->writePage(rootId, tablePage->data);
    memcpy(ptablePage->data, tablePage->data, PAGE_SIZE);

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

#ifdef TEST
    cout << "DROP TABLE test ..." << endl;
    auto *testDbMetaPage =
            new DbMetaPage(bufferPoolManager->fetchPage(0));
    testDbMetaPage->parsePage();
    cout << "\tsize of entries now: " << testDbMetaPage->getEntryNumber() << endl;
    delete testDbMetaPage;
#endif


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
            cout << item.columnName << "(" << item.dataType << "["
                 << item.charLength << "])";
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
    Page *ptablePage = bufferPoolManager->fetchPage(rootId);
    auto *tablePage =
            new TablePage(ptablePage);
    tablePage->parsePage();

    page_id_t nextId = tablePage->nextId;
    while (nextId != INVALID_PAGE_ID) {
        delete tablePage;
        tablePage = new TablePage(bufferPoolManager->fetchPage(nextId));
        tablePage->parsePage();
        nextId = tablePage->nextId;
    }

    cout << "\tlast page ID #" << tablePage->pageId
         << " count: " << tablePage->count
         << " size: " << tablePage->size
         << " max: " << tablePage->max << endl;

    if (tablePage->pageFull()) {
        page_id_t newId;
        auto *newPage =
                new TablePage(bufferPoolManager->newPage(newId));
        newPage->composePage(newId, tablePage->pageId, INVALID_PAGE_ID,
                             tablePage->size, tablePage->max, 0);
        delete tablePage;
        tablePage = newPage;
        tablePage->parsePage();
    }

    //assemble tuple
    char *t = new char[tablePage->size];
    int offset = 0;
    for (int i = 0; i < tuple.size(); ++i) {
        //int will be converted to float
        if (tuple[i].type == "int") {
            memwrite_int(t + offset, stoi(tuple[i].field));
            offset += 4;
        } else if (tuple[i].type == "float") {
            memwrite_float(t + offset, stof(tuple[i].field));
            offset += 4;
        } else if (tuple[i].type == "char") {
            int len = tableMetaPage->columns[i].charLength;
            char *s = new char[len];
            memset(s, 0, len);
            memcpy(s, tuple[i].field.c_str(), tuple[i].field.length());
            memcpy(t + offset, s, len);
            offset += tuple[i].field.length();
            delete[] s;
        }
    }

    cout << "\ttuple: " << t << endl;
    tablePage->addTupleString(t);
    tablePage->composePage();

    cout << "Wrting to " << tablePage->pageId << endl;
    diskManager->writePage(tablePage->pageId, tablePage->data);
    memcpy(ptablePage->data, tablePage->data, PAGE_SIZE);


    delete[] t;

    //start pointer


    //if new page


    delete tableMetaPage;
    delete tablePage;
}

