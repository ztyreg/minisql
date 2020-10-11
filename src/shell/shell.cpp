#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "../command/Parser.h"
#include "../command/Command.h"
#include "../command/Result.h"
#include "../command/Sql.h"
#include "../util/StringUtils.h"
#include "../catalog/DbInterface.h"
#include "../common/Config.h"

using namespace std;

static_assert(sizeof(float) == sizeof(uint32_t), "");
static_assert(sizeof(int) == sizeof(uint32_t), "");

/**
 * print prompt and get SQL
 * also remove comemnts, convert multi-line SQL to single-line
 * @param cin
 * @param sql
 */
void promptAndGetSql(istream &cin, Sql &sql) {
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

int main(int argc, char *argv[]) {
    Parser parser;
    unique_ptr<Command> command;
    cout << "Welcome to minisql shell." << endl;

    //
    //test
    //
//    ofstream f;
//    f.open("dbfile", ios::out | ios::binary | ios::trunc);
//    f.close();
    //
    //end test
    //
    double total_time;
    clock_t start, end;

    DbInterface db;
    db.init("dbfile");

    // execute in command line
    if (argc > 1 && string(argv[1]) == "-c") {
        if (argc == 2) {
            return 0;
        }
        Sql sql;
        string line = string(argv[2]);
        sql.addLine(line);
        sql.combineLines();
        command = parser.parse(sql.getSql());
        Result result = command->execute(db);
        command.reset(nullptr);
        return 0;
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
        Sql sql;
        //input
        promptAndGetSql(cin, sql);
//        cout << sql;
        //to one-line string

        vector<string> tokens = split(sql.getSql());
        if (tokens[0] == "execfile") {
            ///execfile
            if (tokens.size() == 1) cout << "Error: please specify file name!" << endl;
            else {
                cout << "Input file ... " << endl;
                ifstream infile(tokens[1]);
                while (!infile.eof()) {
                    //time
                    start = clock();
                    Sql fileSql;
                    promptAndGetSql(infile, fileSql);
                    cout << fileSql.getSql() << endl;
                    ///parse
                    command = parser.parse(fileSql.getSql());
                    ///execute
                    Result result = command->execute(db);
                    command.reset(nullptr);
                    //time
                    end = clock();
                    total_time = ((double) (end - start));
                    cout << "[" << "Finished in " << total_time << "]" << endl;
                }
            }
        } else {
            //time
            start = clock();
            ///parse
            command = parser.parse(sql.getSql());
            ///execute
            Result result = command->execute(db);
            command.reset(nullptr);
            //time
            end = clock();
            total_time = ((double) (end - start));
            cout << "[" << "Finished in " << total_time << "]" << endl;
        }


    }
#pragma clang diagnostic pop

    return 0;
}

