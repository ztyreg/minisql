//
// Created by y on 2019-06-11.
//

#include "TablePage.h"
#include "../common/Config.h"
#include <string>

using namespace std;

void TablePage::composePage(page_id_t id, page_id_t prevId, page_id_t nextId,
                            int size, int max, int count)
{
    //pageId
    memcpy(data, to_string(id).c_str(), TABLE_ID);
    //prevId
    memcpy(data + TABLE_ID, to_string(prevId).c_str(), TABLE_PREVID);
    //nextId
    memcpy(data + TABLE_ID + TABLE_PREVID, to_string(nextId).c_str(), TABLE_NEXTID);
    //size
    memcpy(data + TABLE_ID + TABLE_PREVID + TABLE_NEXTID,
           to_string(size).c_str(), TABLE_SIZE);
    //tuple count 0 when initializing table
    memcpy(data + TABLE_ID + TABLE_PREVID + TABLE_NEXTID + TABLE_SIZE,
           to_string(max).c_str(), TABLE_COUNT);

    memcpy(data + TABLE_ID + TABLE_PREVID + TABLE_NEXTID + TABLE_SIZE + TABLE_COUNT,
           to_string(count).c_str(), TABLE_COUNT);

}

void TablePage::parsePage()
{
    char tempId[TABLE_ID+1];
    char tempPrev[TABLE_PREVID+1];
    char tempNext[TABLE_NEXTID+1];
    char tempSize[TABLE_SIZE+1];
    char tempMax[TABLE_COUNT+1];
    char tempCount[TABLE_COUNT+1];
    memcpy(tempId, data, TABLE_ID);
    memcpy(tempPrev, data+TABLE_ID, TABLE_PREVID);
    memcpy(tempNext, data+TABLE_ID+TABLE_PREVID, TABLE_NEXTID);
    memcpy(tempSize, data+TABLE_ID+TABLE_PREVID+TABLE_NEXTID, TABLE_SIZE);
    memcpy(tempMax, data+TABLE_ID+TABLE_PREVID+TABLE_NEXTID+TABLE_SIZE, TABLE_COUNT);
    memcpy(tempCount, data+TABLE_ID+TABLE_PREVID+TABLE_NEXTID+TABLE_SIZE+TABLE_COUNT, TABLE_COUNT);
    pageId = atoi(tempId);
    prevId = atoi(tempPrev);
    nextId = atoi(tempNext);
    size = atoi(tempSize);
    max = atoi(tempMax);
    count = atoi(tempCount);


}

bool TablePage::pageFull()
{
    return max == count;
}

page_id_t TablePage::getNextId() const
{
    return nextId;
}
