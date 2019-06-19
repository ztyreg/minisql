//
// Created by y on 2019-06-13.
//

#ifndef MINISQL_DBINTERFACE_H
#define MINISQL_DBINTERFACE_H

#include "../table/Tuple.h"
#include "../disk/DiskManager.h"
#include "../buffer/DbMetaPage.h"
#include "../buffer/BufferPoolManager.h"
#include "../buffer/TableMetaPage.h"

#include <map>

using namespace std;

class DbInterface {
private:
    DiskManager *diskManager;
    BufferPoolManager *bufferPoolManager;
    map<string, int> tableStart;
    map<string, int> tableEnd;
    DbMetaPage *dbMetaPage;
    void readMeta();

//    map<string, Table *> tables;

public:
    DbInterface();

    ~DbInterface();

    void init(string name);

    void writeTableMeta(const string& tableName, string data);

    void deleteTableMeta(const string &tableName);

    void insertTuple(const string &tableName, vector<value_t> tuple);

};



#endif //MINISQL_DBINTERFACE_H
