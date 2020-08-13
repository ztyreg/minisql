//
// Created by lenovo on 2019/6/24.
//

#include "IndexManager.h"
IndexManager::IndexManager() {
    Index.clear();
}
IndexManager::~IndexManager() {};
void IndexManager::Insert(string name, Tree T) {
    if (Index.count(name))
        Index[name] = T;
    else
        Index.insert(make_pair(name, T));
}
Tree IndexManager::GetTree(string name) {
        return Index[name];
}
bool IndexManager::isExist(string name) {
    if(Index.count(name))
        return true;
    else return false;
}