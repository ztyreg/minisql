//
// Created by y on 2019-05-26.
//

#include "DropIndex.h"

DropIndex::DropIndex()
{}

DropIndex::~DropIndex()
{

}

const string &DropIndex::getIndexName() const
{
    return indexName;
}

void DropIndex::setIndexName(const string &indexName)
{
    DropIndex::indexName = indexName;
}

const string &DropIndex::getTableName()  const {
    return tableName;
}

void DropIndex::setTableName(const string &tableName) {
    this->tableName=tableName;
}



ostream &operator<<(ostream &os, const DropIndex &dropIndex)
{
    os << "\tindexName: " << dropIndex.indexName;
    return os;
}

Result DropIndex::execute(DbInterface &db)
{
    cout << "\texecuting drop index ... " << endl;
    Result result;
    db.deleteIndexMeta(tableName,indexName);
    return result;

}
