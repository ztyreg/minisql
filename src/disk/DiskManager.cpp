//
// Created by y on 2019-06-05.
//

#include <sys/stat.h>
#include "DiskManager.h"
#include "../common/config.h"

DiskManager::DiskManager(const string &dbName) : dbName(dbName), nextPageId(0)
{
    dbIo.open(dbName, ios::binary | ios::in | ios::app | ios::out);
    // not exists
    if (!dbIo.is_open()) {
        dbIo.clear();
        // new file
        dbIo.open(dbName, ios::binary | ios::trunc | ios::out);
        dbIo.close();
        // reopen
        dbIo.open(dbName, ios::binary | ios::in | ios::out);
    }
}

DiskManager::~DiskManager()
{
    dbIo.close();
}

void DiskManager::writePage(page_id_t pageId, const char *pageData)
{
    int offset = pageId * PAGE_SIZE;
    dbIo.seekp(offset);
    dbIo.write(pageData, PAGE_SIZE);
    // I/O error
    if (dbIo.bad()) {
        throw runtime_error("I/O error while writing!");
    }
    dbIo.flush();

}

void DiskManager::readPage(page_id_t pageId, char *pageData)
{
    int offset = pageId * PAGE_SIZE;
    char *tempData = nullptr;
    // check if read beyond file length
    if (offset > getFileSize(dbName)) {
        throw runtime_error("I/O error while writing!");
    } else {
        dbIo.seekp(offset);
        dbIo.read(tempData, PAGE_SIZE);
        int readCount = dbIo.gcount();
        if (readCount < PAGE_SIZE) {
            memset(pageData + readCount, 0, PAGE_SIZE - readCount);
            throw runtime_error("I/O error while reading (debugged)!");
        }
    }

}

int DiskManager::getFileSize(const std::string &file_name)
{
    struct stat statBuf{};
    int rc = stat(dbName.c_str(), &statBuf);
    return rc == 0 ? statBuf.st_size : -1;
}

page_id_t DiskManager::allocatePage()
{
    return nextPageId++;
}
