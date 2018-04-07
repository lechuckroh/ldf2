#ifndef _LDF_DATETIME_H_
#define _LDF_DATETIME_H_

#include <memory>
#include "Date.h"
#include "Time.h"


LDF_BEGIN

    class DateTime {
    public:
        DateTime();

        DateTime(const Date &date);

        DateTime(int year, int month, int day, int hour = 0, int min = 0, int sec = 0);

        DateTime(const std::string &str);

        virtual ~DateTime() = default;

        void date(int year, int month, int day);

        void date(const Date &date);

        void time(int hour, int min, int sec = 0);

        void time(const Time &time);

        int year() const;

        int month() const;

        int day() const;

        int hour() const;

        int minute() const;

        int second() const;

        const Date date() const;

        const Time time() const;

        void plusSecond(long sec);

        void plusDay(int day);

        void plusHour(int hour);

        void plusMinute(int min);

        DateTime &operator=(const DateTime &dateTime);

        long operator-(const DateTime &dateTime);

        bool operator<(const DateTime &dateTime);

        bool operator>(const DateTime &dateTime);

        bool operator==(const DateTime &dateTime);

        bool operator!=(const DateTime &dateTime);

        bool operator<=(const DateTime &dateTime);

        bool operator>=(const DateTime &dateTime);

        std::string format() const;

        std::string toString() const;

        static int Compare(const DateTime &dateTime1, const DateTime &dateTime2);

        static long Diff(const DateTime &from, const DateTime &to);

    private:
        std::unique_ptr<Date> _date;
        std::unique_ptr<Time> _time;

        void adjustDate();
    };

LDF_END
#endif
