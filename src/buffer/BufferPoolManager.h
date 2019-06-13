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

    /**
     * Allocate new page
     * @param pageId: stores page ID
     * @return
     */
    Page *newPage(page_id_t &pageId);

    /**
     * Deallocate page
     * @param pageId
     * @return
     */
    bool deletePage(page_id_t pageId);

    /**
     * (1) Requested page in buffer ? return page : (2) ask DiskManager
     * (2) Free frames ? random one : (3) victim
     * (3) Dirty ? write and read : read
     * @param pageId
     * @return
     */
    Page *fetchPage(page_id_t pageId);

    /**
     * Write Page object to disk
     * @param pageId
     * @return
     */
    bool flushPage(page_id_t pageId);

    list<Page *> *freeList;


};


#endif //MINISQL_BUFFERPOOLMANAGER_H
