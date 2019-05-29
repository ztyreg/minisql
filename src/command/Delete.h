//
// Created by y on 2019-05-26.
//

#ifndef PROJECT_DELETE_H
#define PROJECT_DELETE_H

#include <ostream>
#include "Command.h"

class Delete : public Command
{
private:
    string tableName;
    bool deleteAll = false;
    vector <whereClause> wheres;

public:
    Delete();

    virtual ~Delete();

    const string &getTableName() const;

    void setTableName(const string &tableName);

    bool isDeleteAll() const;

    void setDeleteAll(bool deleteAll);

    void setWheres(const vector<whereClause> &wheres);

    const vector<whereClause> &getWheres() const;

    friend ostream &operator<<(ostream &os, const Delete &aDelete);

    Result execute() override;


};


#endif //PROJECT_DELETE_H
