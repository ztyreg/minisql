//
// Created by y on 2019-06-05.
//

#ifndef MINISQL_LRUREPLACER_H
#define MINISQL_LRUREPLACER_H

#include <vector>

using namespace std;

template <class T>
class LruReplacer {
private:
    vector<pair<T, int> > tracker;
    int lruNo = 0;

public:
    LruReplacer();

    virtual ~LruReplacer();

    void insert(const T &value);

    bool victim(T &value);

    bool erase(const T &value);

    int size();

    const vector<pair<T, int>> &getTracker() const;

};


#endif //MINISQL_LRUREPLACER_H
