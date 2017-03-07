/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _DARKFEED_SCHEMAS_SBE_PRICE_H_
#define _DARKFEED_SCHEMAS_SBE_PRICE_H_

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

#include "Currency.h"

using namespace sbe;

namespace darkfeed
{
namespace schemas
{
namespace sbe
{

class Price {
 private:
    char *m_buffer;
    std::uint64_t m_bufferLength;
    std::uint64_t m_offset;
    std::uint64_t m_actingVersion;

    inline void
    reset(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        if (SBE_BOUNDS_CHECK_EXPECT(((offset + 7) > bufferLength), false))
        {
            throw std::runtime_error("buffer too short for flyweight [E107]");
        }
        m_buffer = buffer;
        m_bufferLength = bufferLength;
        m_offset = offset;
        m_actingVersion = actingVersion;
    }

 public:
    Price() : m_buffer(nullptr), m_offset(0)
    {}

    Price(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingVersion);
    }

    Price &
    wrap(char *buffer, const std::uint64_t offset, const std::uint64_t actingVersion, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, actingVersion);
        return *this;
    }

    static SBE_CONSTEXPR std::uint64_t encodedLength()
    {
        return 7;
    }

    std::uint64_t offset() const
    {
        return m_offset;
    }

    char *buffer()
    {
        return m_buffer;
    }


    static SBE_CONSTEXPR std::uint32_t priceNullValue()
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t priceMinValue()
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t priceMaxValue()
    {
        return 4294967293;
    }

    static SBE_CONSTEXPR std::size_t priceEncodingLength()
    {
        return 4;
    }

    std::uint32_t price() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *) (m_buffer + m_offset + 0)));
    }

    Price &price(const std::uint32_t value)
    {
        *((std::uint32_t *) (m_buffer + m_offset + 0)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::int8_t precisionNullValue()
    {
        return SBE_NULLVALUE_INT8;
    }

    static SBE_CONSTEXPR std::int8_t precisionMinValue()
    {
        return (std::int8_t) -127;
    }

    static SBE_CONSTEXPR std::int8_t precisionMaxValue()
    {
        return (std::int8_t) 127;
    }

    static SBE_CONSTEXPR std::size_t precisionEncodingLength()
    {
        return 1;
    }

    std::int8_t precision() const
    {
        return (*((std::int8_t *) (m_buffer + m_offset + 4)));
    }

    Price &precision(const std::int8_t value)
    {
        *((std::int8_t *) (m_buffer + m_offset + 4)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint8_t tick_sizeNullValue()
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t tick_sizeMinValue()
    {
        return (std::uint8_t) 0;
    }

    static SBE_CONSTEXPR std::uint8_t tick_sizeMaxValue()
    {
        return (std::uint8_t) 254;
    }

    static SBE_CONSTEXPR std::size_t tick_sizeEncodingLength()
    {
        return 1;
    }

    std::uint8_t tick_size() const
    {
        return (*((std::uint8_t *) (m_buffer + m_offset + 5)));
    }

    Price &tick_size(const std::uint8_t value)
    {
        *((std::uint8_t *) (m_buffer + m_offset + 5)) = (value);
        return *this;
    }

    Currency::Value currency() const
    {
        return Currency::get((*((std::uint8_t *) (m_buffer + m_offset + 6))));
    }

    Price &currency(const Currency::Value value)
    {
        *((std::uint8_t *) (m_buffer + m_offset + 6)) = (value);
        return *this;
    }
    static SBE_CONSTEXPR std::size_t currencyEncodingLength()
    {
        return 1;
    }
};
}
}
}
#endif
