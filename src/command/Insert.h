//
// Created by y on 2019-05-26.
//

#ifndef PROJECT_INSERT_H
#define PROJECT_INSERT_H

#include <ostream>
#include "Command.h"
#include "../catalog/DbInterface.h"

class Insert : public Command
{
private:
    string tableName;
    typedef struct {
        string type;
        string field;
    } value;

    vector <value> values;

public:
    Insert();

    ~Insert() override;

    const string &getTableName() const;

    void setTableName(const string &tableName);

    void addValue(string type, string field);

    const vector<value> &getValues() const;

    friend ostream &operator<<(ostream &os, const Insert &insert);

    Result execute(DbInterface &db) override;

};


#endif //PROJECT_INSERT_H
