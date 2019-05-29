//
// Created by y on 2019-05-25.
//

#include <regex>
#include "Sql.h"
#include "../util/StringUtils.h"

void Sql::addLine(string line)
{
    // delete anything after ';'
    // and remove comments
    line = line.substr(0, line.find("--", 0));
    line = line.substr(0, line.find(';', 0));
    lines.push_back(line);

}

void Sql::combineLines()
{
    sql = "";
    for (auto const& line : lines) { sql += line + " "; }
    // to lowercase
    bool inQuotes = false;
    for(char& c : sql) {
        if (c == '\'') inQuotes = !inQuotes;
        if (!inQuotes) c = (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
    }

    // surround with spaces
    sql = regex_replace(sql, regex("\\("), " ( ");
    sql = regex_replace(sql, regex("\\)"), " ) ");
    sql = regex_replace(sql, regex(","), " , ");
    sql = regex_replace(sql, regex("'"), " ' ");
    sql = regex_replace(sql, regex("<="), " @@LE ");
    sql = regex_replace(sql, regex(">="), " @@GE ");
    sql = regex_replace(sql, regex("<>"), " @@NE ");
    sql = regex_replace(sql, regex("<"), " @@LT ");
    sql = regex_replace(sql, regex(">"), " @@GT ");
    sql = regex_replace(sql, regex("="), " @@EQ ");

    // multiple spaces to single space
    sql = single_space(sql);
    trim(sql);
}

ostream &operator<<(ostream &os, const Sql &sql)
{
    os << "sql: " << sql.sql;
    return os;
}

const string &Sql::getSql() const
{
    return sql;
}

bool Sql::isEmpty()
{
    return !lines.empty();
}
