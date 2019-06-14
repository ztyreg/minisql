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
* Format (size in byte):
*  -----------------------------------------------------------------
* | RecordCount (4) | Entry_1 name (32) | Entry_1 root_id (4) | ... |
*  -----------------------------------------------------------------
*/

class DbMetaPage : public Page {
private:
    map<string, int> entries;


public:
    explicit DbMetaPage(Page const& p) : Page(p) {};

    virtual ~DbMetaPage();

    void parsePage();

    void composePage();

    void addMeta(string data);

};


#endif //MINISQL_DBMETAPAGE_H
