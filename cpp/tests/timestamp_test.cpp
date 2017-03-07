#define GTEST_HAS_TR1_TUPLE 0
#include <gtest/gtest.h>
#include <chrono>
#include "darkfeed/types/timestamp.hpp"

TEST(Timestamp, DefaultConstructor)
{
    darkfeed::Timestamp t;
    ASSERT_EQ((std::uint32_t)0, t.ts);
    ASSERT_EQ((std::uint32_t)0, t.ns);
    ASSERT_EQ(0, t.offset);
    ASSERT_EQ(false, t.dst);
}

TEST(Timestamp, StringConstructor)
{
    //ISO 8601 timestamp with "T" and no fractional seconds
    darkfeed::Timestamp ts1("2016-05-06T13:11:51");
    auto ct = ts1.get_civiltime();
    ASSERT_EQ(2016, ct.year);
    ASSERT_EQ(5, ct.month);
    ASSERT_EQ(6, ct.day);
    ASSERT_EQ(13, ct.hour);
    ASSERT_EQ(11, ct.minute);
    ASSERT_EQ(51, ct.second);
    //ISO 8601 timestamp with "T" and fractional milliseconds
    darkfeed::Timestamp ts2("2016-05-06T13:11:51.314");
    ct = ts2.get_civiltime();
    ASSERT_EQ(2016, ct.year);
    ASSERT_EQ(5, ct.month);
    ASSERT_EQ(6, ct.day);
    ASSERT_EQ(13, ct.hour);
    ASSERT_EQ(11, ct.minute);
    ASSERT_EQ(51, ct.second);
    ASSERT_EQ((std::uint32_t)314000000, ct.nanosecond);
    //ISO 8601 timestamp with "T" and fractional microseconds
    darkfeed::Timestamp ts3("2016-05-06T13:11:51.314151");
    ct = ts3.get_civiltime();
    ASSERT_EQ(2016, ct.year);
    ASSERT_EQ(5, ct.month);
    ASSERT_EQ(6, ct.day);
    ASSERT_EQ(13, ct.hour);
    ASSERT_EQ(11, ct.minute);
    ASSERT_EQ(51, ct.second);
    ASSERT_EQ((std::uint32_t)314151000, ct.nanosecond);

    //ISO 8601 timestamp with space and no fractional seconds
    darkfeed::Timestamp ts4("2016-05-06 13:11:51");
    ct = ts4.get_civiltime();
    ASSERT_EQ(2016, ct.year);
    ASSERT_EQ(5, ct.month);
    ASSERT_EQ(6, ct.day);
    ASSERT_EQ(13, ct.hour);
    ASSERT_EQ(11, ct.minute);
    ASSERT_EQ(51, ct.second);

    //ISO 8601 timestamp with space and fractional milliseconds
    darkfeed::Timestamp ts5("2016-05-06 13:11:51.314");
    ct = ts5.get_civiltime();
    ASSERT_EQ(2016, ct.year);
    ASSERT_EQ(5, ct.month);
    ASSERT_EQ(6, ct.day);
    ASSERT_EQ(13, ct.hour);
    ASSERT_EQ(11, ct.minute);
    ASSERT_EQ(51, ct.second);
    ASSERT_EQ((std::uint32_t)314000000, ct.nanosecond);

    //ISO 8601 timestamp with space and fractional microseconds
    darkfeed::Timestamp ts6("2016-05-06 13:11:51.314151");
    ct = ts6.get_civiltime();
    ASSERT_EQ(2016, ct.year);
    ASSERT_EQ(5, ct.month);
    ASSERT_EQ(6, ct.day);
    ASSERT_EQ(13, ct.hour);
    ASSERT_EQ(11, ct.minute);
    ASSERT_EQ(51, ct.second);
    ASSERT_EQ((std::uint32_t)314151000, ct.nanosecond);

    //FIX UTCTimestamp with no fractional seconds
    darkfeed::Timestamp fix1("20160506-13:11:51");
    ct = fix1.get_civiltime();
    ASSERT_EQ(2016, ct.year);
    ASSERT_EQ(5, ct.month);
    ASSERT_EQ(6, ct.day);
    ASSERT_EQ(13, ct.hour);
    ASSERT_EQ(11, ct.minute);
    ASSERT_EQ(51, ct.second);

    //FIX UTCTimestamp fractional milliseconds
    darkfeed::Timestamp fix2("20160506-13:11:51.314");
    ct = fix2.get_civiltime();
    ASSERT_EQ(2016, ct.year);
    ASSERT_EQ(5, ct.month);
    ASSERT_EQ(6, ct.day);
    ASSERT_EQ(13, ct.hour);
    ASSERT_EQ(11, ct.minute);
    ASSERT_EQ(51, ct.second);
    ASSERT_EQ((std::uint32_t)314000000, ct.nanosecond);

    //FIX UTCTimestamp with fractional microseconds
    darkfeed::Timestamp fix3("20160506-13:11:51.314151");
    ct = fix3.get_civiltime();
    ASSERT_EQ(2016, ct.year);
    ASSERT_EQ(5, ct.month);
    ASSERT_EQ(6, ct.day);
    ASSERT_EQ(13, ct.hour);
    ASSERT_EQ(11, ct.minute);
    ASSERT_EQ(51, ct.second);
    ASSERT_EQ((std::uint32_t)314151000, ct.nanosecond);
}

