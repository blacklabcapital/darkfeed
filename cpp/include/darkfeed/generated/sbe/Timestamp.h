/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _DARKFEED_SCHEMAS_SBE_TIMESTAMP_H_
#define _DARKFEED_SCHEMAS_SBE_TIMESTAMP_H_

#if defined(SBE_HAVE_CMATH)
/* cmath needed for std::numeric_limits<double>::quiet_NaN() */
#  include <cmath>
#  define SBE_FLOAT_NAN std::numeric_limits<float>::quiet_NaN()
#  define SBE_DOUBLE_NAN std::numeric_limits<double>::quiet_NaN()
#else
/* math.h needed for NAN */
#  include <math.h>
#  define SBE_FLOAT_NAN NAN
#  define SBE_DOUBLE_NAN NAN
#endif

#if __cplusplus >= 201103L
#  include <cstdint>
#  include <string>
#  include <cstring>
#endif

#if __cplusplus >= 201103L
#  define SBE_CONSTEXPR constexpr
#else
#  define SBE_CONSTEXPR
#endif

#include <sbe/sbe.h>

#include "Bool.h"

using namespace sbe;

namespace darkfeed
{
namespace schemas
{
namespace sbe
{

class Timestamp {
 private:
    char *m_buffer;
    std::uint64_t m_bufferLength;
    std::uint64_t m_offset;
    std::uint64_t m_actingVersion;

    inline void
    reset(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        if (SBE_BOUNDS_CHECK_EXPECT(((offset + 14) > bufferLength), false))
        {
            throw std::runtime_error("buffer too short for flyweight [E107]");
        }
        m_buffer = buffer;
        m_bufferLength = bufferLength;
        m_offset = offset;
        m_actingVersion = actingVersion;
    }

 public:
    Timestamp() : m_buffer(nullptr), m_offset(0)
    {}

    Timestamp(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingVersion);
    }

    Timestamp &
    wrap(char *buffer, const std::uint64_t offset, const std::uint64_t actingVersion, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, actingVersion);
        return *this;
    }

    static SBE_CONSTEXPR std::uint64_t encodedLength()
    {
        return 14;
    }

    std::uint64_t offset() const
    {
        return m_offset;
    }

    char *buffer()
    {
        return m_buffer;
    }


    static SBE_CONSTEXPR std::uint64_t unixNullValue()
    {
        return SBE_NULLVALUE_UINT64;
    }

    static SBE_CONSTEXPR std::uint64_t unixMinValue()
    {
        return 0x0L;
    }

    static SBE_CONSTEXPR std::uint64_t unixMaxValue()
    {
        return 0xfffffffffffffffeL;
    }

    static SBE_CONSTEXPR std::size_t unixEncodingLength()
    {
        return 8;
    }

    std::uint64_t unix() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_64(*((std::uint64_t *) (m_buffer + m_offset + 0)));
    }

    Timestamp &unix(const std::uint64_t value)
    {
        *((std::uint64_t *) (m_buffer + m_offset + 0)) = SBE_LITTLE_ENDIAN_ENCODE_64(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint32_t nsNullValue()
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t nsMinValue()
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t nsMaxValue()
    {
        return 4294967293;
    }

    static SBE_CONSTEXPR std::size_t nsEncodingLength()
    {
        return 4;
    }

    std::uint32_t ns() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *) (m_buffer + m_offset + 8)));
    }

    Timestamp &ns(const std::uint32_t value)
    {
        *((std::uint32_t *) (m_buffer + m_offset + 8)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::int8_t utc_offsetNullValue()
    {
        return SBE_NULLVALUE_INT8;
    }

    static SBE_CONSTEXPR std::int8_t utc_offsetMinValue()
    {
        return (std::int8_t) -127;
    }

    static SBE_CONSTEXPR std::int8_t utc_offsetMaxValue()
    {
        return (std::int8_t) 127;
    }

    static SBE_CONSTEXPR std::size_t utc_offsetEncodingLength()
    {
        return 1;
    }

    std::int8_t utc_offset() const
    {
        return (*((std::int8_t *) (m_buffer + m_offset + 12)));
    }

    Timestamp &utc_offset(const std::int8_t value)
    {
        *((std::int8_t *) (m_buffer + m_offset + 12)) = (value);
        return *this;
    }

    Bool::Value dst() const
    {
        return Bool::get((*((std::uint8_t *) (m_buffer + m_offset + 13))));
    }

    Timestamp &dst(const Bool::Value value)
    {
        *((std::uint8_t *) (m_buffer + m_offset + 13)) = (value);
        return *this;
    }
    static SBE_CONSTEXPR std::size_t dstEncodingLength()
    {
        return 1;
    }
};
}
}
}
#endif
