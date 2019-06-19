//
// Created by y on 2019-06-15.
//

#ifndef MINISQL_TABLE_H
#define MINISQL_TABLE_H

#include <string>
#include "../command/CreateTable.h"

using namespace std;

/**
 * Table metadata
 */
class Table {
private:
    string tableName;

public:
    Table(string tableName, string ddl);

};


#endif //MINISQL_TABLE_H
