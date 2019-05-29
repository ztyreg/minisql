//
// Created by y on 2019-05-25.
//

#ifndef PROJECT_SQL_H
#define PROJECT_SQL_H

#include <iostream>
#include <vector>

using namespace std;

class Sql
{
private:
    vector <string> lines;
    string sql;

public:
    void addLine(string line);
    void combineLines();

    const string &getSql() const;

    friend ostream &operator<<(ostream &os, const Sql &sql);

    bool isEmpty();
};


#endif //PROJECT_SQL_H
