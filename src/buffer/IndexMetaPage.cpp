//
// Created by y on 2019-06-15.
//

#include "IndexMetaPage.h"
#include <iostream>
#include "../command/Parser.h"
#include "../command/CreateIndex.h"
void IndexMetaPage::composePage(page_id_t rootId, string ddl) {
    resetMemory();

    memwrite_int(data, rootId);

    const char *ddlArray = ddl.c_str();
    int ddlSize = strlen(ddlArray);
    memwrite_int(data+TABLEMETA_ID, ddlSize);

    memcpy(data+TABLEMETA_ID+TABLEMETA_SIZE, ddl.c_str(), ddlSize);


}
void IndexMetaPage::parsePage() {
    int size;
    char tempDdl[PAGE_SIZE];
    memset(tempDdl, 0, PAGE_SIZE);

    memread_int(data, (int *)(&rootId));
    memread_int(data+TABLEMETA_ID, (int *)(&size));

    memcpy(tempDdl, data+TABLEMETA_ID+TABLEMETA_SIZE, size);
    ddl = string(tempDdl);

    Parser parser;
    unique_ptr<Command> command = parser.parse(ddl);
    auto *meta = dynamic_cast<CreateIndex *>(command.get());

    indexName=meta->indexName;
}