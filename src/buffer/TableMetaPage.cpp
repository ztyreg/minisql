//
// Created by y on 2019-06-14.
//

#include "TableMetaPage.h"
#include "../command/Parser.h"
#include "../command/CreateTable.h"
#include <iostream>

void TableMetaPage::composePage(page_id_t rootId, string ddl)
{
    resetMemory();

    memcpy(data, to_string(rootId).c_str(), TABLEMETA_ID);

    const char *ddlArray = ddl.c_str();
    int ddlSize = strlen(ddlArray);
    memcpy(data+TABLEMETA_ID, to_string(ddlSize).c_str(), TABLEMETA_SIZE);

    memcpy(data+TABLEMETA_ID+TABLEMETA_SIZE, ddl.c_str(), ddlSize);

}

void TableMetaPage::parsePage()
{
    char tempId[5];
    char tempSize[5];
    char tempDdl[4096];

    memcpy(tempId, data, TABLEMETA_ID);
    memcpy(tempSize, data+TABLEMETA_ID, TABLEMETA_SIZE);
    rootId = atoi(tempId);

    int size = atoi(tempSize);
    memcpy(tempDdl, data+TABLEMETA_ID+TABLEMETA_SIZE, size);
    ddl = string(tempDdl);

    Parser parser;
    unique_ptr<Command> command = parser.parse(ddl);
    auto *meta = dynamic_cast<CreateTable *>(command.get());

    tableName = meta->tableName;
    primaryKey = meta->primaryKey;
    columns.swap(meta->columns);


}

void TableMetaPage::composePage()
{
    resetMemory();

    memcpy(data, to_string(rootId).c_str(), TABLEMETA_ID);

    const char *ddlArray = ddl.c_str();
    int ddlSize = strlen(ddlArray);
    memcpy(data+TABLEMETA_ID, to_string(ddlSize).c_str(), TABLEMETA_SIZE);

    memcpy(data+TABLEMETA_ID+TABLEMETA_SIZE, ddl.c_str(), ddlSize);

}

const string &TableMetaPage::getDdl() const
{
    return ddl;
}
