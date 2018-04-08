#include "time/Date.h"
#include "catch.hpp"

using namespace std;
using namespace ldf;

TEST_CASE("Date", "[time]") {

    SECTION("constructor") {
        Date d(2018, 10, 11);
        REQUIRE(d.year() == 2018);
        REQUIRE(d.month() == 10);
        REQUIRE(d.day() == 11);
    }

    SECTION("copy constructor") {
        Date d(Date(2018, 10, 11));
        REQUIRE(d.year() == 2018);
        REQUIRE(d.month() == 10);
        REQUIRE(d.day() == 11);
    }

    SECTION("yyyy-MM-dd") {
        Date d("2018-10-11");
        REQUIRE(d.year() == 2018);
        REQUIRE(d.month() == 10);
        REQUIRE(d.day() == 11);
    }

    SECTION("yyyy-MM-dd - invalid") {
        CHECK_THROWS(Date("2018-99-50"));
        CHECK_THROWS(Date("2018-00-00"));
    }

    SECTION("yyyyMMdd") {
        Date d("20181011");
        REQUIRE(d.year() == 2018);
        REQUIRE(d.month() == 10);
        REQUIRE(d.day() == 11);
    }

    SECTION("set yyyy,MM,dd") {
        Date d;
        d.set(2018, 10, 11);
        REQUIRE(d.year() == 2018);
        REQUIRE(d.month() == 10);
        REQUIRE(d.day() == 11);
    }

    SECTION("set Date") {
        Date d;
        d.set(Date(2018, 10, 11));
        REQUIRE(d.year() == 2018);
        REQUIRE(d.month() == 10);
        REQUIRE(d.day() == 11);
    }

    SECTION("set string") {
        Date d;
        d.set("2018-10-11");
        REQUIRE(d.year() == 2018);
        REQUIRE(d.month() == 10);
        REQUIRE(d.day() == 11);

        d.set("2019/2/1");
        REQUIRE(d.year() == 2019);
        REQUIRE(d.month() == 2);
        REQUIRE(d.day() == 1);
    }

    SECTION("dayOfMonth") {
        REQUIRE(Date(2016, 2, 1).daysOfMonth() == 29);
        REQUIRE(Date(2018, 2, 1).daysOfMonth() == 28);
    }

    SECTION("dayOfYear") {
        REQUIRE(Date(2016, 3, 1).dayOfYear() == 31 + 29 + 1);
    }

    SECTION("plusDay") {
        Date d1(2018, 1, 31);
        d1.plusDay(1);
        REQUIRE(d1.month() == 2);
        REQUIRE(d1.day() == 1);

        Date d2(2018, 1, 1);
        d2.plusDay(-1);
        REQUIRE(d2.format() == "2017-12-31");
        REQUIRE(d2.year() == 2017);
        REQUIRE(d2.month() == 12);
        REQUIRE(d2.day() == 31);
    }

    SECTION("operator") {
        Date d1(2018, 1, 1);
        Date d2(2017, 12, 31);
        REQUIRE(d1 == Date(2018, 1, 1));
        REQUIRE(d1 >= Date(2018, 1, 1));
        REQUIRE(d1 <= Date(2018, 1, 1));
        REQUIRE(d2 + 1 == d1);
        REQUIRE(d1 - 1 == d2);
        REQUIRE(d1 - d2 == 1);
        REQUIRE(d1 > d2);
        REQUIRE(d1 >= d2);
        REQUIRE(d2 < d1);
        REQUIRE(d2 <= d1);
        REQUIRE(d2 != d1);
    }

    SECTION("format") {
        REQUIRE(Date(2018, 10, 11).format() == "2018-10-11");
        REQUIRE(Date(2018, 1, 1).format() == "2018-01-01");
    }

    SECTION("toString") {
        REQUIRE(Date(2018, 10, 11).toString() == "2018-10-11");
        REQUIRE(Date(2018, 1, 1).toString() == "2018-01-01");
    }

    SECTION("Compare") {
        Date d1(2018, 1, 1);
        Date d2(2017, 12, 31);
        REQUIRE(Date::Compare(d1, Date(2018, 1, 1)) == 0);
        REQUIRE(Date::Compare(d1, d2) > 0);
        REQUIRE(Date::Compare(d2, d1) < 0);
    }

    SECTION("Diff") {
        Date d1(2018, 1, 1);
        Date d2(2017, 12, 31);
        REQUIRE(Date::Diff(d1, Date(2018, 1, 1)) == 0);
        REQUIRE(Date::Diff(d1, d2) == -1);
        REQUIRE(Date::Diff(d2, d1) == 1);
    }
}
