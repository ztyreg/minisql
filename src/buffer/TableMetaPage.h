//
// Created by y on 2019-06-14.
//

#ifndef MINISQL_TABLEMETAPAGE_H
#define MINISQL_TABLEMETAPAGE_H

#include <string>
#include "Page.h"
#include "vector"

using namespace std;


/**
 * | root_id (4) | ddl_size (4) | CREATE TABLE … ;
 */
class TableMetaPage : Page {
    friend class DbInterface;
private:
    string ddl = "";
    string tableName = "";
    string primaryKey = "";
    vector<column_t> columns; //column defined in Config.h

    int tupleLength;

    page_id_t rootId;

public:
    explicit TableMetaPage(Page const& p) : Page(p) {};

    void composePage();

    void composePage(page_id_t rootId, string ddl);

    void parsePage();

    const string &getDdl() const;

    int getTupleLength() const;


};


#endif //MINISQL_TABLEMETAPAGE_H
