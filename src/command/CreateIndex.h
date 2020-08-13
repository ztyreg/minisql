//
// Created by y on 2019-05-26.
//

#ifndef PROJECT_CREATEINDEX_H
#define PROJECT_CREATEINDEX_H

#include "Command.h"
#include <ostream>
#include "../buffer/IndexMetaPage.h"

class CreateIndex : public Command
{
    friend class IndexMetaPage;
private:
    string Ddl="";
    string tableName;
    string indexName;
    vector <string> columns;

public:
    CreateIndex();

    ~CreateIndex() override;

    const string &getTableName() const;

    void setTableName(const string &tableName);

    const string &getIndexName() const;

    void setIndexName(const string &indexName);

    void addColumn(string column);

    vector <string> getColumns();

    Result execute(DbInterface &db) override;

    friend ostream &operator<<(ostream &os, const CreateIndex &createIndex);

    const string &getDdl() const;

    void setDdl(const string &ddl);

};


#endif //PROJECT_CREATEINDEX_H
