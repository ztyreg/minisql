//
// Created by y on 2019-06-13.
//

#include "DbInterface.h"
#include "../common/Config.h"

void DbInterface::init(string name)
{
    diskManager = new DiskManager(name);

}

DbInterface::~DbInterface()
{
    delete diskManager;

}

DbInterface::DbInterface()
{

}

void DbInterface::writeData(string tableName, string data)
{
    char test[PAGE_SIZE] = "write test";
    diskManager->writePage(0, test);

}
