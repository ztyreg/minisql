//
// Created by y on 2019-05-25.
//

#ifndef PROJECT_STRINGUTILS_H
#define PROJECT_STRINGUTILS_H

#include <algorithm>
#include <cctype>
#include <locale>
#include <vector>

void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s);
std::string ltrim_copy(std::string s);
std::string rtrim_copy(std::string s);
std::string trim_copy(std::string s);
std::vector<std::string> split(const std::string& subject);
std::string single_space(std::string const &input);
int bstring_to_int(std::string bin);
float bstring_to_float(std::string bin);
std::string int_to_bstring(int bin);
std::string float_to_bstring(float bin);
void memwrite_int(char mem[], int n);
void memwrite_float(char mem[], float n);
void memread_int(char mem[], int *n);
void memread_float(char mem[], float *n);
#endif //PROJECT_STRINGUTILS_H
