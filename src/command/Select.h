//
// Created by y on 2019-05-26.
//

#ifndef PROJECT_SELECT_H
#define PROJECT_SELECT_H

#include <ostream>
#include "Command.h"

class Select : public Command
{
private:
    string tableName;
    bool selectAll;
    vector<string> columnNames;
    vector <whereClause> wheres;

public:
    Select();

    virtual ~Select();

    const string &getTableName() const;

    void setTableName(const string &tableName);

    bool isSelectAll() const;

    void setSelectAll(bool selectAll);

    const vector<string> &getColumnNames() const;

    void setColumnNames(const vector<string> &columnNames);

    const vector<whereClause> &getWheres() const;

    void setWheres(const vector<whereClause> &wheres);

    friend ostream &operator<<(ostream &os, const Select &select);

    Result execute() override;

};


#endif //PROJECT_SELECT_H
