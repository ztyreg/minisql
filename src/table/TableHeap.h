#include <utility>

//
// Created by y on 2019-06-11.
//

#ifndef MINISQL_TABLEHEAP_H
#define MINISQL_TABLEHEAP_H

#include <string>
#include "Table.h"


using namespace std;

/**
 * Used to hold tables
 */
class TableHeap {
private:
    map<string, Table *> tables;
public:
    explicit TableHeap();


};


#endif //MINISQL_TABLEHEAP_H
