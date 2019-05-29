//
// Created by y on 2019-05-26.
//

#ifndef PROJECT_DROPINDEX_H
#define PROJECT_DROPINDEX_H

#include <ostream>
#include "Command.h"

class DropIndex : public Command
{
private:
    string indexName;

public:
    DropIndex();

    ~DropIndex() override;

    const string &getIndexName() const;

    void setIndexName(const string &indexName);

    friend ostream &operator<<(ostream &os, const DropIndex &dropIndex);

    Result execute() override;

};


#endif //PROJECT_DROPINDEX_H
