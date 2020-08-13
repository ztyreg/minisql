//
// Created by y on 2019-05-26.
//

#include "CreateIndex.h"

CreateIndex::CreateIndex()
{}

CreateIndex::~CreateIndex()
{

}

const string &CreateIndex::getTableName() const
{
    return tableName;
}

void CreateIndex::setTableName(const string &tableName)
{
    CreateIndex::tableName = tableName;
}

const string &CreateIndex::getIndexName() const
{
    return indexName;
}

void CreateIndex::setIndexName(const string &indexName)
{
    CreateIndex::indexName = indexName;
}

void CreateIndex::addColumn(string column)
{
    columns.push_back(column);

}

vector<string> CreateIndex::getColumns(void)
{
    return columns;
}

Result CreateIndex::execute(DbInterface &db)
{
    cout << "\texecuting create index ... " << endl;
    Result result;
    db.createIndex(tableName, columns[0], Ddl);
    return result;

}

ostream &operator<<(ostream &os, const CreateIndex &createIndex)
{
    os << "\ttableName: " << createIndex.tableName << " indexName: "
       << createIndex.indexName;
    os << " columns: ";
    for (const auto &item : createIndex.columns) {
        os << item << " ";
    }
    return os;
}

const string &CreateIndex::getDdl() const
{
    return Ddl;
}

void CreateIndex::setDdl(const string &ddl)
{
    Ddl = ddl;
}