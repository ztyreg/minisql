//
// Created by lenovo on 2019/6/24.
//

#ifndef FINISHED_INDEX_INDEXMANAGER_H
#define FINISHED_INDEX_INDEXMANAGER_H

#include "BTree.h"

class IndexManager {
private:
    map<string,Tree> Index;
public:

    IndexManager();
    ~IndexManager();
    void Insert(string name,Tree T);
    Tree GetTree(string name);
    bool isExist(string name);
};


#endif //FINISHED_INDEX_INDEXMANAGER_H
