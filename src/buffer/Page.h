//
// Created by y on 2019-06-05.
//

#ifndef MINISQL_PAGE_H
#define MINISQL_PAGE_H

#include <cstring>
#include "../common/Config.h"
#include "../util/StringUtils.h"

/**
* Format (size in byte):
*  -----------------------------------------------------------------
* | RecordCount (4) | Entry_1 name (32) | Entry_1 root_id (4) | ... |
*  -----------------------------------------------------------------
*/

class Page {
    friend class BufferPoolManager;
    friend class DbInterface;
    friend class DbMetaPage;
    friend class TableMetaPage;
    friend class TablePage;

private:
    bool isDirty = false;
    page_id_t pageId = INVALID_PAGE_ID;

protected:
    char data[PAGE_SIZE];

public:
    void printData();

    page_id_t getPageId() const { return pageId; }

    void resetMemory() { memset(data, 0, PAGE_SIZE); }


};


#endif //MINISQL_PAGE_H
