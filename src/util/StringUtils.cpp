//
// Created by y on 2019-05-25.
//

#include <regex>
#include <sstream>
#include "StringUtils.h"

// trim from start (in place)

void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

// split string to tokens (vector <string>)
std::vector<std::string> split(const std::string& subject) {
    static const std::regex re{"\\s+"};
    std::vector<std::string> container{
            std::sregex_token_iterator(subject.begin(), subject.end(), re, -1),
            std::sregex_token_iterator()
    };
    return container;
}

// convert all whitespaces to single spaces
std::string single_space(std::string const &input) {
    std::istringstream buffer(input);
    std::ostringstream result;

    std::copy(std::istream_iterator<std::string>(buffer),
              std::istream_iterator<std::string>(),
              std::ostream_iterator<std::string>(result, " "));
    return result.str();
}
