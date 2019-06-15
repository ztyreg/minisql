//
// Created by y on 2019-06-05.
//

#include <sys/stat.h>
#include <iostream>
#include "DiskManager.h"
#include "../common/Config.h"

DiskManager::DiskManager(const string& dbName) : dbName(dbName), nextPageId(0)
{
    setNextPageId();
    dbIo.open(dbName, ios::binary | ios::in | ios::app | ios::out);
    // not exists
    if (!dbIo.is_open()) {
        dbIo.clear();
        // new file
        dbIo.open(dbName, ios::binary | ios::trunc | ios::out);
        dbIo.close();
        // reopen
        dbIo.open(dbName, ios::binary | ios::in | ios::app | ios::out);
    }
}

DiskManager::~DiskManager()
{
    dbIo.close();
}

void DiskManager::clearFile()
{
    dbIo.close();
    dbIo.open(dbName, ios::binary | ios::trunc | ios::out);
    dbIo.close();
}

void DiskManager::writePage(page_id_t pageId, const char *pageData)
{
    dbIo.close();
    dbIo.open(dbName, ios::binary | ios::in | ios::app | ios::out);

    int offset = pageId * PAGE_SIZE;
    dbIo.seekp(offset);
    dbIo.write(pageData, PAGE_SIZE);
    // I/O error
    if (dbIo.bad()) {
        cerr << "I/O error while writing" << endl;
        return;
    }
    dbIo.flush();

}

void DiskManager::readPage(page_id_t pageId, char *pageData)
{
    int offset = pageId * PAGE_SIZE;
    // check if read beyond file length
    if (offset > getFileSize(dbName)) {
        cerr << "I/O error while reading" << endl;
    } else {
        dbIo.seekp(offset);
        dbIo.read(pageData, PAGE_SIZE);
        int readCount = dbIo.gcount();
        if (readCount < PAGE_SIZE) {
            //not a complete page
            memset(pageData + readCount, 0, PAGE_SIZE - readCount);
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

void DiskManager::setNextPageId()
{
    if (getFileSize(dbName) % PAGE_SIZE != 0)
        cerr << "Corrupt db file!" << endl;

    nextPageId = getFileSize(dbName)/PAGE_SIZE;
    // skip page 0
    if (nextPageId == 0) nextPageId++;
    cout << "File size: " << getFileSize(dbName) << endl;
    cout << "Opened db. Next page ID: " << nextPageId << endl;
}
