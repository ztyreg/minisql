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
    char tempCount[5];
    char tempName[33];
    char tempId[5];
    if (string(header) == "minisqlformat...") {
        cout << "Parsing db meta page ..." << endl;
        memcpy(tempCount, data+DBMETA_HEADER, DBMETA_COUNT);
        count = atoi(tempCount);
        for (int i = 0; i < count; ++i) {
            memcpy(tempName,
                    data+DBMETA_HEADER+DBMETA_COUNT+(DBMETA_NAME+DBMETA_ID)*i,
                    DBMETA_NAME);
            memcpy(tempId,
                    data+DBMETA_HEADER+DBMETA_COUNT+(DBMETA_NAME+DBMETA_ID)*i+DBMETA_NAME,
                    DBMETA_ID);
            entries.insert(make_pair(tempName, atoi(tempId)));

        }

    } else {
        //new database or corrupted file
        cout << "New db ..." << endl;
        memcpy(data, "minisqlformat...", DBMETA_HEADER);
        memcpy(data+DBMETA_HEADER, to_string(0).c_str(), DBMETA_COUNT);
        return false;

    }

    return true;
}

void DbMetaPage::composePage()
{
//    entries.insert(make_pair("takes", 4));
    resetMemory();

    memcpy(data, "minisqlformat...", DBMETA_HEADER);
    memcpy(data+DBMETA_HEADER, to_string(entries.size()).c_str(), DBMETA_COUNT);
    int j = 0;
    for (auto const &entry : entries) {
        memcpy(data+DBMETA_HEADER+DBMETA_COUNT+(DBMETA_NAME+DBMETA_ID)*j,
               entry.first.c_str(), DBMETA_NAME);
        memcpy(data+DBMETA_HEADER+DBMETA_COUNT+(DBMETA_NAME+DBMETA_ID)*j+DBMETA_NAME,
               to_string(entry.second).c_str(), DBMETA_ID);
        j++;
    }

}

void DbMetaPage::addMeta(string data)
{


}
