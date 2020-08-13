//
// Created by y on 2019-05-25.
//

#include <vector>
#include "Parser.h"
#include "Command.h"
#include "CreateTable.h"
#include "DropTable.h"
#include "CreateIndex.h"
#include "DropIndex.h"
#include "Insert.h"
#include "Select.h"
#include "Delete.h"
#include "../util/StringUtils.h"

/**
 * parse sql
 * @param sqlString lowercase, trimmed, tokens are separated by single spaces
 * @return pointer to command
 */
unique_ptr<Command> Parser::parse(string sqlString)
{
    if (TRACKPARSE) cout << "\tBegin parsing ... ";
    if (TRACKPARSE) cout << sqlString;

    vector <string> tokens = split(sqlString);
    if (TRACKPARSE) cout << "\tTokens ... ";
    if (TRACKPARSE) for (const auto &item : tokens) { cout << item << "+"; }
    if (TRACKPARSE) cout << endl;

    try {
        if (tokens[0] == "create" && tokens[1] == "table") {
            ///create table
            auto * createTable = new CreateTable;
            createTable->setDdl(sqlString);
            createTable->setTableName(tokens[2]);
            if (tokens[3] != "(") throw runtime_error("Syntax error!");

            int pos = 4;
            string columnName;
            string dataType;
            int charLength;
            bool isUnique;
            bool onlyOnePrimaryKey = false;
            // column end with comma: continue
            // column end with parentheses: end
            while (true) {
                if (tokens[pos] == ")" || tokens[pos] == ",") throw runtime_error("Syntax error!");
                else if (tokens[pos] == "primary") {
                    if (onlyOnePrimaryKey) throw runtime_error("Syntax error: multiple primary key");
                    if (tokens[pos+1] == "key" || tokens[pos+2] == "(" ||
                            tokens[pos+4] == ")" ) {
                        createTable->addPrimaryKey(tokens[pos+3]);
                        pos += 5;
                        onlyOnePrimaryKey = true;
                    } else {
                        throw runtime_error("Syntax error: primary key error");
                    }

                } else {
                    columnName = tokens[pos++];
                    dataType = tokens[pos++]; //type check is performed in addColumn

                    if (dataType == "char") {
                        if (tokens[pos++] != "(") throw runtime_error("Syntax error!");
                        charLength = stoi(tokens[pos++]);
                        if (tokens[pos++] != ")") throw runtime_error("Syntax error!");

                    } else if (dataType == "int" || dataType == "float") {
                        charLength = -1;
                    } else {
                        throw runtime_error("Syntax error: unsupported type");
                    }

                    isUnique = tokens[pos] == "unique";
                    if (isUnique) pos++;

                    createTable->addColumn(columnName, dataType, charLength, isUnique);

                }

                if (tokens[pos] == ")") break;
                else if (tokens[pos++] != ",") throw runtime_error("Syntax error!");
            }
            if (TRACKPARSE) cout << *createTable << endl;
            return unique_ptr<Command>(createTable);

        } else if (tokens[0] == "drop" && tokens[1] == "table") {
            ///drop table
            auto * dropTable = new DropTable;
            if (tokens.size() != 3) throw runtime_error("Syntax error!");

            dropTable->setTableName(tokens[2]);

            cout << *dropTable << endl;
            return unique_ptr<Command>(dropTable);

        } else if (tokens[0] == "create" && tokens[1] == "index" && tokens[3] == "on") {
            ///create index
            auto * createIndex = new CreateIndex;
            if (tokens[5] != "(" || tokens[tokens.size() - 1] != ")")
                throw runtime_error("Syntax error!");
            createIndex->setDdl(sqlString);
            createIndex->setIndexName(tokens[2]);
            createIndex->setTableName(tokens[4]);

            int pos = 6;
            while (true) {
                if (tokens[pos] == ")" || tokens[pos] == ",") throw runtime_error("Syntax error!");
                createIndex->addColumn(tokens[pos++]);

                if (tokens[pos] == ")") break;
                else if (tokens[pos++] != ",") throw runtime_error("Syntax error!");
            }

            if (TRACKPARSE) cout << *createIndex << endl;
            return unique_ptr<Command>(createIndex);

        } else if (tokens[0] == "drop" && tokens[1] == "index") {
            ///drop index
            auto * dropIndex = new DropIndex;
            if (tokens.size() != 5) throw runtime_error("Syntax error!");

            dropIndex->setIndexName(tokens[2]);
            dropIndex->setTableName(tokens[4]);
            if (TRACKPARSE) cout << *dropIndex << endl;
            return unique_ptr<Command>(dropIndex);

        } else if (tokens[0] == "insert" && tokens[1] == "into" && tokens[3] == "values") {
            ///insert
            auto * insert = new Insert;
            if (tokens[4] != "(" || tokens[tokens.size() - 1] != ")")
                throw runtime_error("Syntax error!");

            insert->setTableName(tokens[2]);

            int pos = 5;
            while (true) {
                if (tokens[pos] == ")" || tokens[pos] == ",") throw runtime_error("Syntax error!");

                string field;
                string type;
                //TODO quote error handling
                if (tokens[pos] == "'" || tokens[pos] == "’") {
                    while (tokens[++pos] != "'" || tokens[pos] == "’") {
                        field += tokens[pos];
                    }
                    type = "char";
                } else {
                    field = tokens[pos];
                    if (tokens[pos].find('.') != string::npos) {
                        type = "float";
                    } else {
                        type = "int";
                    }
                }
                pos++;

                insert->addValue(type, field);

                if (tokens[pos] == ")") break;
                else if (tokens[pos++] != ",") throw runtime_error("Syntax error!");
            }

            if (TRACKPARSE) cout << *insert << endl;
            return unique_ptr<Command>(insert);

        } else if (tokens[0] == "delete" && tokens[1] == "from") {
            ///delete
            auto * del = new Delete;

            del->setTableName(tokens[2]);
            if (tokens.size() == 3) {
                del->setDeleteAll(true);
                cout << *del << endl;
                return unique_ptr<Command>(del);
            }
            if (tokens[3] != "where") throw runtime_error("Syntax error!");

            tokens.erase(tokens.begin(), tokens.begin() + 4);
            del->setWheres(parseWhere(tokens));

            if (TRACKPARSE) cout << *del << endl;
            return unique_ptr<Command>(del);

        } else if (tokens[0] == "select") {
            ///select
            auto * select = new Select;
            bool selectAll;

            selectAll = tokens[1] == "*";
            if (!selectAll) {
                tokens.erase(tokens.begin());
                select->setColumnNames(getCommaSeparatedFields(tokens));
            } else {
                tokens.erase(tokens.begin(), tokens.begin() + 2);
            }
            select->setSelectAll(selectAll);

            if (tokens[0] != "from") throw runtime_error("Syntax error!");
            select->setTableName(tokens[1]);
            tokens.erase(tokens.begin(), tokens.begin() + 2);

            //(where) clause begins here
            if (!tokens.empty()) {
                if (tokens[0] != "where") throw runtime_error("Syntax error!");
                else {
                    tokens.erase(tokens.begin());
                    select->setWheres(parseWhere(tokens));
                }
            }

            if (TRACKPARSE) cout << *select << endl;
            return unique_ptr<Command>(select);

        } else {
        }
    } catch (...) {
        cerr << "Syntax error!" << endl;
    }


    return unique_ptr<Command>(new Unknown);

}

