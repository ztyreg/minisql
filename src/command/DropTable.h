//
// Created by y on 2019-05-26.
//

#ifndef PROJECT_DROPTABLE_H
#define PROJECT_DROPTABLE_H

#include <string>
#include <ostream>
#include "Command.h"

using namespace std;

class DropTable : public Command
{
private:
    string tableName;
public:
    DropTable();

    const string &getTableName() const;

    void setTableName(const string &tableName);

    Result execute() override;

    friend ostream &operator<<(ostream &os, const DropTable &table);

};


#endif //PROJECT_DROPTABLE_H
