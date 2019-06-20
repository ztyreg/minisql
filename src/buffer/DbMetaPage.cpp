//
// Created by y on 2019-06-14.
//

#include "DbMetaPage.h"
#include <iostream>

using namespace std;


DbMetaPage::~DbMetaPage()
{

}

/**
 * @return true if successful, false if new db
 */
bool DbMetaPage::parsePage()
{

    //check header
    char header[DBMETA_HEADER+1];
    memcpy(header, data, DBMETA_HEADER);
    memset(header + DBMETA_HEADER, 0, sizeof(char));

    int count;
    char tempName[33];
    int id;
    if (string(header) == "minisqlformat...") {
        cout << "Parsing db meta page ..." << endl;
        memread_int(data+DBMETA_HEADER, &count);
        for (int i = 0; i < count; ++i) {
            memcpy(tempName,
                    data+DBMETA_HEADER+DBMETA_COUNT+(DBMETA_NAME+DBMETA_ID)*i,
                    DBMETA_NAME);
            memread_int(data+DBMETA_HEADER+DBMETA_COUNT+(DBMETA_NAME+DBMETA_ID)*i+DBMETA_NAME,
                    &id);
            entries.insert(make_pair(tempName, id));
        }

    } else {
        //new database or corrupted file
        cout << "New db ..." << endl;
        memcpy(data, "minisqlformat...", DBMETA_HEADER);
        memwrite_int(data+DBMETA_HEADER, 0);
        return false;

    }

    return true;
}

void DbMetaPage::composePage()
{
//    entries.insert(make_pair("takes", 4));
    resetMemory();

    memcpy(data, "minisqlformat...", DBMETA_HEADER);
    memwrite_int(data+DBMETA_HEADER, entries.size());
    int j = 0;
    for (auto const &entry : entries) {
        memcpy(data+DBMETA_HEADER+DBMETA_COUNT+(DBMETA_NAME+DBMETA_ID)*j,
               entry.first.c_str(), DBMETA_NAME);
        memwrite_int(data+DBMETA_HEADER+DBMETA_COUNT+(DBMETA_NAME+DBMETA_ID)*j+DBMETA_NAME,
                entry.second);
        j++;
    }

}

void DbMetaPage::addMeta(string data)
{


}

DbMetaPage::DbMetaPage(Page *p) : Page(*p)
{

}
