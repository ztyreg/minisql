//
// Created by lenovo on 2019/6/22.
//

#include "Data.h"
#include <iostream>

Data::Data(string value, int size) : i(0), f(0), type(size)
{
    value.resize(size);
    s = value;
};

Data::Data(int value) : i(value), f(0), s(""), type(-1)
{};

Data::Data(float value) : i(0), f(value), s(""), type(0)
{};

Data::Data(const Data &value)
{
    type = value.type;
    switch (type) {
        case -1:
            i = value.i;
            break;
        case 0:
            f = value.f;
            break;
        default:
            s = value.s;
            break;
    }
}

bool operator<(const Data &v1, const Data &v2)
{
    switch (v1.type) {
        case -1:
            return v1.i < v2.i;
        case 0:
            return v1.f < v2.f;
        default:
            return v1.s < v2.s;
    }
}

bool operator>(const Data &v1, const Data &v2)
{
    return v2 < v1;
}

bool operator>=(const Data &v1, const Data &v2)
{
    return !(v1 < v2);
}

bool operator<=(const Data &v1, const Data &v2)
{
    return !(v1 > v2);
}

bool operator==(const Data &v1, const Data &v2)
{
    return (v1 <= v2) && (v1 >= v2);
}

bool operator!=(const Data &v1, const Data &v2)
{
    return !(v1 == v2);
}

ostream &operator<<(ostream &os, const Data &v)
{
    switch (v.type) {
        case -1: {
            os << v.i;
            return os;
        }
        case 0: {
            os << v.f;
            return os;
        }
        default: {
            os << v.s;
            return os;
        }
    }
}

Data::Data() : i(0), f(0), s(), type(-2)
{}

Data::Data(string data, string type)
{
    if (type == "int") {
        this->type = -1;
        i = stoi(data);

    } else if (type == "char") {
        this->type = data.size();
        s = data;

    } else if (type == "float") {
        this->type = 0;
        f = stof(data);

    }

};
