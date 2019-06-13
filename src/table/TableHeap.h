#include <utility>

//
// Created by y on 2019-06-11.
//

#ifndef MINISQL_TABLEHEAP_H
#define MINISQL_TABLEHEAP_H

#include "../buffer/Page.h"
#include <string>

using namespace std;

/**
 * Used to hold tables
 */
class TableHeap {
private:
    string name;
    Page *pages;
public:
    explicit TableHeap();


};


#endif //MINISQL_TABLEHEAP_H
