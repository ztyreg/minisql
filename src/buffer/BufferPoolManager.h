//
// Created by y on 2019-06-05.
//

#ifndef MINISQL_BUFFERPOOLMANAGER_H
#define MINISQL_BUFFERPOOLMANAGER_H

#include <list>
#include "Page.h"
#include "../disk/DiskManager.h"
#include "LruReplacer.h"

using namespace std;

class BufferPoolManager {
    friend class Page;
private:
    int poolSize;
    Page *pages;
    DiskManager *diskManager;
    LruReplacer<Page *> *replacer;



public:
    BufferPoolManager(int poolSize, DiskManager *diskManager);

    virtual ~BufferPoolManager();

    /* new page ID is stored in pageId */
    Page *newPage(page_id_t &pageId);

    bool deletePage(page_id_t pageId);

    Page *fetchPage(page_id_t pageId);

    bool flushPage(page_id_t pageId);

    list<Page *> *freeList;


};



#endif //MINISQL_BUFFERPOOLMANAGER_H
