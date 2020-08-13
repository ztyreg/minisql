//
// Created by y on 2019-05-26.
//

#include "Delete.h"

Delete::Delete()
{}

Delete::~Delete()
{

}

const string &Delete::getTableName() const
{
    return tableName;
}

void Delete::setTableName(const string &tableName)
{
    Delete::tableName = tableName;
}

Result Delete::execute(DbInterface &db)
{
//    cout << "\texecuting delete ..." << endl;
    Result result;
    db.deleteTuple(tableName, wheres);

    return result;
}

void Delete::setWheres(const vector<whereClause> &wheres)
{
    Delete::wheres = wheres;
}

const vector<whereClause> &Delete::getWheres() const
{
    return wheres;
}

ostream &operator<<(ostream &os, const Delete &aDelete)
{
    os << static_cast<const Command &>(aDelete) << "\ttableName: " << aDelete.tableName;
    os << " deleteAll: " << aDelete.deleteAll;
    os << " where: ";
    for (const auto &item : aDelete.wheres) {
        os << item.columnName << item.op << item.field << "(" << item.type << ") ";
    }

    return os;
}

bool Delete::isDeleteAll() const
{
    return deleteAll;
}

void Delete::setDeleteAll(bool deleteAll)
{
    Delete::deleteAll = deleteAll;
}
