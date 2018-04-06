#include <vector>
#include "time/DateTime.h"
#include "Strings.h"

using namespace std;

LDF_BEGIN

    DateTime::DateTime() {
    }

    DateTime::DateTime(const Date &date) : _date(date) {
        _time.set(0, 0, 0);
    }

    DateTime::DateTime(const DateTime &dateTime) : _date(dateTime._date), _time(dateTime._time) {
    }

    DateTime::DateTime(int year, int month, int day, int hour, int min, int sec) {
        _date.set(year, month, day);
        _time.set(hour, min, sec);
    }

    DateTime::DateTime(const string &str) {
        if (str.find(' ') != string::npos) {
            auto tokens = Strings::split(str, ' ', 2);
            _date.set(tokens[0]);
            _time.set(tokens[1]);
        } else {
            _date.set(str);
            _time.set(0, 0, 0);
        }
    }

    DateTime::~DateTime() {
    }

    void DateTime::adjustDate() {
        int hour = _time.hour();

        if (hour < 0) {
            int daysToReduce = abs((hour + 1) / 24) + 1;
            _time.plusHour(daysToReduce * 24);
            _date.minusDay(daysToReduce);
        }

        if (hour >= 24) {
            int daysToAdd = hour / 24;
            _date.plusDay(daysToAdd);
            _time.plusHour(-daysToAdd * 24);
        }
    }

    void DateTime::setDate(int year, int month, int day) {
        _date.set(year, month, day);
    }

    void DateTime::setDate(const Date &date) {
        _date.set(date);
    }

    void DateTime::setTime(int hour, int min, int sec) {
        _time.set(hour, min, sec);
        adjustDate();
    }

    DateTime DateTime::Empty() {
        return DateTime(0, 1, 1);
    }

    bool DateTime::empty() const {
        return _date.empty() && _time.hour() == 0 && _time.minute() == 0 && _time.second() == 0;
    }

    void DateTime::setTime(const Time &time) {
        _time.set(time);
        adjustDate();
    }

    int DateTime::year() const {
        return _date.year();
    }

    int DateTime::month() const {
        return _date.month();
    }

    int DateTime::day() const {
        return _date.day();
    }

    int DateTime::hour() const {
        return _time.hour();
    }

    int DateTime::minute() const {
        return _time.minute();
    }

    int DateTime::second() const {
        return _time.second();
    }

    const Date *DateTime::date() const {
        return &_date;
    }

    const Time *DateTime::time() const {
        return &_time;
    }

    void DateTime::plusDay(int day) {
        _date.plusDay(day);
    }

    void DateTime::plusHour(int hour) {
        _time.plusHour(hour);
        adjustDate();
    }

    void DateTime::plusMinute(int min) {
        _time.plusMinute(min);
        adjustDate();
    }

    void DateTime::plusSecond(long sec) {
        _time.plusSecond(sec);
        adjustDate();
    }

    DateTime &DateTime::operator=(const DateTime &dateTime) {
        _date.set(dateTime._date);
        _time.set(dateTime._time);
        return *this;
    }

    long DateTime::operator-(const DateTime &dateTime) {
        return GetDiff(dateTime, *this);
    }

    bool DateTime::operator<(const DateTime &dateTime) {
        if (_date < dateTime._date)
            return true;
        if (_date == dateTime._date)
            return _time < dateTime._time;
        return false;
    }

    bool DateTime::operator>(const DateTime &dateTime) {
        if (_date > dateTime._date)
            return true;
        if (_date < dateTime._date)
            return false;
        return _time > dateTime._time;
    }

    bool DateTime::operator==(const DateTime &dateTime) {
        return _date == dateTime._date && _time == dateTime._time;
    }

    bool DateTime::operator!=(const DateTime &dateTime) {
        return _date != dateTime._date || _time != dateTime._time;
    }

    bool DateTime::operator<=(const DateTime &dateTime) {
        if (_date < dateTime._date)
            return true;
        if (_date > dateTime._date)
            return false;

        return _time <= dateTime._time;
    }

    bool DateTime::operator>=(const DateTime &dateTime) {
        if (_date > dateTime._date)
            return true;
        if (_date == dateTime._date)
            return _time >= dateTime._time;
        return false;
    }

    string DateTime::format() const {
        return strf("%04d-%02d-%02d %02d:%02d:%02d", _date.year(), _date.month(), _date.day(), _time.hour(),
                    _time.minute(), _time.second());
    }

    string DateTime::toString() const {
        return strf("%04d/%02d/%02d %02d:%02d:%02d", _date.year(), _date.month(), _date.day(), _time.hour(),
                    _time.minute(), _time.second());
    }

    int DateTime::Compare(const DateTime &dateTime1, const DateTime &dateTime2) {
        int cmp = Date::Compare(dateTime1._date, dateTime2._date);
        if (cmp == 0) {
            cmp = Time::Compare(dateTime1._time, dateTime2._time);
        }

        return cmp;
    }

    // to - from 의 값을 초단위로 리턴한다.
    long DateTime::GetDiff(const DateTime &from, const DateTime &to) {
        long dayResult = Date::Diff(from._date, to._date);
        long timeResult = Time::Diff(from._time, to._time);

        return dayResult * 86400 + timeResult;
    }

LDF_END
