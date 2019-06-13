//
// Created by y on 2019-06-05.
//

#include "BufferPoolManager.h"

BufferPoolManager::BufferPoolManager(int poolSize, DiskManager *diskManager)
: poolSize(poolSize), diskManager(diskManager)
{

}

Page *BufferPoolManager::newPage(page_id_t &pageId)
{
    Page *page = nullptr;
    if (!freeList->empty()) {
        page = *freeList->begin();
        freeList->pop_front();
        //TODO dirty?
    } else {
        /* find a victim */
        if (!replacer->victim(page)) {
            return nullptr;
        }
        if (page->isDirty) {
            diskManager->writePage(page->pageId, page->data);
            page->isDirty = false;
        }

    }

    return nullptr;
}

bool BufferPoolManager::deletePage(page_id_t pageId)
{
    return false;
}

Page *BufferPoolManager::fetchPage(page_id_t pageId)
{
    return nullptr;
}

bool BufferPoolManager::flushPage(page_id_t pageId)
{
    return false;
}
