/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _DARKFEED_SCHEMAS_SBE_MESSAGEHEADER_H_
#define _DARKFEED_SCHEMAS_SBE_MESSAGEHEADER_H_

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


using namespace sbe;

namespace darkfeed
{
namespace schemas
{
namespace sbe
{

class MessageHeader {
 private:
    char *m_buffer;
    std::uint64_t m_bufferLength;
    std::uint64_t m_offset;
    std::uint64_t m_actingVersion;

    inline void
    reset(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        if (SBE_BOUNDS_CHECK_EXPECT(((offset + 12) > bufferLength), false))
        {
            throw std::runtime_error("buffer too short for flyweight [E107]");
        }
        m_buffer = buffer;
        m_bufferLength = bufferLength;
        m_offset = offset;
        m_actingVersion = actingVersion;
    }

 public:
    MessageHeader() : m_buffer(nullptr), m_offset(0)
    {}

    MessageHeader(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingVersion);
    }

    MessageHeader &
    wrap(char *buffer, const std::uint64_t offset, const std::uint64_t actingVersion, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, actingVersion);
        return *this;
    }

    static SBE_CONSTEXPR std::uint64_t encodedLength()
    {
        return 12;
    }

    std::uint64_t offset() const
    {
        return m_offset;
    }

    char *buffer()
    {
        return m_buffer;
    }


    static SBE_CONSTEXPR std::uint16_t checksumNullValue()
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t checksumMinValue()
    {
        return (std::uint16_t) 0;
    }

    static SBE_CONSTEXPR std::uint16_t checksumMaxValue()
    {
        return (std::uint16_t) 65534;
    }

    static SBE_CONSTEXPR std::size_t checksumEncodingLength()
    {
        return 2;
    }

    std::uint16_t checksum() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *) (m_buffer + m_offset + 0)));
    }

    MessageHeader &checksum(const std::uint16_t value)
    {
        *((std::uint16_t *) (m_buffer + m_offset + 0)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t msgLengthNullValue()
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t msgLengthMinValue()
    {
        return (std::uint16_t) 0;
    }

    static SBE_CONSTEXPR std::uint16_t msgLengthMaxValue()
    {
        return (std::uint16_t) 65534;
    }

    static SBE_CONSTEXPR std::size_t msgLengthEncodingLength()
    {
        return 2;
    }

    std::uint16_t msgLength() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *) (m_buffer + m_offset + 2)));
    }

    MessageHeader &msgLength(const std::uint16_t value)
    {
        *((std::uint16_t *) (m_buffer + m_offset + 2)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t blockLengthNullValue()
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t blockLengthMinValue()
    {
        return (std::uint16_t) 0;
    }

    static SBE_CONSTEXPR std::uint16_t blockLengthMaxValue()
    {
        return (std::uint16_t) 65534;
    }

    static SBE_CONSTEXPR std::size_t blockLengthEncodingLength()
    {
        return 2;
    }

    std::uint16_t blockLength() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *) (m_buffer + m_offset + 4)));
    }

    MessageHeader &blockLength(const std::uint16_t value)
    {
        *((std::uint16_t *) (m_buffer + m_offset + 4)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t templateIdNullValue()
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t templateIdMinValue()
    {
        return (std::uint16_t) 0;
    }

    static SBE_CONSTEXPR std::uint16_t templateIdMaxValue()
    {
        return (std::uint16_t) 65534;
    }

    static SBE_CONSTEXPR std::size_t templateIdEncodingLength()
    {
        return 2;
    }

    std::uint16_t templateId() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *) (m_buffer + m_offset + 6)));
    }

    MessageHeader &templateId(const std::uint16_t value)
    {
        *((std::uint16_t *) (m_buffer + m_offset + 6)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t schemaIdNullValue()
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t schemaIdMinValue()
    {
        return (std::uint16_t) 0;
    }

    static SBE_CONSTEXPR std::uint16_t schemaIdMaxValue()
    {
        return (std::uint16_t) 65534;
    }

    static SBE_CONSTEXPR std::size_t schemaIdEncodingLength()
    {
        return 2;
    }

    std::uint16_t schemaId() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *) (m_buffer + m_offset + 8)));
    }

    MessageHeader &schemaId(const std::uint16_t value)
    {
        *((std::uint16_t *) (m_buffer + m_offset + 8)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t versionNullValue()
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t versionMinValue()
    {
        return (std::uint16_t) 0;
    }

    static SBE_CONSTEXPR std::uint16_t versionMaxValue()
    {
        return (std::uint16_t) 65534;
    }

    static SBE_CONSTEXPR std::size_t versionEncodingLength()
    {
        return 2;
    }

    std::uint16_t version() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *) (m_buffer + m_offset + 10)));
    }

    MessageHeader &version(const std::uint16_t value)
    {
        *((std::uint16_t *) (m_buffer + m_offset + 10)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }
};
}
}
}
#endif
