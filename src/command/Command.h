//
// Created by y on 2019-05-25.
//

#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H

#include <string>
#include <vector>
#include <iostream>
#include "Result.h"
#include "../shell/DbInterface.h"

using namespace std;

typedef struct whereType {
    string columnName;
    string op;
    string field;
    string type;
} whereClause;

class Command
{
private:
    double total_time;
    clock_t start, end;
public:
    Command();

    virtual Result execute(DbInterface &db) = 0;

    virtual ~Command();

    friend ostream &operator<<(ostream &os, const Command &command);

};

class Unknown : public Command
{
public:
    Result execute(DbInterface &db) override;

};


#endif //PROJECT_COMMAND_H
