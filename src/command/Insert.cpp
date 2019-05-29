#include <utility>

//
// Created by y on 2019-05-26.
//

#include "Insert.h"

Insert::Insert()
{}

Insert::~Insert()
{

}

const string &Insert::getTableName() const
{
    return tableName;
}

void Insert::setTableName(const string &tableName)
{
    Insert::tableName = tableName;
}

const vector<Insert::value> &Insert::getValues() const
{
    return values;
}

void Insert::addValue(string type, string field)
{
    value val;
    val.type = std::move(type);
    val.field = std::move(field);
    values.push_back(val);

}

Result Insert::execute()
{
    cout << "\texecuting insert ..." << endl;
    Result result;

    return result;

}

ostream &operator<<(ostream &os, const Insert &insert)
{
    os << "\ttableName: " << insert.tableName;
    os << " values: ";
    for (const auto &item : insert.values) {
        os << item.field << "(" << item.type << ") ";
    }
    return os;
}


