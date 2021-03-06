//
// Created by y on 2019-05-26.
//

#include "DropTable.h"

const string &DropTable::getTableName() const
{
    return tableName;
}

void DropTable::setTableName(const string &tableName)
{
    DropTable::tableName = tableName;
}

Result DropTable::execute(DbInterface &db)
{
    cout << "executing drop table ... " << endl;
    Result result;

    db.deleteTableMeta(tableName);

    return result;

}

ostream &operator<<(ostream &os, const DropTable &table)
{
    os << "\ttableName: " << table.tableName;
    return os;
}

DropTable::DropTable()
{}
