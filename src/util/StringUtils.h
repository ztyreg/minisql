//
// Created by y on 2019-05-25.
//

#ifndef PROJECT_STRINGUTILS_H
#define PROJECT_STRINGUTILS_H

#include <algorithm>
#include <cctype>
#include <locale>

void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s);
std::string ltrim_copy(std::string s);
std::string rtrim_copy(std::string s);
std::string trim_copy(std::string s);
std::vector<std::string> split(const std::string& subject);
std::string single_space(std::string const &input);
#endif //PROJECT_STRINGUTILS_H
