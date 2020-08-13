#include <utility>

#include <utility>
#include <iostream>
#include <time.h>

//
// Created by y on 2019-05-25.
//

#include "Command.h"

Result Unknown::execute(DbInterface &db)
{
    Result result;

    return result;
}

Command::~Command()
{
}

Command::Command()
{
}

ostream &operator<<(ostream &os, const Command &command)
{
    return os;
}
