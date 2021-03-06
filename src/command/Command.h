//
// Created by y on 2019-05-25.
//

#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H

#include <string>
#include <vector>
#include <iostream>
#include "Result.h"
#include "../catalog/DbInterface.h"

using namespace std;


class Command {
private:
public:
    Command();

    virtual Result execute(DbInterface &db) = 0;

    virtual ~Command();

    friend ostream &operator<<(ostream &os, const Command &command);

};

class Unknown : public Command {
public:
    Result execute(DbInterface &db) override;

};


#endif //PROJECT_COMMAND_H
