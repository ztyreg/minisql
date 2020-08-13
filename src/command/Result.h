//
// Created by y on 2019-05-25.
//

#ifndef PROJECT_RESULT_H
#define PROJECT_RESULT_H

#include <vector>
#include <string>

using namespace std;

class Result
{
private:
    vector<vector<string>> tuples;
    string message;
public:
    void setTuples(const vector<vector<string>> &tuples);

    void printTuples();
};


#endif //PROJECT_RESULT_H
