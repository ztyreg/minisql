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

    memwrite_int(data, rootId);

    const char *ddlArray = ddl.c_str();
    int ddlSize = strlen(ddlArray);
    memwrite_int(data+TABLEMETA_ID, ddlSize);

    memcpy(data+TABLEMETA_ID+TABLEMETA_SIZE, ddl.c_str(), ddlSize);

}

void TableMetaPage::parsePage()
{
    if (DEBUG) cout << strcmp(TEST_CHAR, data) << endl;
    int size;
    char tempDdl[PAGE_SIZE];
    memset(tempDdl, 0, PAGE_SIZE);

    memread_int(data, (int *)(&rootId));
    memread_int(data+TABLEMETA_ID, (int *)(&size));

    memcpy(tempDdl, data+TABLEMETA_ID+TABLEMETA_SIZE, size);
    ddl = string(tempDdl);

    Parser parser;
    unique_ptr<Command> command = parser.parse(ddl);
    auto *meta = dynamic_cast<CreateTable *>(command.get());

    tableName = meta->tableName;
    primaryKey = meta->primaryKey;
    columns.swap(meta->columns);

    tupleLength = 0;
    for (const auto &item : columns) {
        if (item.dataType == "int") {
            tupleLength += 4;

        } else if (item.dataType == "float") {
            tupleLength += 4;

        } else if (item.dataType == "char") {
            tupleLength += item.charLength;

        }


    }

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

int TableMetaPage::getTupleLength() const
{
    return tupleLength;
}

int TableMetaPage::calMaxNumOfTuples()
{
    return (PAGE_SIZE-TABLE_ID-TABLE_PREVID-TABLE_NEXTID-
    TABLEMETA_SIZE-TABLE_COUNT)/tupleLength;
}

page_id_t TableMetaPage::getRootId() const
{
    return rootId;
}

TableMetaPage::TableMetaPage(Page *p) : Page(*p)
{
}


