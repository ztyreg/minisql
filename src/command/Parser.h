//
// Created by y on 2019-05-25.
//

#ifndef PROJECT_PARSER_H
#define PROJECT_PARSER_H

#include "Command.h"
#include <string>
#include <iostream>

using namespace std;

class Parser
{
public:
    unique_ptr<Command> parse(string sqlString);
    vector <whereClause> parseWhere(vector <string> tokens);
    vector <string> getCommaSeparatedFields(vector <string>& tokens);

};


#endif //PROJECT_PARSER_H
