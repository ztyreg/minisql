//
// Created by y on 2019-05-25.
//

#include <iostream>
#include <regex>
#include <sstream>
#include <cassert>
#include <cstring>
#include "StringUtils.h"

using namespace std;

// trim from start (in place)

void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch)
    {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch)
    {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
void trim(std::string &s)
{
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
std::string ltrim_copy(std::string s)
{
    ltrim(s);
    return s;
}

// trim from end (copying)
std::string rtrim_copy(std::string s)
{
    rtrim(s);
    return s;
}

// trim from both ends (copying)
std::string trim_copy(std::string s)
{
    trim(s);
    return s;
}

// split string to tokens (vector <string>)
std::vector<std::string> split(const std::string &subject)
{
    static const std::regex re{"\\s+"};
    std::vector<std::string> container{
            std::sregex_token_iterator(subject.begin(), subject.end(), re, -1),
            std::sregex_token_iterator()
    };
    return container;
}

// convert all whitespaces to single spaces
std::string single_space(std::string const &input)
{
    std::istringstream buffer(input);
    std::ostringstream result;

    std::copy(std::istream_iterator<std::string>(buffer),
              std::istream_iterator<std::string>(),
              std::ostream_iterator<std::string>(result, " "));
    return result.str();
}

int bstring_to_int(std::string bin)
{
    assert(bin.length() == 32);
    int n = 0;
    for (int i = 0; i < bin.length(); ++i) {
        n |= (bin[i] - 48) << (bin.length() - 1 - i);
    }
    return n;
}

float bstring_to_float(std::string bin)
{
    assert(bin.length() == 32);
    int n = 0;
    for (int i = 0; i < bin.length(); ++i) {
        n |= (bin[i] - 48) << (bin.length() - 1 - i);
    }
    float f = *(float *) &n;
    return f;
}

std::string int_to_bstring(int bin)
{
    std::uint32_t t;
    std::memcpy(&t, &bin, sizeof(bin));
    return std::bitset<sizeof(int) * 8>(t).to_string();
}

std::string float_to_bstring(float bin)
{
    std::uint32_t t;
    std::memcpy(&t, &bin, sizeof(bin));
    return std::bitset<sizeof(float) * 8>(t).to_string();
}

void memwrite_int(char *mem, int n)
{
    memcpy(mem, &n, 4);
}

void memwrite_float(char *mem, float n)
{
    memcpy(mem, &n, 4);
}

void memread_int(char *mem, int *n)
{
    memcpy(n, mem, 4);

}

void memread_float( char *mem, float *n)
{
    memcpy(n, mem, 4);

}
