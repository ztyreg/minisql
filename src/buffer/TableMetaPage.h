//
// Created by y on 2019-06-14.
//

#ifndef MINISQL_TABLEMETAPAGE_H
#define MINISQL_TABLEMETAPAGE_H

#include "Page.h"
#include <string>

using namespace std;


/**
 * | root_id (4) | ddl_size (4) | CREATE TABLE … ;
 */
class TableMetaPage : Page {
    friend class DbInterface;
public:
    explicit TableMetaPage(Page const& p) : Page(p) {};

    void composePage(page_id_t rootId, string ddl);

};


#endif //MINISQL_TABLEMETAPAGE_H
