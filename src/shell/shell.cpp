#include <iostream>
#include <fstream>
#include <cassert>
#include "../command/Parser.h"
#include "../command/Command.h"
#include "../command/Result.h"
#include "../command/Sql.h"
#include "../util/StringUtils.h"
#include "../catalog/DbInterface.h"

using namespace std;


/**
 * print prompt and get SQL
 * also remove comemnts, convert multi-line SQL to single-line
 * @param cin
 * @param sql
 */
void promptAndGetSql(istream& cin, Sql& sql)
{
    string line;
    cout << "minisql> ";
    getline(cin, line);
    // remove preceding and trailing whitespaces
    trim(line);
    // all whitespaces
    if (line.empty()) return;
    // quit
    if (line == "quit") {
        cout << "Bye." << endl;
        exit(0);
    }

    sql.addLine(line);
    //TODO only after adding does the line becomes empty

    while (line.find(';') == string::npos && !cin.eof()) {
        getline(cin, line);
        sql.addLine(line);
    }

    sql.combineLines();

}

int main(int argc, char* argv[])
{
    Parser parser;
    unique_ptr<Command> command;
    cout << "Welcome to minisql shell." << endl;

    DbInterface db;
    db.init("dbfile");

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
        Sql sql;
        //input
        promptAndGetSql(cin, sql);
        cout << sql;
        //to one-line string

        vector <string> tokens = split(sql.getSql());
        if (tokens[0] == "execfile") {
            ///execfile
            if (tokens.size() == 1) cout << "Error: please specify file name!" << endl;
            else {
                cout << "Input file ... " << endl;
                ifstream infile(tokens[1]);
                while (!infile.eof()) {
                    Sql fileSql;
                    promptAndGetSql(infile, fileSql);
                    cout << fileSql;
                    //parse
                    command = parser.parse(fileSql.getSql());
                    //execute
                    Result result = command->execute(db);
                    command.reset(nullptr);
                }
            }
        } else {
            //parse
            command = parser.parse(sql.getSql());
            //execute
            Result result = command->execute(db);
            command.reset(nullptr);
        }


    }
#pragma clang diagnostic pop

    return 0;
}

