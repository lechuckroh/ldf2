#include "time/Time.h"
#include "catch.hpp"

using namespace std;
using namespace ldf;

TEST_CASE("Constructor", "[time]") {
    Time t(15, 10, 22);

    SECTION("now") {
        REQUIRE(t.hour() == 15);
        REQUIRE(t.minute() == 10);
        REQUIRE(t.second() == 22);
    }

    SECTION("copy") {
        Time t2(t);
        REQUIRE(t.hour() == 15);
        REQUIRE(t.minute() == 10);
        REQUIRE(t.second() == 22);
    }

    SECTION("hh:mm:ss") {
        Time t2("12:13:14");
        REQUIRE(t2.hour() == 12);
        REQUIRE(t2.minute() == 13);
        REQUIRE(t2.second() == 14);
    }

    SECTION("hh:mm:ss - invalid") {
        CHECK_THROWS(Time("10:12:-1"));
    }

    SECTION("hhmmss") {
        Time t2("121314");
        REQUIRE(t2.hour() == 12);
        REQUIRE(t2.minute() == 13);
        REQUIRE(t2.second() == 14);
    }

    SECTION("hhmmss - invalid") {
        CHECK_THROWS(Time("10121a"));
    }
}
