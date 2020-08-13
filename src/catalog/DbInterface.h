//
// Created by y on 2019-06-13.
//

#ifndef MINISQL_DBINTERFACE_H
#define MINISQL_DBINTERFACE_H

#include "../disk/DiskManager.h"
#include "../buffer/DbMetaPage.h"
#include "../buffer/BufferPoolManager.h"
#include "../buffer/TableMetaPage.h"
#include "../common/Data.h"
#include "../index/BTree.h"
#include "../buffer/IndexPage.h"
#include "../buffer/TablePage.h"
#include "../buffer/IndexMetaPage.h"

#include <map>

using namespace std;

class DbInterface {
private:
    DiskManager *diskManager;
    BufferPoolManager *bufferPoolManager;
    map<string, int> tableStart;
    map<string, int> tableEnd;
    DbMetaPage *dbMetaPage;

public:
    DbInterface();

    ~DbInterface();

    void init(string name);

    void writeTableMeta(const string &tableName, string data);

    void deleteTableMeta(const string &tableName);

    void insertTuple(const string &tableName, vector<value_t> tuple);

    vector<vector<string>> readTuple(const string &tableName, bool selectAll,
                                     vector<string> columnNames, vector<whereClause> wheres);

    void createIndex(const string &tableName, const string &attrName, string data);

    int readIndex(const string &tableName, const string &attrName, int mode, Data &key, int val);

    void deleteIndexMeta(const string &tableName, const string &indexName);

    void deleteTuple(const string &tableName, vector<whereClause> wheres);

private:
    void readTable(page_id_t rootId, const string &type, int attrSize, int attrOffset, vector<Data> &keys);

    Tree readTree(page_id_t metaId, const string &type, int attrSize, map<page_id_t, TreeNode *> &id);

    int adjustIndex(Tree T, int mode, const Data &key, int value, const string &type, map<page_id_t, TreeNode *> id);

    bool hasConflict(TableMetaPage *tableMetaPage, string tableName, string columnName, vector<value_t> tuple);
};


#endif //MINISQL_DBINTERFACE_H
