//
// Created by y on 2019-06-05.
//

#include "BufferPoolManager.h"
#include <iostream>

BufferPoolManager::BufferPoolManager(int poolSize, DiskManager *diskManager)
        : poolSize(poolSize), diskManager(diskManager)
{
    pages = new Page[poolSize];
    freeList = new list<Page *>;
    replacer = new LruReplacer<Page *>;

    //initialize free list
    for (int i = 0; i < poolSize; ++i) {
        freeList->push_back(&pages[i]);
    }
}

Page *BufferPoolManager::newPage(page_id_t &pageId)
{
    Page *page = nullptr;
    if (!freeList->empty()) {
        page = freeList->front();
        freeList->pop_front();
    } else {
        /* find a victim */
        if (!replacer->victim(page)) {
            return nullptr;
        }
        cout << "\tBuffer: found victim page #" << page->pageId << endl;
        if (page->isDirty) {
            diskManager->writePage(page->pageId, page->data);
            page->isDirty = false;
        }

        pageTable.erase(page->getPageId());

    }

    pageId = diskManager->allocatePage();

    page->pageId = pageId;
    page->isDirty = true;
    page->resetMemory();
    pageTable[pageId] = page;
    replacer->insert(page);


    return page;
}

bool BufferPoolManager::deletePage(page_id_t pageId)
{
    return false;
}

/**
 * (1) Requested page in buffer ? return page : (2) ask DiskManager
 * (2) Free frames ? random one : (3) victim
 * (3) Dirty ? write and read : read
 * @param pageId
 * @return
 */
Page *BufferPoolManager::fetchPage(page_id_t pageId)
{
    Page *page = nullptr;
    if (pageTable.find(pageId) != pageTable.end()) {
        // page already in memory
        cout << "\tBuffer: fetched page #" << pageId << " in page table" << endl;
        page = pageTable[pageId];
        replacer->insert(page);
        return page;
    }


    if (freeList->empty()) {
        // use replacer
        cout << "\tBuffer: new page #" << pageId << " from replacer" << endl;
        if (!replacer->victim(page)) {
            return nullptr;
        }
        cout << "\tBuffer: found victim page #" << page->pageId << endl;
        if (page->isDirty) {
            diskManager->writePage(page->pageId, page->data);
            page->isDirty = false;
        }

        pageTable.erase(page->getPageId());

        // flush dirty page

    } else {
        // fetch from free list
        cout << "\tBuffer: new page #" << pageId << " from free list" << endl;
        page = freeList->front();
        freeList->pop_front();
    }

    //retrieve the physical page
    cout << "\tBuffer: retrieving physical page #" << pageId << " ..." << endl;
    diskManager->readPage(pageId, page->data);
    page->pageId = pageId;
    replacer->insert(page);
    assert(!page->isDirty);

    return page;
}

bool BufferPoolManager::flushPage(page_id_t pageId)
{
    return false;
}

BufferPoolManager::~BufferPoolManager()
{
    delete replacer;
    delete freeList;
    delete [] pages;

}
