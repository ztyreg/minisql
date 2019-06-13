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
 * | PageId (4)| LSN (4)| PrevPageId (4)| NextPageId (4)| FreeSpacePointer(4) |
 *  --------------------------------------------------------------------------
 *  --------------------------------------------------------------
 * | TupleCount (4) | Tuple_1 offset (4) | Tuple_1 size (4) | ... |
 *  --------------------------------------------------------------
 *
 */

class TablePage : public Page {
public:
    /* initialize header */
    void init();

};


#endif //MINISQL_TABLEPAGE_H
