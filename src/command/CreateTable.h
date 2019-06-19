//
// Created by y on 2019-05-26.
//

#ifndef PROJECT_CREATETABLE_H
#define PROJECT_CREATETABLE_H

#include <string>
#include <vector>
#include <iostream>
#include "Command.h"
#include "../catalog/DbInterface.h"

class CreateTable : public Command {
    friend class TableMetaPage;
private:
    string Ddl = "";
    string tableName = "";
    string primaryKey = "";
    vector<column_t> columns; //column defined in Config.h

public:
    CreateTable();

    const string &getDdl() const;

    void setDdl(const string &ddl);

    const string &getTableName() const;

    void setTableName(const string &tableName);

    const string &getPrimaryKey() const;

    void addColumn(string columnName, string dataType, int charLength, bool isUnique);

    void addPrimaryKey(string column);

    Result execute(DbInterface &db) override;

    friend ostream &operator<<(ostream &os, const CreateTable &table);


};


#endif //PROJECT_CREATETABLE_H
