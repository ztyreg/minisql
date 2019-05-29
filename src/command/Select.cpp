//
// Created by y on 2019-05-26.
//

#include "Select.h"

Select::Select()
{}

Select::~Select()
{

}

const string &Select::getTableName() const
{
    return tableName;
}

void Select::setTableName(const string &tableName)
{
    Select::tableName = tableName;
}

bool Select::isSelectAll() const
{
    return selectAll;
}

void Select::setSelectAll(bool selectAll)
{
    Select::selectAll = selectAll;
}

Result Select::execute()
{
    cout << "\texecuting select ..." << endl;
    return Result();
}

const vector<whereClause> &Select::getWheres() const
{
    return wheres;
}

void Select::setWheres(const vector<whereClause> &wheres)
{
    Select::wheres = wheres;
}

const vector<string> &Select::getColumnNames() const
{
    return columnNames;
}

void Select::setColumnNames(const vector<string> &columnNames)
{
    Select::columnNames = columnNames;
}

ostream &operator<<(ostream &os, const Select &select)
{
    os << static_cast<const Command &>(select) << "\ttableName: " << select.tableName << " selectAll: "
       << select.selectAll << " columNames: ";
    for (const auto &item : select.columnNames) {
        os << item << ",";
    }
    os << " where: ";
    for (const auto &item : select.wheres) {
        os << item.columnName << item.op << item.field << "(" << item.type << ") ";
    }
    return os;
}
