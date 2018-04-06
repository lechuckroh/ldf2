#include <vector>
#include <sstream>
#include "Strings.h"

using namespace std;

LDF_BEGIN

    int Strings::ToInt(const std::string &s, int defaultValue) {
        try {
            return stoi(s);
        } catch (...) {
            return defaultValue;
        }
    }

    vector<string> Strings::split(const string &s, char delim, int minCount) {
        stringstream ss(s);
        string item;
        vector<string> tokens;
        while (getline(ss, item, delim)) {
            tokens.push_back(item);
        }
        for (auto i = tokens.size(); i < minCount; i++) {
            tokens.push_back("");
        }
        return tokens;
    }

LDF_END
