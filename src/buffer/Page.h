//
// Created by y on 2019-06-05.
//

#ifndef MINISQL_PAGE_H
#define MINISQL_PAGE_H

#include "../common/Config.h"

class Page {
    friend class BufferPoolManager;

private:
    bool isDirty = false;
    page_id_t pageId = INVALID_PAGE_ID;
    char data[PAGE_SIZE];

public:


};


#endif //MINISQL_PAGE_H
