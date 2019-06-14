//
// Created by y on 2019-06-14.
//

#ifndef MINISQL_DBMETAPAGE_H
#define MINISQL_DBMETAPAGE_H

#include "Page.h"

/**
* Format (size in byte):
*  -----------------------------------------------------------------
* | RecordCount (4) | Entry_1 name (32) | Entry_1 root_id (4) | ... |
*  -----------------------------------------------------------------
*/

class DbMetaPage : public Page {
private:
    int recordCount;

public:
    DbMetaPage(int recordCount);

    virtual ~DbMetaPage();

    void parsePage();

};


#endif //MINISQL_DBMETAPAGE_H
