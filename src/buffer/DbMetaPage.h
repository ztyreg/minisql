//
// Created by y on 2019-06-14.
//

#ifndef MINISQL_DBMETAPAGE_H
#define MINISQL_DBMETAPAGE_H

#include "Page.h"
#include <string>
#include <map>

using namespace std;

/**
* | HEADER (16) | record_count (4) | entry_1_name (32) | entry_1_meta_id (4) | ...
*/

class DbMetaPage : public Page {
    friend class DbInterface;

private:
    map<string, int> entries;


public:
    explicit DbMetaPage(Page const &p) : Page(p)
    {};

    virtual ~DbMetaPage();

    bool parsePage();

    void composePage();

    void addMeta(string data);

    inline int getEntryNumber()
    { return entries.size(); }

    inline bool entryExists(const string &name)
    { return entries.find(name) != entries.end(); }

};


#endif //MINISQL_DBMETAPAGE_H
