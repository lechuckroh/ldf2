#ifndef _LDF_DATETIME_H_
#define _LDF_DATETIME_H_

#include "Date.h"
#include "Time.h"


LDF_BEGIN

class DateTime {
public:
    DateTime();
    DateTime(const Date &date);
    DateTime(const DateTime &dateTime);
    DateTime(int year, int month, int day, int hour=0, int min=0, int sec=0);
    DateTime(const std::string& str);

    virtual ~DateTime();

    void setDate(int year, int month, int day);
    void setDate(const Date& date);
    void setTime(int hour, int min, int sec=0);
    void setTime(const Time& time);

    int  year()   const;
    int  month()  const;
    int  day()    const;
    int  hour()   const;
    int  minute() const;
    int  second() const;

    const Date* date() const;
    const Time* time() const;

    void  plusSecond(long sec);
    void  plusDay(int day);
    void  plusHour(int hour);
    void  plusMinute(int min);

    DateTime& operator= (const DateTime& dateTime);
    long  operator- (const DateTime& dateTime);
    bool  operator< (const DateTime& dateTime);
    bool  operator> (const DateTime& dateTime);
    bool  operator==(const DateTime& dateTime);
    bool  operator!=(const DateTime& dateTime);
    bool  operator<=(const DateTime& dateTime);
    bool  operator>=(const DateTime& dateTime);

    std::string format() const;
    std::string toString() const;

	bool empty() const;

    static int  Compare(const DateTime& dateTime1, const DateTime& dateTime2);
    static long GetDiff(const DateTime& from, const DateTime& to);
	static DateTime Empty();

private:
    Date _date;
    Time _time;

    void adjustDate();
};

LDF_END
#endif
