//
// Created by lenovo on 2019/6/22.
//

#ifndef FINISHED_SELECT_ALL_DATA_H
#define FINISHED_SELECT_ALL_DATA_H


#include <string>

using namespace std;

class Data {
    // int -1
    // float 0
    // string  length
public:
    int type;
    int i;
    float f;
    string s;

    Data();

    Data(int value);

    Data(float value);

    Data(string value, int size);

    Data(const Data &value);

    Data(string data, string type);
};

bool operator<(const Data &v1, const Data &v2);

bool operator>(const Data &v1, const Data &v2);

bool operator<=(const Data &v1, const Data &v2);

bool operator>=(const Data &v1, const Data &v2);

bool operator==(const Data &v1, const Data &v2);

bool operator!=(const Data &v1, const Data &v2);

ostream &operator<<(ostream &os, const Data &v);


#endif //FINISHED_SELECT_ALL_DATA_H
