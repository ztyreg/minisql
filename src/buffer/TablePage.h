//
// Created by y on 2019-06-11.
//

#ifndef MINISQL_TABLEPAGE_H
#define MINISQL_TABLEPAGE_H

#include "Page.h"

/**
 * TablePage.h
 *
 *  Header format (size in byte):
 *
 * | PageId (4)| PrevPageId (4)| NextPageId (4)| TupleSize (4) | TupleCount (4) | ...
 *
 *
 *
 */

class TablePage : public Page {
    friend class DbInterface;
public:
    /* initialize header */
    explicit TablePage(Page const& p) : Page(p) {};

    void composePage(page_id_t id, page_id_t prevId, page_id_t nextId);

};


#endif //MINISQL_TABLEPAGE_H
