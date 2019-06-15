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

    pageId = diskManager->allocatePage();

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
    // page already in ?
    // TODO page table
    for (int i = 0; i < poolSize; i++) {
        if (pages[i].pageId == pageId) {
            cout << "Found page in page table" << endl;
            return &pages[i];
        }
    }

    Page *page = nullptr;
    if (freeList->empty()) {
        // use replacer

        // flush dirty page

    } else {
        // fetch from free list
        cout << "New page in free list" << endl;
        page = freeList->front();
        freeList->pop_front();
    }

    //retrieve the physical page
    cout << "Retrieving physical page #" << pageId << " ..." << endl;
    diskManager->readPage(pageId, page->data);
    page->pageId = pageId;
    assert(!page->isDirty);

    return page;
}

bool BufferPoolManager::flushPage(page_id_t pageId)
{
    return false;
}

BufferPoolManager::~BufferPoolManager()
{
    delete freeList;
    delete [] pages;

}
