#ifndef _LDF_DATE_H_
#define _LDF_DATE_H_

#include <stdexcept>
#include <string>
#include "../base.h"


LDF_BEGIN

    /**
     * Date 포맷에 에러가 있는 경우 발생하는 Exception
     */
    class DateFormatException : public std::runtime_error {
    public:
        explicit DateFormatException(const std::string &msg) : std::runtime_error(msg) {
        }
    };


    /**
     * 날짜를 저장하는 클래스
     */
    class Date {
    public:
        Date();

        Date(const Date &date) : _year(date._year), _month(date._month), _day(date._day) {}

        Date(int year, int month, int day) : _year(year), _month(month), _day(day) {}

        Date(const std::string &str);

        void set(int year, int month, int day);

        void set(const Date &date);

        void set(const std::string &str);

        int year() const { return _year; }

        int month() const { return _month; }

        int day() const { return _day; }

        int daysOfMonth() const;

        int dayOfYear() const;

        void plusDay(int days);

        void minusDay(int days);

        Date &operator+(int days);

        Date &operator-(int days);

        Date &operator=(const Date &date);

        int operator-(const Date &date);

        bool operator<(const Date &date);

        bool operator>(const Date &date);

        bool operator==(const Date &date);

        bool operator!=(const Date &date);

        bool operator<=(const Date &date);

        bool operator>=(const Date &date);

        std::string format() const;

        std::string toString() const;

        bool leap() const;

        static bool Leap(int year);

        static int Compare(const Date &date1, const Date &date2);

        static int Diff(const Date &from, const Date &to);

    private:
        int _year;
        int _month;
        int _day;
    };

LDF_END

#endif
