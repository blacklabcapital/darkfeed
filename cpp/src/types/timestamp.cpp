#include "darkfeed/types/timestamp.hpp"
#include <civil_time.h>
#include <time_zone.h>
#include <sstream>
#include "../holiday_hash.hpp"
#include <re2/re2.h>

// Regex for parsing ISO 8601 timestamp AND FIX timestamp
static const re2::RE2 TIMESTAMP_REGEX(R"((\d{4})-{0,1}(\d{2})-{0,1}(\d{2})[T|\s|-](\d{2}):(\d{2}):(\d{2}).{0,1}(\d*)([+|-]\d+){0,1})");
static cctz::time_zone utc;

namespace darkfeed
{
CivilTime::CivilTime()
{
    year = 0;
    month = 0;
    day = 0;
    hour = 0;
    minute = 0;
    second = 0;
    dow = 0;
    nanosecond = 0;
    offset = 0;
    dst = false;
}

Timestamp::Timestamp()
{
    ts = 0;
    ns = 0;
    offset = 0;
    dst = false;
}

Timestamp::Timestamp(std::time_t unix, std::uint32_t nano, std::int8_t utc_offset, bool dst_status)
{
    ts = unix;
    ns = nano;
    offset = (std::int8_t) utc_offset;
    dst = dst_status;
}

Timestamp::Timestamp(const std::string &input)
{
    offset = 0;
    std::string Y, M, D, h, m, s, fs, tzo;
    // the input
    if (!re2::RE2::FullMatch(input, TIMESTAMP_REGEX, &Y, &M, &D, &h, &m, &s, &fs, &tzo))
    {
        std::stringstream ss;
        ss << input << " is not a valid ISO8601 or FIX timestamp";
        throw std::invalid_argument(ss.str());
    }
    int year = std::stoi(Y);
    if (year < 1900 || year > 3000)
        throw std::invalid_argument("invalid year");
    int month = std::stoi(M);
    if (month < 1 || month > 12)
        throw std::invalid_argument("invalid month");
    int day = std::stoi(D);
    if (day < 1 || day > 31)
        throw std::invalid_argument("invalid day");
    int hour = std::stoi(h);
    if (hour < 0 || hour > 23)
        throw std::invalid_argument("invalid hour");
    int minute = std::stoi(m);
    if (minute < 0 || minute > 59)
        throw std::invalid_argument("invalid minute");
    int second = std::stoi(s);
    if (second < 0 || second > 59)
        throw std::invalid_argument("invalid second");
    if (fs != "")
    {
        // check what kind of fractional second we have
        unsigned int frac_second = (unsigned int) std::stoi(fs);
        switch (fs.size())
        {
        case 2:  // hundredths of a second
            ns = frac_second * 10000000;
            break;
        case 3:  // millisecond
            ns = frac_second * 1000000;
            break;
        case 6:  // microsecond
            ns = frac_second * 1000;
            break;
        case 9:  // nanosecond
            ns = frac_second;
            break;
        default:
            throw std::invalid_argument(
                "invalid fractional second. Only hundredths, milliseconds, microseconds, and nanoseconds are supported");
        }
    }

    int timezone_offset = 0;
    if (tzo != "")
    {
        timezone_offset = std::stoi(tzo);
        if (timezone_offset != 0)
            throw std::invalid_argument("Non UTC timestamps are currently unsupported");
    }

    auto abs_time = cctz::convert(cctz::civil_second(year, month, day, hour, minute, second), utc);
    offset = 0;
    dst = false;
    ts = std::chrono::system_clock::to_time_t(abs_time);
}

Timestamp::Timestamp(const CivilTime &c)
{
    auto abs_time = cctz::convert(cctz::civil_second(c.year, c.month, c.day, c.hour, c.minute, c.second), utc);
    ts = std::chrono::system_clock::to_time_t(abs_time);
    //shift TS by the UTC offset since this was a local time
    ts -= 60 * 60 * c.offset;
    ns = c.nanosecond;
    offset = c.offset;
    dst = c.dst;
}

void Timestamp::now()
{
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    ts = t.tv_sec;
    ns = (uint32_t) t.tv_nsec;
}

CivilTime Timestamp::get_civiltime() const
{
    auto cs = cctz::convert(std::chrono::system_clock::from_time_t(ts + 60 * 60 * offset), utc);
    CivilTime c;
    c.year = (uint16_t) cs.year();
    c.month = (uint8_t) cs.month();
    c.day = (uint8_t) cs.day();
    c.hour = (uint8_t) cs.hour();
    c.minute = (uint8_t) cs.minute();
    c.second = (uint8_t) cs.second();
    c.nanosecond = ns;
    cctz::civil_day cd = cctz::civil_day(cs.year(), cs.month(), cs.day());
    c.dow = static_cast<std::uint8_t>(cctz::get_weekday(cd));
    c.doy = (uint16_t) ((int) c.day + (((int) c.month < 3) ?
                                       (306 * (int) c.month - 301) / 10 :
                                       (306 * (int) c.month - 913) / 10
                                       + (((int) c.year % 4 == 0
                                           && ((int) c.year % 100 != 0 || (int) c.year % 400 == 0)) ? 60 : 59)));
    c.offset = offset;
    c.dst = dst;
    return c;
}

CivilTime Timestamp::get_utc_civiltime() const
{
    auto cs = cctz::convert(std::chrono::system_clock::from_time_t(ts), utc);
    CivilTime c;
    c.year = (uint16_t) cs.year();
    c.month = (uint8_t) cs.month();
    c.day = (uint8_t) cs.day();
    auto cd = cctz::civil_day(cs.year(), cs.month(), cs.day());
    c.dow = static_cast<std::uint8_t>(cctz::get_weekday(cd));
    c.doy = (uint16_t) ((int) c.day + (((int) c.month < 3) ?
                                       (306 * (int) c.month - 301) / 10 :
                                       (306 * (int) c.month - 913) / 10
                                       + (((int) c.year % 4 == 0
                                           && ((int) c.year % 100 != 0 || (int) c.year % 400 == 0)) ? 60
                                                                                                    : 59)));
    c.hour = (uint8_t) cs.hour();
    c.minute = (uint8_t) cs.minute();
    c.second = (uint8_t) cs.second();
    c.nanosecond = ns;
    c.offset = 0;
    c.dst = false;
    return c;
}

std::string Timestamp::iso8601() const
{
    auto c = get_civiltime();
    char str_buf[64];
    if (offset < 0)
    {
        sprintf(str_buf, "%04d-%02d-%02dT%02d:%02d:%02d.%06d%02d", c.year, c.month, c.day, c.hour, c.minute,
                c.second, c.nanosecond / 1000, offset);
    }
    else
    {
        sprintf(str_buf, "%04d-%02d-%02dT%02d:%02d:%02d.%06d+%02d", c.year, c.month, c.day, c.hour, c.minute,
                c.second, c.nanosecond / 1000, offset);
    }
    return std::string(str_buf);
}

std::string Timestamp::iso8601Date() const
{
    auto c = get_civiltime();
    char str_buf[64];
    sprintf(str_buf, "%04d-%02d-%02d", c.year, c.month, c.day);
    return std::string(str_buf);
}

std::string Timestamp::iso8601UTC() const
{
    auto c = get_utc_civiltime();
    char str_buf[64];
    if (offset < 0)
    {
        sprintf(str_buf, "%04d-%02d-%02dT%02d:%02d:%02d.%06d%02d", c.year, c.month, c.day, c.hour, c.minute,
                c.second, c.nanosecond / 1000, offset);
    }
    else
    {
        sprintf(str_buf, "%04d-%02d-%02dT%02d:%02d:%02d.%06d+%02d", c.year, c.month, c.day, c.hour, c.minute,
                c.second, c.nanosecond / 1000, offset);
    }
    return std::string(str_buf);
}

std::string Timestamp::iso8601DateUTC() const
{
    auto c = get_utc_civiltime();
    char str_buf[64];
    sprintf(str_buf, "%04d-%02d-%02d", c.year, c.month, c.day);
    return std::string(str_buf);
}

std::string Timestamp::FIX() const
{
    auto c = get_utc_civiltime();
    char str_buf[64];
    sprintf(str_buf, "%04d%02d%02d-%02d:%02d:%02d.%06d", c.year, c.month, c.day, c.hour,
            (int) c.minute, (int) c.second, ns / 1000);
    return std::string(str_buf);
}

bool Timestamp::is_holiday() const
{
    HolidayHash hh;
    std::string d = iso8601Date();
    return hh.in_word_set(d.c_str(), (unsigned int) d.length()) != nullptr;
}

bool Timestamp::is_weekend() const
{
    auto ct = get_civiltime();
    return ct.dow == 5 || ct.dow == 6;
}

}  // darkfeed
