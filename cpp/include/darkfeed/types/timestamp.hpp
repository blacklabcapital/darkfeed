#pragma once

#include <iostream>
#include <ctime>
#include "darkfeed/generated/flatbuffers/timestamps_generated.h"

namespace darkfeed
{
/// @defgroup time
/// @brief primitives for dealing with market timestamps
/// @ingroup types


/// @brief A timestamp broken out in civil format
/// @ingroup time
struct CivilTime {
    std::uint16_t year; ///< gregorian year (eg; 2016)
    std::uint8_t month; ///< calendar month (1= January, 2=February, ...)
    std::uint8_t day;; ///< day of month (starting at 1)
    std::uint8_t hour; ///< hour of day (0 = midnight, 23=11PM)
    std::uint8_t minute; ///< minute of hour
    std::uint8_t second; ///< second of minute
    std::uint32_t nanosecond; ///< nanosecond offset past second
    std::uint8_t dow; ///< day of week (0 = Sunday, 1 = Monday, etc.)
    std::uint16_t doy; ///< day of year (0-365)
    std::int8_t offset; ///< hours offset from UTC
    bool dst; ///< whether DST was active at timezone

    CivilTime(); ///< default constructor
};


/// @brief A high resolution (nanosecond) timestamp with easy civil time conversion
/// @ingroup time
struct Timestamp {
    std::time_t ts; ///< Internal representation of time in UTC
    std::uint32_t ns; ///< Nanosecond offset
    std::int8_t offset;      ///< UTC offset of source time (including DST if active) in HOURS
    bool dst;        ///< Whether DST was active at this location and time (automatically set if timezone is specified)

 public:
    /// @brief Default constructor
    Timestamp();
    /// @brief Full constructor
    /// @param unix Seconds since the unix epoch
    /// @param nano nanoseconds past the unix timestamp
    /// @param utc_offset number of hours + or - GMT
    /// @param dst_status whether DST is active for this timestamp
    /// @return
    Timestamp(std::time_t epoch, std::uint32_t nano = 0, std::int8_t utc_offset = 0, bool dst_status = false);
    /// @brief Construct from ISO 8601 timestamp or FIX timestamp (both at UTC)
    /// @param s the string to process
    /// @return
    Timestamp(const std::string &s);
    /// @brief Construct from a CivilTime object
    /// @param c The CivilTime object to use
    Timestamp(const CivilTime & c);
    /// @brief Constructor from flatbuffers timestamp
    /// @param t The flatbuffers timestamp

    /// @brief Populate timestamp with current host timestamp
    void now();

    bool operator<(const Timestamp &t) const
    {
        return (ts < t.ts) || ((ts == t.ts) && (ns < t.ns));
    }

    bool operator<=(const Timestamp &t) const
    {
        return (ts < t.ts) || ((ts == t.ts) && (ns <= t.ns));
    }

    bool operator>(const Timestamp &t) const
    {
        return (ts > t.ts) || ((ts == t.ts) && (ns > t.ns));
    }

    bool operator>=(const Timestamp &t) const
    {
        return (ts > t.ts) || ((ts == t.ts) && (ns >= t.ns));
    }

    bool operator==(const Timestamp &t) const
    {
        return (ts == t.ts) && (ns == t.ns);
    }

    bool operator!=(const Timestamp &t) const
    {
        return !((ts == t.ts) && (ns == t.ns));
    }

    /// @brief Compares using only dates (not intraday aware)
    /// @param t
    /// @return
    bool operator<<(const Timestamp &t) const
    {
        auto ct1 = get_utc_civiltime();
        auto ct2 = t.get_utc_civiltime();

        return ct1.year * 365 + ct1.doy < ct2.year * 365 + ct2.doy;

    }

    /// @brief Compares using only dates (not intraday aware)
    /// @param t
    /// @return
    bool operator>>(const Timestamp &t) const
    {
        auto ct1 = get_utc_civiltime();
        auto ct2 = t.get_utc_civiltime();

        return ct1.year * 365 + ct1.doy > ct2.year * 365 + ct2.doy;

    }

    /// @brief returns civil time breakdown using supplied offsets/DST
    /// @return
    CivilTime get_civiltime() const;
    /// @brief returns civil time breakdown at UTC
    /// @return
    CivilTime get_utc_civiltime() const;

    /// @brief whether date is NYSE/NASDAQ market holiday
    /// @return
    bool is_holiday() const;
    /// @brief whether date falls on the weekend
    /// @return
    bool is_weekend() const;

    /// @brief returns timestamp as ISO 8601 formatted timestamp (at origin UTC offset)
    /// @return
    std::string iso8601() const;
    /// @brief returns date in ISO 8601 format (at origin UTC offset)
    /// @return
    std::string iso8601Date() const;
    /// @brief return timestamp as ISO 8601 formatted timestamp at UTC
    /// @return
    std::string iso8601UTC() const;
    /// @brief return date in ISO 8601 format (at UTC)
    /// @return
    std::string iso8601DateUTC() const;
    /// @brief return FIX >= 4.2 compatible UTC timestamp
    /// @return
    std::string FIX() const;
};
} // darkfeed
