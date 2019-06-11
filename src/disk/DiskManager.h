//
// Created by y on 2019-06-05.
//

#ifndef MINISQL_DISKMANAGER_H
#define MINISQL_DISKMANAGER_H

#include <string>
#include <fstream>

using namespace std;

typedef uint32_t page_id_t;

class DiskManager {
private:
    string dbName;
    fstream dbIo;
    page_id_t nextPageId;

public:
    DiskManager(const string &dbName);

    virtual ~DiskManager();

    void writePage(page_id_t pageId, const char *pageData);

    void readPage(page_id_t pageId, char *pageData);

    page_id_t allocatePage();


    int getFileSize(const std::string &file_name);
};


#endif //MINISQL_DISKMANAGER_H