vector <whereClause> Parser::parseWhere(vector<string> tokens)
{
    vector <whereClause> wheres;

    try {
        int pos = 0;
        while (true) {
            whereClause where;
            where.columnName = tokens[pos++];

            if (tokens[pos] == "@@LT") where.op = "LT";
            else if (tokens[pos] == "@@GT") where.op = "GT";
            else if (tokens[pos] == "@@LE") where.op = "LE";
            else if (tokens[pos] == "@@GE") where.op = "GE";
            else if (tokens[pos] == "@@EQ") where.op = "EQ";
            else if (tokens[pos] == "@@NE") where.op = "NE";
            pos++;

            string field;
            string type;
            if (tokens[pos] == "'" || tokens[pos] == "’") {
                while (tokens[++pos] != "'" || tokens[pos] == "’") {
                    field += tokens[pos];
                }
                type = "char";
            } else {
                field = tokens[pos];
                if (tokens[pos].find('.') != string::npos) {
                    type = "float";
                } else {
                    type = "int";
                }
            }
            pos++;

            where.field = field;
            where.type = type;

            wheres.push_back(where);
            if (pos == tokens.size()) break;
            if (tokens[pos++] != "and") throw runtime_error("Syntax error!");

        }
    } catch(...) {
        throw runtime_error("Syntax error!");
    }

    return wheres;
}

/**
 * get comma separated fields and erase them
 * @param tokens
 * @return
 */
vector<string> Parser::getCommaSeparatedFields(vector<string>& tokens)
{
    vector<string> fields;

    try {
        bool shouldBeComma = false;
        int eraseCount = 0;
        for (const auto &item : tokens) {
            if (!shouldBeComma) fields.push_back(item);
            else if (item != ",") break;
            // erase
            eraseCount++;

            shouldBeComma = !shouldBeComma;
        }

        tokens.erase(tokens.begin(), tokens.begin() + eraseCount);
    } catch(...) {
        throw runtime_error("Syntax error!");
    }
    return fields;
}


