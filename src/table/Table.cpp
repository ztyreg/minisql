#include <utility>

//
// Created by y on 2019-06-15.
//

#include "Table.h"
#include "../command/Parser.h"

Table::Table(string tableName, string ddl) : tableName(std::move(tableName))
{
    Parser parser;
//    meta = parser.parse(std::move(ddl));
}
