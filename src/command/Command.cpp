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
    end = clock();
    //time count stops 
    total_time = ((double) (end - start)) / CLK_TCK;
    cout << "Finished in " << total_time << " s" << endl;
}

Command::Command()
{
    start = clock();
}

ostream &operator<<(ostream &os, const Command &command)
{
    return os;
}
