//
// Created by y on 2019-06-11.
//

#include "TablePage.h"
#include "../common/Config.h"
#include <string>
#include <iostream>
#include "../util/StringUtils.h"

using namespace std;

void TablePage::composePage(page_id_t id, page_id_t prevId, page_id_t nextId,
                            int size, int max, int count)
{
    resetMemory();
    //pageId
    memwrite_int(data, id);
    memwrite_int(data+TABLE_ID, prevId);
    memwrite_int(data+TABLE_ID+TABLE_PREVID, nextId);
    memwrite_int(data+TABLE_ID+TABLE_PREVID+TABLE_NEXTID, size);
    memwrite_int(data+TABLE_ID+TABLE_PREVID+TABLE_NEXTID+TABLE_SIZE, max);
    memwrite_int(data+TABLE_ID+TABLE_PREVID+TABLE_NEXTID+TABLE_SIZE+TABLE_COUNT, count);

}

void TablePage::parsePage()
{
    memread_int(data, (int *)&pageId);
    memread_int(data+TABLE_ID, (int *)&prevId);
    memread_int(data+TABLE_ID+TABLE_PREVID, (int *)&nextId);
    memread_int(data+TABLE_ID+TABLE_PREVID+TABLE_NEXTID, &size);
    memread_int(data+TABLE_ID+TABLE_PREVID+TABLE_NEXTID+TABLE_SIZE, &max);
    memread_int(data+TABLE_ID+TABLE_PREVID+TABLE_NEXTID+TABLE_SIZE+TABLE_COUNT, &count);

}

bool TablePage::pageFull()
{
    return max == count;
}

TablePage::TablePage(Page *p) : Page(*p)
{

}


