#ifndef _LDF_STRINGS_H_
#define _LDF_STRINGS_H_

#include <cstdio>
#include <memory>
#include <string>
#include "base.h"

LDF_BEGIN

    template<typename ... Args>
    std::string strf(const std::string &format, Args ... args) {
        int size = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
        std::unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), static_cast<size_t>(size), format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size - 1);
    }

    class Strings {
    public:
        static int ToInt(const std::string &s, int defaultValue = 0);

        static std::vector<std::string> split(const std::string &s, char delim, int minCount = 0);
    };

LDF_END

#endif
