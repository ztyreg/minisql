//
// Created by y on 2019-06-14.
//

#include "TableMetaPage.h"
#include <iostream>

void TableMetaPage::composePage(page_id_t rootId, string ddl)
{
    cout << rootId << ddl << endl;
    memcpy(data, to_string(rootId).c_str(), TABLEMETA_ID);

    const char *ddlArray = ddl.c_str();
    int ddlSize = strlen(ddlArray);
    memcpy(data+TABLEMETA_ID, to_string(ddlSize).c_str(), TABLEMETA_SIZE);

    memcpy(data+TABLEMETA_ID+TABLEMETA_SIZE, ddl.c_str(), ddlSize);

    cout << "Meta data: " << data << endl;

}