TEST(Timestamp, CivilTimeConstructor)
{
    darkfeed::CivilTime ct;
    ct.year = 2015;
    ct.month = 7;
    ct.day = 13;
    ct.hour = 9;
    ct.minute = 31;
    ct.second = 5;
    ct.nanosecond = 131451;
    ct.offset = -4;
    ct.dst = true;

    darkfeed::Timestamp t(ct);
    auto cct = t.get_civiltime();
    ASSERT_EQ(ct.year, cct.year);
    ASSERT_EQ(ct.month, cct.month);
    ASSERT_EQ(ct.day, cct.day);
    ASSERT_EQ(ct.hour, cct.hour);
    ASSERT_EQ(ct.minute, cct.minute);
    ASSERT_EQ(ct.second, cct.second);
    ASSERT_EQ(ct.nanosecond, cct.nanosecond);
    ASSERT_EQ(ct.offset, cct.offset);
}

TEST(Timestamp, LessThanComparison)
{
    darkfeed::Timestamp a(1468610956, 0, 0, false);
    darkfeed::Timestamp b(1468610956, 0, 0, false);
    EXPECT_EQ(false, a < b);

    b.ns += 100;
    EXPECT_EQ(true, a < b);
    b.ns = 0;
    b.ts -= 6000;
    EXPECT_EQ(false, a < b);
}

TEST(Timestamp, GetCivilTime)
{
    darkfeed::CivilTime ct;
    ct.year = 2015;
    ct.month = 7;
    ct.day = 13;
    ct.hour = 9;
    ct.minute = 31;
    ct.second = 5;
    ct.nanosecond = 131451;
    ct.offset = -4;
    ct.dst = true;

    darkfeed::Timestamp t(ct);
    auto cct = t.get_civiltime();
    ASSERT_EQ(ct.year, cct.year);
    ASSERT_EQ(ct.month, cct.month);
    ASSERT_EQ(ct.day, cct.day);
    ASSERT_EQ(ct.hour, cct.hour);
    ASSERT_EQ(ct.minute, cct.minute);
    ASSERT_EQ(ct.second, cct.second);
    ASSERT_EQ(ct.nanosecond, cct.nanosecond);
    ASSERT_EQ(ct.offset, cct.offset);
}

TEST(Timetamp, GetUTCCivilTime)
{
    darkfeed::CivilTime ct;
    ct.year = 2015;
    ct.month = 7;
    ct.day = 13;
    ct.hour = 9;
    ct.minute = 31;
    ct.second = 5;
    ct.nanosecond = 131451;
    ct.offset = -4;
    ct.dst = true;

    darkfeed::Timestamp t(ct);
    auto cct = t.get_utc_civiltime();
    ASSERT_EQ(ct.year, cct.year);
    ASSERT_EQ(ct.month, cct.month);
    ASSERT_EQ(ct.day, cct.day);
    ASSERT_EQ(ct.hour - ct.offset, cct.hour);
    ASSERT_EQ(ct.minute, cct.minute);
    ASSERT_EQ(ct.second, cct.second);
    ASSERT_EQ(ct.nanosecond, cct.nanosecond);
    ASSERT_EQ(0, cct.offset);
}

TEST(Timestamp, LessThanEqComparison)
{
    darkfeed::Timestamp a(1468610956, 0, 0, false);
    darkfeed::Timestamp b(1468610956, 0, 0, false);
    EXPECT_EQ(true, a <= b);

    b.ts += 6000;
    EXPECT_EQ(true, a <= b);
    b.ts = a.ts;
    b.ns += 100;
    EXPECT_EQ(true, a <= b);
    b = a;
    a.ns = 500;
    b.ns = 501;
    EXPECT_EQ(true, a <= b);
    a.ns += 1000;
    EXPECT_EQ(false, a <= b);
}

TEST(Timestamp, GreaterThanComparison)
{
    darkfeed::Timestamp a(1468610956, 0, 0, false);
    darkfeed::Timestamp b(1468610956, 0, 0, false);
    EXPECT_EQ(false, a > b);

    a.ns += 100;
    EXPECT_EQ(true, a > b);
    a.ns = 0;
    a.ts -= 6000;
    EXPECT_EQ(false, a > b);
}

TEST(Timestamp, GreaterThanEqComparison)
{
    darkfeed::Timestamp a(1468610956, 0, 0, false);
    darkfeed::Timestamp b(1468610956, 0, 0, false);
    EXPECT_EQ(true, a >= b);

    a.ts += 6000;
    EXPECT_EQ(true, a >= b);
    a.ts = b.ts;
    a.ns += 100;
    EXPECT_EQ(true, a >= b);
    a = b;
    b.ns = 500;
    a.ns = 501;
    EXPECT_EQ(true, a >= b);
    a.ts -= 10000;
    EXPECT_EQ(false, a >= b);
}

TEST(Timestamp, EqComparison)
{
    darkfeed::Timestamp a(1468610956, 0, 0, false);
    darkfeed::Timestamp b(1468610956, 0, 0, false);
    ASSERT_EQ(true, a == b);
}

TEST(Timestamp, NeqComparison)
{
    darkfeed::Timestamp a(1468610956, 0, 0, false);
    darkfeed::Timestamp b(1468610957, 0, 0, false);
    ASSERT_EQ(true, a != b);
}

TEST(Timestamp, ISO8601Date)
{
    darkfeed::Timestamp t(1436792461, 0, 0, false);
    ASSERT_TRUE(t.iso8601Date() == "2015-07-13");
}

TEST(Timestamp, IsHoliday)
{
    // New Year's 2015
    darkfeed::Timestamp nye15(1420119540, 0, 0, false);
    ASSERT_TRUE(nye15.is_holiday());
    // January 2nd, 2015
    darkfeed::Timestamp t1(1420191000, 0, 0, false);
    ASSERT_FALSE(t1.is_holiday());
}
