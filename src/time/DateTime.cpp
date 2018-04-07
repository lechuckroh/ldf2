#include <vector>
#include "time/DateTime.h"
#include "Strings.h"

using namespace std;

LDF_BEGIN

    DateTime::DateTime() {
        _date = make_unique<Date>();
        _time = make_unique<Time>();
    }

    DateTime::DateTime(const Date &date) {
        _date = make_unique<Date>(date);
        _time = make_unique<Time>(0, 0, 0);
    }

    DateTime::DateTime(int year, int month, int day, int hour, int min, int sec) {
        _date = make_unique<Date>(year, month, day);
        _time = make_unique<Time>(hour, min, sec);
    }

    DateTime::DateTime(const string &str) {
        if (str.find(' ') != string::npos) {
            auto tokens = Strings::split(str, ' ', 2);
            _date = make_unique<Date>(tokens[0]);
            _time = make_unique<Time>(tokens[1]);
        } else {
            _date = make_unique<Date>(str);
            _time = make_unique<Time>(0, 0, 0);
        }
    }

    void DateTime::adjustDate() {
        int hour = _time->hour();

        if (hour < 0) {
            int daysToReduce = abs((hour + 1) / 24) + 1;
            _time->plusHour(daysToReduce * 24);
            _date->minusDay(daysToReduce);
        }

        if (hour >= 24) {
            int daysToAdd = hour / 24;
            _date->plusDay(daysToAdd);
            _time->plusHour(-daysToAdd * 24);
        }
    }

    void DateTime::date(int year, int month, int day) {
        _date->set(year, month, day);
    }

    void DateTime::date(const Date &date) {
        _date->set(date);
    }

    void DateTime::time(int hour, int min, int sec) {
        _time->set(hour, min, sec);
        adjustDate();
    }

    void DateTime::time(const Time &time) {
        _time->set(time);
        adjustDate();
    }

    int DateTime::year() const {
        return _date->year();
    }

    int DateTime::month() const {
        return _date->month();
    }

    int DateTime::day() const {
        return _date->day();
    }

    int DateTime::hour() const {
        return _time->hour();
    }

    int DateTime::minute() const {
        return _time->minute();
    }

    int DateTime::second() const {
        return _time->second();
    }

    const Date DateTime::date() const {
        return *_date;
    }

    const Time DateTime::time() const {
        return *_time;
    }

    void DateTime::plusDay(int day) {
        _date->plusDay(day);
    }

    void DateTime::plusHour(int hour) {
        _time->plusHour(hour);
        adjustDate();
    }

    void DateTime::plusMinute(int min) {
        _time->plusMinute(min);
        adjustDate();
    }

    void DateTime::plusSecond(long sec) {
        _time->plusSecond(sec);
        adjustDate();
    }

    DateTime &DateTime::operator=(const DateTime &dateTime) {
        _date->set(dateTime.year(), dateTime.month(), dateTime.day());
        _time->set(dateTime.hour(), dateTime.minute(), dateTime.second());
        return *this;
    }

    long DateTime::operator-(const DateTime &dateTime) {
        return Diff(dateTime, *this);
    }

    bool DateTime::operator<(const DateTime &dateTime) {
        int cmp = Date::Compare(*_date, *dateTime._date);
        return cmp < 0 || (cmp == 0 && Time::Compare(*_time, *dateTime._time) < 0);
    }

    bool DateTime::operator>(const DateTime &dateTime) {
        int cmp = Date::Compare(*_date, *dateTime._date);
        return cmp > 0 || (cmp == 0 && Time::Compare(*_time, *dateTime._time) > 0);
    }

    bool DateTime::operator==(const DateTime &dateTime) {
        return Date::Compare(*_date, *dateTime._date) == 0 && Time::Compare(*_time, *dateTime._time) == 0;
    }

    bool DateTime::operator!=(const DateTime &dateTime) {
        return Date::Compare(*_date, *dateTime._date) != 0 || Time::Compare(*_time, *dateTime._time) != 0;
    }

    bool DateTime::operator<=(const DateTime &dateTime) {
        int cmp = Date::Compare(*_date, *dateTime._date);
        return cmp < 0 || (cmp == 0 && Time::Compare(*_time, *dateTime._time) <= 0);
    }

    bool DateTime::operator>=(const DateTime &dateTime) {
        int cmp = Date::Compare(*_date, *dateTime._date);
        return cmp > 0 || (cmp == 0 && Time::Compare(*_time, *dateTime._time) >= 0);
    }

    string DateTime::format() const {
        return strf("%04d-%02d-%02d %02d:%02d:%02d",
                    _date->year(), _date->month(), _date->day(),
                    _time->hour(), _time->minute(), _time->second());
    }

    string DateTime::toString() const {
        return strf("%04d/%02d/%02d %02d:%02d:%02d",
                    _date->year(), _date->month(), _date->day(),
                    _time->hour(), _time->minute(), _time->second());
    }

    int DateTime::Compare(const DateTime &dateTime1, const DateTime &dateTime2) {
        int cmp = Date::Compare(*dateTime1._date, *dateTime2._date);
        if (cmp == 0) {
            cmp = Time::Compare(*dateTime1._time, *dateTime2._time);
        }
        return cmp;
    }

    // to - from 의 값을 초단위로 리턴한다.
    long DateTime::Diff(const DateTime &from, const DateTime &to) {
        long dayResult = Date::Diff(*from._date, *to._date);
        long timeResult = Time::Diff(*from._time, *to._time);
        return dayResult * 86400 + timeResult;
    }

LDF_END
