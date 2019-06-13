//
// Created by y on 2019-05-26.
//

#ifndef PROJECT_CREATETABLE_H
#define PROJECT_CREATETABLE_H

#include <string>
#include <vector>
#include <iostream>
#include "Command.h"
#include "../shell/DbInterface.h"

class CreateTable : public Command
{
private:
    string tableName = "";
    string primaryKey = "";
    typedef struct column_struct {
        string columnName;
        string dataType; //int, float, char
        int charLength; //0-255
        bool isUnique;
        bool isPrimaryKey;
    } column;
    vector <column> columns;

public:
    CreateTable();

    const string &getTableName() const;

    void setTableName(const string &tableName);

    const string &getPrimaryKey() const;

    void addColumn(string columnName, string dataType, int charLength, bool isUnique);

    void addPrimaryKey(string column);

    Result execute(DbInterface &db) override;

    friend ostream &operator<<(ostream &os, const CreateTable &table);


};


#endif //PROJECT_CREATETABLE_H
