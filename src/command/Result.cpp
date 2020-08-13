//
// Created by y on 2019-05-25.
//

#include "Result.h"
#include <iostream>
using namespace std;

void Result::setTuples(const vector<vector<string>> &tuples)
{
    Result::tuples = tuples;
}

void Result::printTuples()
{
    for (const auto &item : tuples) {
        for (const auto &item1 : item) {
            cout << item1 << " ";
        }
        cout << endl;
    }

}
