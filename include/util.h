#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>

using std::vector, std::string;

namespace util {
    inline vector<string> split(const string &text, const string &delim) {
        vector<string> parts;
        size_t start = 0, end;
        while ((end = text.find(delim, start)) != string::npos) {
            parts.push_back(text.substr(start, end - start));
            start = end + delim.size();
        }
        parts.push_back(text.substr(start));
        return parts;
    }
}

#endif //UTIL_H
