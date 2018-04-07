#include <chrono>
#include <regex>
#include <vector>
#include <iostream>
#include "Strings.h"
#include "time/Time.h"

using namespace std;

LDF_BEGIN

    /**
     * 디폴트 생성자.
     * 현재 시각으로 설정한다.
     */
    Time::Time() {
        auto t = chrono::system_clock::to_time_t(chrono::system_clock::now());
        auto now = localtime(&t);

        if (now == nullptr) {
            _hour = 0;
            _minute = 0;
            _second = 0;
        } else {
            _hour = now->tm_hour;
            _minute = now->tm_min;
            _second = now->tm_sec;
        }
    }

    Time::Time(const Time &time) {
        _hour = time._hour;
        _minute = time._minute;
        _second = time._second;
    }

    /**
     * 생성자<p/>
     * 0미만의 각 필드의 값은 0으로 변경된다.
     * 60이상인 분,초는 60미만의 값으로 변경되면서 상위 필드의 값을
     * 변경한다.
     */
    Time::Time(int hour, int minute, int second) {
        set(hour, minute, second);
    }

    /**
     * hhmmdd 또는 hh:mm:dd 포맷
     */
    Time::Time(const string &str) {
        set(str);
    }

    Time::Time(int timeInSec) {
        set(timeInSec);
    }

    void Time::adjustFields() {
        if (_second < 0) {
            int minToReduce = abs((_second + 1) / 60) + 1;
            _second += minToReduce * 60;
            _minute -= minToReduce;
        }

        if (_second >= 60) {
            _minute += _second / 60;
            _second = _second % 60;
        }

        if (_minute < 0) {
            int hourToReduce = abs((_minute + 1) / 60) + 1;
            _minute += hourToReduce * 60;
            _hour -= hourToReduce;
        }

        if (_minute >= 60) {
            _hour += _minute / 60;
            _minute = _minute % 60;
        }
    }

    void Time::set(int hour, int minute, int second) {
        _hour = hour;
        _minute = minute;
        _second = second;

        adjustFields();
    }

    void Time::set(const string &str) {
        int hour = -1;
        int minute = -1;
        int second = -1;

        smatch sm;
        regex_match(str, sm, regex("([0-9]+)[:]?([0-9]{2})[:]?([0-9]{2})"));
        if (sm.size() == 4) {
            hour = Strings::ToInt(sm[1], -1);
            minute = Strings::ToInt(sm[2], -1);
            second = Strings::ToInt(sm[3], -1);
        }
        if (hour <= -1 || minute <= -1 || second <= -1) {
            throw TimeFormatException("Invalid Format: " + str);
        }

        set(hour, minute, second);
    }

    void Time::set(int timeInSec) {
        set(0, 0, timeInSec);
    }

    void Time::set(const Time &time) {
        set(time._hour, time._minute, time._second);
    }

    /**
     * hh:mm:dd 포맷으로 리턴한다.
     */
    string Time::format() const {
        return strf("%02d:%02d:%02d", _hour, _minute, _second);
    }

    /**
     * hh:mm:dd 포맷으로 리턴한다.
     */
    string Time::toString() const {
        return strf("%02d:%02d:%02d", _hour, _minute, _second);
    }

    void Time::plusHour(int hours) {
        _hour += hours;
    }

    void Time::plusMinute(int minutes) {
        _minute += minutes;
        adjustFields();
    }

    void Time::plusSecond(int seconds) {
        _second += seconds;
        adjustFields();
    }

    int Time::timeInSec() const {
        return _hour * 3600 + _minute * 60 + _second;
    }

    Time Time::operator+(int seconds) {
        return Time(timeInSec() + seconds);
    }

    Time Time::operator-(int seconds) {
        return Time(timeInSec() - seconds);
    }

    Time &Time::operator=(const Time &time) {
        _hour = time._hour;
        _minute = time._minute;
        _second = time._second;
        return (*this);
    }

    int Time::Compare(const Time &time1, const Time &time2) {
        if (time1._hour < time2._hour) return -1;
        if (time1._hour > time2._hour) return 1;

        if (time1._minute < time2._minute) return -1;
        if (time1._minute > time2._minute) return 1;

        if (time1._second < time2._second) return -1;
        if (time1._second > time2._second) return 1;

        return false;
    }

    // to - from 의 값을 초단위로 리턴한다.
    int Time::Diff(const Time &from, const Time &to) {
        return to.timeInSec() - from.timeInSec();
    }

    int Time::operator-(const Time &time) {
        return timeInSec() - time.timeInSec();
    }

    bool Time::operator<(const Time &time) {
        return Compare(*this, time) < 0;
    }

    bool Time::operator>(const Time &time) {
        return Compare(*this, time) > 0;
    }

    bool Time::operator==(const Time &time) {
        return _hour == time._hour && _minute == time._minute && _second == time._second;
    }

    bool Time::operator!=(const Time &time) {
        return _hour != time._hour && _minute != time._minute && _second != time._second;
    }

    bool Time::operator<=(const Time &time) {
        return !(*this > time);
    }

    bool Time::operator>=(const Time &time) {
        return !(*this < time);
    }

LDF_END
