//
// Created by y on 2019-06-11.
//

#ifndef MINISQL_TABLEPAGE_H
#define MINISQL_TABLEPAGE_H

#include "Page.h"

/**
 * TablePage.h
 *
 * Slotted page format:
 *  ---------------------------------------
 * | HEADER | ... FREE SPACES ... | TUPLES |
 *  ---------------------------------------
 *                                 ^
 *                         free space pointer
 *
 *  Header format (size in byte):
 *  --------------------------------------------------------------------------
 * | PageId (4)| PrevPageId (4)| NextPageId (4)| FreeSpacePointer(4) |
 *  --------------------------------------------------------------------------
 *  --------------------------------------------------------------
 * | TupleCount (4) | Tuple_1 offset (4) | Tuple_1 size (4) | ... |
 *  --------------------------------------------------------------
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
