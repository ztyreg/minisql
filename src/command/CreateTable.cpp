//
// Created by y on 2019-05-26.
//

#include "CreateTable.h"

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
    column col;
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

Result CreateTable::execute()
{
    cout << "\texecuting create table ... " << endl;
    Result result;

    return result;

}

CreateTable::CreateTable()
{}


