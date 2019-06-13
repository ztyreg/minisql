//
// Created by y on 2019-06-05.
//

#include "LruReplacer.h"
#include "Page.h"

template<class T>
LruReplacer<T>::LruReplacer()
{

}

template<class T>
LruReplacer<T>::~LruReplacer()
{

}

template<class T>
void LruReplacer<T>::insert(const T &value)
{
    // starting from 0
    tracker.push_back(make_pair(value, lruNo++));
}

template<class T>
bool LruReplacer<T>::victim(T &value)
{
    if (size() == 0) return false;

    int index = 0;
    int no = lruNo;
    for (int i = 0; i < size(); i++) {
        if (tracker[i].second < no) {
            no = tracker[i].second;
            index = i;
        }
    }

    value = tracker[index].first;
    tracker.erase(tracker.begin() + index);
    return true;
}

template<class T>
bool LruReplacer<T>::erase(const T &value)
{
    if (size() == 0) return false;

    bool found = false;
    int index = 0;
    for (int i = 0; i < size(); i++) {
        // equals
        if (tracker[i].first == value) {
            found = true;
            index = i;
        }
    }

    if (found)
        tracker.erase(tracker.begin() + index);

    return found;
}

template<class T>
int LruReplacer<T>::size()
{
    return tracker.size();
}

template<class T>
const vector<pair<T, int>> &LruReplacer<T>::getTracker() const
{
    return tracker;
}

// specialization
template
class LruReplacer<int>;

template
class LruReplacer<Page *>;

