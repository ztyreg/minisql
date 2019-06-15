//
// Created by y on 2019-06-11.
//

#include "TablePage.h"
#include "../common/Config.h"
#include <string>

using namespace std;

void TablePage::composePage(page_id_t id, page_id_t prevId, page_id_t nextId)
{
    memcpy(data, to_string(id).c_str(), TABLE_ID);
    memcpy(data+TABLE_ID, to_string(prevId).c_str(), TABLE_PREVID);
    memcpy(data+TABLE_ID+TABLE_PREVID, to_string(nextId).c_str(), TABLE_NEXTID);
    memcpy(data+TABLE_ID+TABLE_PREVID+TABLE_NEXTID,
            to_string(TABLE_TUPLE_START).c_str(), TABLE_POINTER);
    //tuple count 0 when initializing table
    memcpy(data+TABLE_ID+TABLE_PREVID+TABLE_NEXTID+TABLE_POINTER,
            to_string(0).c_str(), TABLE_COUNT);

}
