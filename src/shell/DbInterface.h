//
// Created by y on 2019-06-13.
//

#ifndef MINISQL_DBINTERFACE_H
#define MINISQL_DBINTERFACE_H

#include "../table/TableHeap.h"
#include "../table/Tuple.h"
#include "../disk/DiskManager.h"
#include "../buffer/BufferPoolManager.h"
#include <map>

using namespace std;

class DbInterface {
private:
    DiskManager *diskManager;
    BufferPoolManager *bufferPoolManager;
    map<string, int> tableStart;
    map<string, int> tableEnd;
    void readMeta();

public:
    DbInterface();

    ~DbInterface();

    void init(string name);

    void writeMeta(string tableName, string data);

    void writeData(string tableName, Tuple &tuple);
};


#endif //MINISQL_DBINTERFACE_H
