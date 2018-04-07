#ifndef _LDF_TIME_H_
#define _LDF_TIME_H_

#include <stdexcept>
#include <string>
#include "base.h"


LDF_BEGIN

    class TimeFormatException : public std::runtime_error {
    public:
        explicit TimeFormatException(const std::string &msg) : std::runtime_error(msg) {
        }
    };


    class Time {
    public:
        Time();

        Time(const Time &time);

        Time(int hour, int minute, int second);

        explicit Time(const std::string &str);

        explicit Time(int timeInSec);

        void set(int hour, int minute, int second);

        void set(int timeInSec);

        void set(const Time &time);

        void set(const std::string &str);

        int hour() const { return _hour; }

        int minute() const { return _minute; }

        int second() const { return _second; }

        int timeInSec() const;

        void plusHour(int hours);

        void plusMinute(int minutes);

        void plusSecond(int seconds);

        Time operator+(int seconds);

        Time operator-(int seconds);

        Time &operator=(const Time &time);

        int operator-(const Time &time);

        bool operator<(const Time &time);

        bool operator>(const Time &time);

        bool operator==(const Time &time);

        bool operator!=(const Time &time);

        bool operator<=(const Time &time);

        bool operator>=(const Time &time);

        std::string format() const;

        std::string toString() const;

        static int Compare(const Time &time1, const Time &time2);

        static int Diff(const Time &from, const Time &to);

    private:
        void adjustFields();

        int _hour;
        int _minute;
        int _second;
    };

LDF_END
#endif
