//
// Created by y on 2019-06-05.
//

#include "BufferPoolManager.h"
#include <iostream>
#include <cassert>

char TEST_CHAR[4096];

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
        if (TRACKBUFFER) cout << "\tBuffer: new page (free list)" << endl;
        page = freeList->front();
        freeList->pop_front();
    } else {
        /* find a victim */
        if (TRACKBUFFER) cout << "\tBuffer: new page (replace)" << endl;
        if (!replacer->victim(page)) {
            return nullptr;
        }
        if (TRACKBUFFER) cout << "\tBuffer: victim page is #" << page->pageId << endl;
        if (page->isDirty) {
            diskManager->writePage(page->pageId, page->data);
            page->isDirty = false;
        }

        pageTable.erase(page->getPageId());

    }

    pageId = diskManager->allocatePage();
    if (TRACKBUFFER) cout << "\tBuffer: new page #" << pageId << endl;

    page->pageId = pageId;
    page->isDirty = true;
    page->resetMemory();
    pageTable[pageId] = page;
    if (DEBUG) cout << "DEBUG: #" << pageId << " " << page << endl;
    replacer->insert(page);

    if (DEBUG) cout << "DEBUG: page table size: " << pageTable.size() << endl;

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
        if (TRACKBUFFER) cout << "\tBuffer: fetched page #" << pageId << " (page table)" << endl;
        page = pageTable[pageId];
        replacer->insert(page);
        return page;
    }


    if (freeList->empty()) {
        // use replacer
        if (TRACKBUFFER) cout << "\tBuffer: fetched page #" << pageId << " (replace)" << endl;
        if (!replacer->victim(page)) {
            return nullptr;
        }
        if (TRACKBUFFER) cout << "\tBuffer: found victim page #" << page->pageId << endl;
        if (page->isDirty) {
            diskManager->writePage(page->pageId, page->data);
            page->isDirty = false;
        }

        pageTable.erase(page->getPageId());

        // flush dirty page

    } else {
        // fetch from free list
        if (TRACKBUFFER) cout << "\tBuffer: fetched page #" << pageId << " (free list)" << endl;
        page = freeList->front();
        freeList->pop_front();
    }

    //retrieve the physical page
    if (TRACKBUFFER) cout << "\tBuffer: retrieving physical page #" << pageId << " ..." << endl;
    diskManager->readPage(pageId, page->data);
    page->pageId = pageId;
    replacer->insert(page);
    assert(!page->isDirty);

    return page;
}

bool BufferPoolManager::flushPage(page_id_t pageId)
{
    if (pageTable.find(pageId) == pageTable.end()) {
        return false;
    }
    Page *page = pageTable[pageId];

    diskManager->writePage(page->pageId, page->data);
    page->isDirty = false;
    if (TRACKBUFFER) cout << "\tBuffer: flushed page #" << pageId << endl;
    return false;
}

BufferPoolManager::~BufferPoolManager()
{
    delete replacer;
    delete freeList;
    delete [] pages;

}
