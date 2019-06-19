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
    auto *tableMetaPage =
            new TableMetaPage(*bufferPoolManager->newPage(metaId));

    //new table root page
    page_id_t rootId;
    auto *tablePage =
            new TablePage(*bufferPoolManager->newPage(rootId));

    //add table metadata
    tableMetaPage->composePage(rootId, std::move(data));
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


    //
    //test
    //
    cout << "CREATE TABLE test ..." << endl;
    auto *testDbMetaPage =
            new DbMetaPage(*bufferPoolManager->fetchPage(0));
    testDbMetaPage->parsePage();
    cout << "\tsize of entries now: " << testDbMetaPage->getEntryNumber() << endl;
    delete testDbMetaPage;

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
            new DbMetaPage(*bufferPoolManager->fetchPage(0));
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
            new TableMetaPage(*bufferPoolManager->fetchPage(metaId));
    tableMetaPage->parsePage();

    //
    //test
    //
    cout << "INSERT test ..." << endl;
    cout << tableMetaPage->primaryKey << endl;
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

    //check value type
    if (tableMetaPage->columns.size() != tuple.size()) {
        cerr << "wrong tuple size" << endl;
        return;
    }
    for (int i = 0; i < tuple.size(); ++i) {
        cout << tableMetaPage->columns[i].dataType << tuple[i].type << endl;
        //int will be converted to float
        if (tableMetaPage->columns[i].dataType == "float" &&
            tuple[i].type == "int")
            continue;
        if (tableMetaPage->columns[i].dataType != tuple[i].type) {
            cerr << "wrong data type" << endl;
        }
    }

    cout << "HERE" << endl;
    //last table page


    //tuple size are the same


    //start pointer


    //if new page


    delete tableMetaPage;
}

