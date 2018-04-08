#include "time/Time.h"
#include "catch.hpp"

using namespace std;
using namespace ldf;

TEST_CASE("Time", "[time]") {

    SECTION("constructor") {
        Time t(15, 10, 22);
        REQUIRE(t.hour() == 15);
        REQUIRE(t.minute() == 10);
        REQUIRE(t.second() == 22);
    }

    SECTION("copy constructor") {
        Time t(Time(15, 10, 22));
        REQUIRE(t.hour() == 15);
        REQUIRE(t.minute() == 10);
        REQUIRE(t.second() == 22);
    }

    SECTION("hh:mm:ss") {
        Time t("999:13:14");
        REQUIRE(t.hour() == 999);
        REQUIRE(t.minute() == 13);
        REQUIRE(t.second() == 14);
    }

    SECTION("hh:mm:ss - invalid") {
        CHECK_THROWS(Time("10:12:-1"));
        CHECK_THROWS(Time("123"));
    }

    SECTION("hhmmss") {
        Time t("121314");
        REQUIRE(t.hour() == 12);
        REQUIRE(t.minute() == 13);
        REQUIRE(t.second() == 14);
    }

    SECTION("set h,m,s") {
        Time t;
        t.set(10, 11, 12);
        REQUIRE(t.hour() == 10);
        REQUIRE(t.minute() == 11);
        REQUIRE(t.second() == 12);
    }

    SECTION("set timeInSec") {
        Time t;
        t.set(10 * 3600 + 11 * 60 + 12);
        REQUIRE(t.hour() == 10);
        REQUIRE(t.minute() == 11);
        REQUIRE(t.second() == 12);
    }

    SECTION("set time") {
        Time t;
        t.set(Time(10, 11, 12));
        REQUIRE(t.hour() == 10);
        REQUIRE(t.minute() == 11);
        REQUIRE(t.second() == 12);
    }

    SECTION("set string") {
        Time t;
        t.set("10:11:12");
        REQUIRE(t.hour() == 10);
        REQUIRE(t.minute() == 11);
        REQUIRE(t.second() == 12);
    }

    SECTION("timeInSec") {
        Time t(10, 11, 12);
        REQUIRE(t.timeInSec() == 10 * 3600 + 11 * 60 + 12);
    }

    SECTION("plusHour") {
        Time t1(10, 11, 12);
        t1.plusHour(20);
        REQUIRE(t1.hour() == 30);

        Time t2(10, 11, 12);
        t2.plusHour(-20);
        REQUIRE(t2.hour() == -10);
    }

    SECTION("plusMinute") {
        Time t1(10, 11, 12);
        t1.plusMinute(50);
        REQUIRE(t1.hour() == 11);
        REQUIRE(t1.minute() == 1);

        Time t2(10, 11, 12);
        t2.plusMinute(-20);
        REQUIRE(t2.hour() == 9);
        REQUIRE(t2.minute() == 51);
    }

    SECTION("plusSecond") {
        Time t1(0, 59, 59);
        t1.plusSecond(2);
        REQUIRE(t1.hour() == 1);
        REQUIRE(t1.minute() == 0);
        REQUIRE(t1.second() == 1);

        Time t2(0, 0, 0);
        t2.plusSecond(-70);
        REQUIRE(t2.hour() == -1);
        REQUIRE(t2.minute() == 58);
        REQUIRE(t2.second() == 50);
    }

    SECTION("operator") {
        Time t1(1, 0, 0);
        Time t2(0, 59, 59);
        REQUIRE(t1 == Time(1, 0, 0));
        REQUIRE(t1 >= Time(1, 0, 0));
        REQUIRE(t1 <= Time(1, 0, 0));
        REQUIRE(t1 + 10 == Time(1, 0, 10));
        REQUIRE(t1 - 10 == Time(0, 59, 50));
        REQUIRE(t1 - t2 == 1);
        REQUIRE(t1 > t2);
        REQUIRE(t1 >= t2);
        REQUIRE(t2 < t1);
        REQUIRE(t2 <= t1);
        REQUIRE(t2 != t1);
    }

    SECTION("format") {
        REQUIRE(Time(1, 0, 0).format() == "01:00:00");
        REQUIRE(Time(1000, 59, 59).format() == "1000:59:59");
    }

    SECTION("toString") {
        REQUIRE(Time(1, 0, 0).format() == "01:00:00");
        REQUIRE(Time(1000, 59, 59).format() == "1000:59:59");
    }

    SECTION("Compare") {
        REQUIRE(Time::Compare(Time(1, 0, 0), Time(1, 0, 0)) == 0);
        REQUIRE(Time::Compare(Time(0, 59, 59), Time(1, 0, 0)) < 0);
        REQUIRE(Time::Compare(Time(1, 0, 0), Time(0, 59, 59)) > 0);
    }

    SECTION("Diff") {
        REQUIRE(Time::Diff(Time(1, 0, 0), Time(1, 0, 0)) == 0);
        REQUIRE(Time::Diff(Time(0, 59, 59), Time(1, 0, 0)) == 1);
        REQUIRE(Time::Diff(Time(1, 0, 0), Time(0, 59, 59)) == -1);
    }
}
