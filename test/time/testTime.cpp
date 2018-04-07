#include "time/Time.h"
#include "catch.hpp"

using namespace std;
using namespace ldf;

TEST_CASE("Constructor", "[time]") {

    SECTION("now") {
        Time t(15, 10, 22);
        REQUIRE(t.hour() == 15);
        REQUIRE(t.minute() == 10);
        REQUIRE(t.second() == 22);
    }

    SECTION("copy") {
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
    }

    SECTION("hhmmss") {
        Time t("121314");
        REQUIRE(t.hour() == 12);
        REQUIRE(t.minute() == 13);
        REQUIRE(t.second() == 14);
    }

    SECTION("hhmmss - invalid") {
        CHECK_THROWS(Time("10121a"));
        CHECK_THROWS(Time("123"));
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
}
