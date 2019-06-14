//
// Created by y on 2019-06-05.
//

#ifndef MINISQL_PAGE_H
#define MINISQL_PAGE_H

#include "../common/Config.h"

/**
* Format (size in byte):
*  -----------------------------------------------------------------
* | RecordCount (4) | Entry_1 name (32) | Entry_1 root_id (4) | ... |
*  -----------------------------------------------------------------
*/

class Page {
    friend class BufferPoolManager;
    friend class DbInterface;

private:
    bool isDirty = false;
    page_id_t pageId = INVALID_PAGE_ID;

protected:
    char data[PAGE_SIZE];

public:
    void printData();



};


#endif //MINISQL_PAGE_H
