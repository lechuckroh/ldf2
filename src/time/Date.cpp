#include <vector>
#include <chrono>
#include "time/Date.h"
#include "Strings.h"

using namespace std;

LDF_BEGIN

    const static int CUMUL_DAYS[2][14] = {
            {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
            {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366}
    };

    const static int DAYS_OF_MONTH[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const static int DAYS_OF_MONTH_LEAP[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    void checkMonth(int month) {
        if (month < 1 || month > 12) {
            throw out_of_range(strf("out of month range : 1 <= month(%d) <= 12", month));
        }
    }

    void checkDay(int month, int day) {
        if (month < 1 || month > 12) {
            throw out_of_range(strf("out of month range : 1 <= month(%d) <= 12", month));
        }

        int dayOfMonth = DAYS_OF_MONTH[month];
        if (day < 1 || day > dayOfMonth) {
            throw out_of_range(strf("out of day range : month=%d, 1 <= day(%d) <= %d", month, day, dayOfMonth));
        }
    }

    void checkDayLeap(int month, int day) {
        if (month < 1 || month > 12) {
            throw out_of_range(strf("out of month range : 1 <= month(%d) <= 12", month));
        }

        int dayOfMonth = DAYS_OF_MONTH_LEAP[month];
        if (day < 1 || day > dayOfMonth) {
            throw out_of_range(strf("out of day range : month=%d, 1 <= day(%d) <= %d", month, day, dayOfMonth));
        }
    }

    Date::Date() {
        time_t t = chrono::system_clock::to_time_t(chrono::system_clock::now());
        struct tm localNow{};
        int errNo = localtime_s(&localNow, &t);

        if (errNo != 0) {
            throw runtime_error("Failed to get current time");
        }
        _year = localNow.tm_year + 1900;
        _month = localNow.tm_mon + 1;
        _day = localNow.tm_mday;
    }

    /**
     * yyyy/MM/dd, yyyy-MM-dd, yyyyMMdd 포맷
     */
    Date::Date(const string &str) {
        set(str);
    }

    /**
     * yyyy/MM/dd, yyyy-MM-dd, yyyyMMdd 포맷
     */
    void Date::set(const string &str) {
        int year = 0;
        int month = 0;
        int day = 0;

        if (str.find('-') != string::npos) {
            vector<string> tokens = Strings::split(str, '-', 3);
            year = Strings::ToInt(tokens[0]);
            month = Strings::ToInt(tokens[1]);
            day = Strings::ToInt(tokens[2]);
        } else if (str.find('/') != string::npos) {
            vector<string> tokens = Strings::split(str, '/', 3);
            year = Strings::ToInt(tokens[0]);
            month = Strings::ToInt(tokens[1]);
            day = Strings::ToInt(tokens[2]);
        } else if (str.length() == 8) {
            year = Strings::ToInt(str.substr(0, 4));
            month = Strings::ToInt(str.substr(4, 2));
            day = Strings::ToInt(str.substr(6, 2));
        }

        if (year <= 0 || month <= 0 || day <= 0) {
            throw DateFormatException("Invalid Format: " + str);
        }

        checkMonth(month);

        if (Leap(year)) {
            checkDayLeap(month, day);
        } else {
            checkDay(month, day);
        }

        _year = year;
        _month = month;
        _day = day;
    }

    void Date::set(int year, int month, int day) {
        checkMonth(month);
        if (Leap(year)) {
            checkDayLeap(month, day);
        } else {
            checkDay(month, day);
        }

        _year = year;
        _month = month;
        _day = day;
    }

    void Date::set(const Date &date) {
        set(date._year, date._month, date._day);
    }

    bool Date::leap() const {
        return Leap(_year);
    }

    bool Date::Leap(int year) {
        if (year % 4 != 0) {
            return false;
        }
        if (year % 100 != 0) {
            return true;
        }
        return year % 400 == 0;
    }


    int Date::daysOfMonth() const {
        return _month == 2 ? (leap() ? 29 : 28) : DAYS_OF_MONTH[_month];
    }

    int Date::dayOfYear() const {
        return (leap() ? CUMUL_DAYS[1][_month] : CUMUL_DAYS[0][_month]) + _day;
    }

    string Date::format() const {
        return strf("%04d-%02d-%02d", _year, _month, _day);
    }

    string Date::toString() const {
        return strf("%04d%02d%02d", _year, _month, _day);
    }

    void Date::plusDay(int days) {
        // add 'days' first
        _day += days;

        // reduce until _day is less than daysOfMonth.
        while (_day > daysOfMonth()) {
            _day -= daysOfMonth();
            _month++;

            if (_month > 12) {
                _month = 1;
                _year++;
            }
        }
    }

    void Date::minusDay(int days) {
        // reduce 'days' first
        _day -= days;

        // add daysOfMonth until '_day' is positive.
        while (_day < 1) {
            _month--;
            if (_month < 1) {
                _month = 12;
                _year--;
            }
            _day += daysOfMonth();
        }
    }

    Date &Date::operator+(int days) {
        plusDay(days);
        return *this;
    }

    Date &Date::operator-(int days) {
        minusDay(days);
        return *this;
    }

    Date &Date::operator=(const Date &date) = default;

    int Date::Compare(const Date &date1, const Date &date2) {
        if (date1._year < date2._year) {
            return -1;
        }
        if (date1._year > date2._year) {
            return 1;
        }

        if (date1._month < date2._month) {
            return -1;
        }
        if (date1._month > date2._month) {
            return 1;
        }

        if (date1._day < date2._day) {
            return -1;
        }
        if (date1._day > date2._day) {
            return 1;
        }

        return false;
    }

    int Date::Diff(const Date &from, const Date &to) {
        int i;
        int days = 0;

        if (Compare(from, to) < 0) {
            for (i = from._year; i < to._year; i++)
                days += Leap(i) ? 366 : 365;

            days += to.dayOfYear() - from.dayOfYear();
        } else {
            for (i = to._year; i < from._year; i++)
                days += Leap(i) ? 366 : 365;

            days += from.dayOfYear() - to.dayOfYear();
            days = -days;
        }

        return days;
    }


    int Date::operator-(const Date &date) {
        return Diff(date, *this);
    }

    bool Date::operator<(const Date &date) {
        return Compare(*this, date) < 0;
    }

    bool Date::operator>(const Date &date) {
        if (*this < date) {
            return false;
        }
        return !(*this == date);
    }

    bool Date::operator==(const Date &date) {
        return _year == date._year && _month == date._month && _day == date._day;
    }

    bool Date::operator!=(const Date &date) {
        return _year != date._year || _month != date._month || _day != date._day;
    }

    bool Date::operator<=(const Date &date) {
        return !(*this > date);
    }

    bool Date::operator>=(const Date &date) {
        return !(*this < date);
    }

LDF_END
