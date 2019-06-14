//
// Created by y on 2019-06-05.
//

#ifndef MINISQL_DISKMANAGER_H
#define MINISQL_DISKMANAGER_H

#include <string>
#include <fstream>
#include "../common/Config.h"

using namespace std;


class DiskManager {
private:
    string dbName;
    fstream dbIo;
    page_id_t nextPageId;

public:
    explicit DiskManager(const string& dbName);

    virtual ~DiskManager();

    void writePage(page_id_t pageId, const char *pageData);

    void readPage(page_id_t pageId, char *pageData);

    page_id_t allocatePage();


    int getFileSize(const std::string &file_name);

    void replacePage(page_id_t pageId, const char *pageData);
};


#endif //MINISQL_DISKMANAGER_H
