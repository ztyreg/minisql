//
// Created by y on 2019-05-26.
//

#ifndef PROJECT_DROPINDEX_H
#define PROJECT_DROPINDEX_H

#include <ostream>
#include "Command.h"
#include "../catalog/DbInterface.h"

class DropIndex : public Command
{
private:
    string indexName;
    string tableName;
public:
    DropIndex();

    ~DropIndex() override;

    const string &getIndexName() const;

    void setIndexName(const string &indexName);

    const string &getTableName() const;

    void setTableName(const string &tableName);

    friend ostream &operator<<(ostream &os, const DropIndex &dropIndex);

    Result execute(DbInterface &db) override;

};


#endif //PROJECT_DROPINDEX_H
