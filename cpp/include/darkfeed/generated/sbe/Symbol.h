/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _DARKFEED_SCHEMAS_SBE_SYMBOL_H_
#define _DARKFEED_SCHEMAS_SBE_SYMBOL_H_

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

#include "MIC.h"
#include "IssueType.h"

using namespace sbe;

namespace darkfeed
{
namespace schemas
{
namespace sbe
{

class Symbol {
 private:
    char *m_buffer;
    std::uint64_t m_bufferLength;
    std::uint64_t m_offset;
    std::uint64_t m_actingVersion;

    inline void
    reset(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        if (SBE_BOUNDS_CHECK_EXPECT(((offset + 11) > bufferLength), false))
        {
            throw std::runtime_error("buffer too short for flyweight [E107]");
        }
        m_buffer = buffer;
        m_bufferLength = bufferLength;
        m_offset = offset;
        m_actingVersion = actingVersion;
    }

 public:
    Symbol() : m_buffer(nullptr), m_offset(0)
    {}

    Symbol(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingVersion);
    }

    Symbol &
    wrap(char *buffer, const std::uint64_t offset, const std::uint64_t actingVersion, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, actingVersion);
        return *this;
    }

    static SBE_CONSTEXPR std::uint64_t encodedLength()
    {
        return 11;
    }

    std::uint64_t offset() const
    {
        return m_offset;
    }

    char *buffer()
    {
        return m_buffer;
    }


    static SBE_CONSTEXPR char rootNullValue()
    {
        return (char) 0;
    }

    static SBE_CONSTEXPR char rootMinValue()
    {
        return (char) 32;
    }

    static SBE_CONSTEXPR char rootMaxValue()
    {
        return (char) 126;
    }

    static SBE_CONSTEXPR std::size_t rootEncodingLength()
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t rootLength()
    {
        return 8;
    }

    const char *root() const
    {
        return (m_buffer + m_offset + 0);
    }

    char root(const std::uint64_t index) const
    {
        if (index >= 8)
        {
            throw std::runtime_error("index out of range for root [E104]");
        }

        return (*((char *) (m_buffer + m_offset + 0 + (index * 1))));
    }

    void root(const std::uint64_t index, const char value)
    {
        if (index >= 8)
        {
            throw std::runtime_error("index out of range for root [E105]");
        }

        *((char *) (m_buffer + m_offset + 0 + (index * 1))) = (value);
    }

    std::uint64_t getRoot(char *dst, const std::uint64_t length) const
    {
        if (length > 8)
        {
            throw std::runtime_error("length too large for getRoot [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 0, length);
        return length;
    }

    Symbol &putRoot(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 0, src, 8);
        return *this;
    }

    std::string getRootAsString() const
    {
        std::string result(m_buffer + m_offset + 0, 8);
        return result;
    }

    Symbol &putRoot(const std::string &str)
    {
        std::memcpy(m_buffer + m_offset + 0, str.c_str(), 8);
        return *this;
    }


    static SBE_CONSTEXPR char seriesNullValue()
    {
        return (char) 0;
    }

    static SBE_CONSTEXPR char seriesMinValue()
    {
        return (char) 32;
    }

    static SBE_CONSTEXPR char seriesMaxValue()
    {
        return (char) 126;
    }

    static SBE_CONSTEXPR std::size_t seriesEncodingLength()
    {
        return 1;
    }

    char series() const
    {
        return (*((char *) (m_buffer + m_offset + 8)));
    }

    Symbol &series(const char value)
    {
        *((char *) (m_buffer + m_offset + 8)) = (value);
        return *this;
    }

    MIC::Value listing_exg() const
    {
        return MIC::get((*((std::uint8_t *) (m_buffer + m_offset + 9))));
    }

    Symbol &listing_exg(const MIC::Value value)
    {
        *((std::uint8_t *) (m_buffer + m_offset + 9)) = (value);
        return *this;
    }
    static SBE_CONSTEXPR std::size_t listing_exgEncodingLength()
    {
        return 1;
    }

    IssueType::Value issue_type() const
    {
        return IssueType::get((*((std::uint8_t *) (m_buffer + m_offset + 10))));
    }

    Symbol &issue_type(const IssueType::Value value)
    {
        *((std::uint8_t *) (m_buffer + m_offset + 10)) = (value);
        return *this;
    }
    static SBE_CONSTEXPR std::size_t issue_typeEncodingLength()
    {
        return 1;
    }
};
}
}
}
#endif
