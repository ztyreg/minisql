//
// Created by y on 2019-05-26.
//

#include "CreateTable.h"
#include "../table/TableHeap.h"

const string &CreateTable::getTableName() const
{
    return tableName;
}

void CreateTable::setTableName(const string &tableName)
{
    CreateTable::tableName = tableName;
}

const string &CreateTable::getPrimaryKey() const
{
    return primaryKey;
}

void CreateTable::addColumn(string columnName, string dataType, int charLength, bool isUnique)
{
    column_t col;
    //pass by value, so use move
    col.columnName = std::move(columnName);
    col.dataType = std::move(dataType);
    col.charLength = charLength;
    col.isUnique = isUnique;
    col.isPrimaryKey = false;

    columns.push_back(col);
}

ostream &operator<<(ostream &os, const CreateTable &table)
{
    os << "\ttableName: " << table.tableName << " primaryKey: "
       << table.primaryKey;
    os << " columns: ";
    for (const auto &item : table.columns) {
        if (item.dataType == "char") {
            os << item.columnName << "(" << item.dataType << "[" << item.charLength << "])";
        } else {
            os << item.columnName << "(" << item.dataType << ")";
        }
        os << (item.isUnique ? "U" : "");
        os << (item.isPrimaryKey ? "P" : "");
        os << " ";
    }
    return os;
}

void CreateTable::addPrimaryKey(string column)
{
    bool found = false;
    for (auto &item : columns) {
        if (item.columnName == column) {
            found = true;
            item.isPrimaryKey = true;
        }
    }
    if (!found) throw "Syntax error: invalid primary key";
    primaryKey = column;

}

Result CreateTable::execute(DbInterface &db)
{
    cout << "EXECUTING CREATE TABLE ... " << endl;
    Result result;


    // store DDL as metadata
    db.writeTableMeta(tableName, getDdl());

    return result;

}

CreateTable::CreateTable()
{}

const string &CreateTable::getDdl() const
{
    return Ddl;
}

void CreateTable::setDdl(const string &ddl)
{
    Ddl = ddl;
}


