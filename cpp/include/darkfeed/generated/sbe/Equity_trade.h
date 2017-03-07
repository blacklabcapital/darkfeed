/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _DARKFEED_SCHEMAS_SBE_EQUITY_TRADE_H_
#define _DARKFEED_SCHEMAS_SBE_EQUITY_TRADE_H_

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

#include "MessageHeader.h"
#include "Bool.h"
#include "MIC.h"
#include "Symbol.h"
#include "MIC.h"
#include "IssueType.h"
#include "HaltStatus.h"
#include "Timestamp.h"
#include "TradeCondition.h"
#include "QuoteCondition.h"
#include "Price.h"
#include "Currency.h"
#include "HaltType.h"
#include "OptionType.h"

using namespace sbe;

namespace darkfeed
{
namespace schemas
{
namespace sbe
{

class Equity_trade {
 private:
    char *m_buffer;
    std::uint64_t m_bufferLength;
    std::uint64_t *m_positionPtr;
    std::uint64_t m_offset;
    std::uint64_t m_position;
    std::uint64_t m_actingBlockLength;
    std::uint64_t m_actingVersion;

    inline void reset(
        char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength,
        const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        m_buffer = buffer;
        m_offset = offset;
        m_bufferLength = bufferLength;
        m_actingBlockLength = actingBlockLength;
        m_actingVersion = actingVersion;
        m_positionPtr = &m_position;
        position(offset + m_actingBlockLength);
    }

 public:

    Equity_trade() : m_buffer(nullptr), m_bufferLength(0), m_offset(0)
    {}

    Equity_trade(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    Equity_trade(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength()
    {
        return (std::uint16_t) 54;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId()
    {
        return (std::uint16_t) 4;
    }

    static SBE_CONSTEXPR std::uint16_t sbeSchemaId()
    {
        return (std::uint16_t) 3116;
    }

    static SBE_CONSTEXPR std::uint16_t sbeSchemaVersion()
    {
        return (std::uint16_t) 0;
    }

    static SBE_CONSTEXPR const char *sbeSemanticType()
    {
        return "";
    }

    std::uint64_t offset() const
    {
        return m_offset;
    }

    Equity_trade &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    Equity_trade &wrapForDecode(
        char *buffer, const std::uint64_t offset, const std::uint64_t actingBlockLength,
        const std::uint64_t actingVersion, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, actingBlockLength, actingVersion);
        return *this;
    }

    std::uint64_t position() const
    {
        return m_position;
    }

    void position(const std::uint64_t position)
    {
        if (SBE_BOUNDS_CHECK_EXPECT((position > m_bufferLength), false))
        {
            throw std::runtime_error("buffer too short [E100]");
        }
        m_position = position;
    }

    std::uint64_t encodedLength() const
    {
        return position() - m_offset;
    }

    char *buffer()
    {
        return m_buffer;
    }

    std::uint64_t actingVersion() const
    {
        return m_actingVersion;
    }

    static SBE_CONSTEXPR std::uint16_t symbolId()
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t symbolSinceVersion()
    {
        return 0;
    }

    bool symbolInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= symbolSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t symbolEncodingOffset()
    {
        return 0;
    }


    static const char *symbolMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

 private:
    Symbol m_symbol;

 public:

    Symbol &symbol()
    {
        m_symbol.wrap(m_buffer, m_offset + 0, m_actingVersion, m_bufferLength);
        return m_symbol;
    }

    static SBE_CONSTEXPR std::uint16_t seq_numId()
    {
        return 2;
    }

    static SBE_CONSTEXPR std::uint64_t seq_numSinceVersion()
    {
        return 0;
    }

    bool seq_numInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= seq_numSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t seq_numEncodingOffset()
    {
        return 11;
    }


    static const char *seq_numMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

    static SBE_CONSTEXPR std::uint64_t seq_numNullValue()
    {
        return SBE_NULLVALUE_UINT64;
    }

    static SBE_CONSTEXPR std::uint64_t seq_numMinValue()
    {
        return 0x0L;
    }

    static SBE_CONSTEXPR std::uint64_t seq_numMaxValue()
    {
        return 0xfffffffffffffffeL;
    }

    static SBE_CONSTEXPR std::size_t seq_numEncodingLength()
    {
        return 8;
    }

    std::uint64_t seq_num() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_64(*((std::uint64_t *) (m_buffer + m_offset + 11)));
    }

    Equity_trade &seq_num(const std::uint64_t value)
    {
        *((std::uint64_t *) (m_buffer + m_offset + 11)) = SBE_LITTLE_ENDIAN_ENCODE_64(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t reporting_exgId()
    {
        return 3;
    }

    static SBE_CONSTEXPR std::uint64_t reporting_exgSinceVersion()
    {
        return 0;
    }

    bool reporting_exgInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= reporting_exgSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t reporting_exgEncodingOffset()
    {
        return 19;
    }


    static const char *reporting_exgMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

    MIC::Value reporting_exg() const
    {
        return MIC::get((*((std::uint8_t *) (m_buffer + m_offset + 19))));
    }

    Equity_trade &reporting_exg(const MIC::Value value)
    {
        *((std::uint8_t *) (m_buffer + m_offset + 19)) = (value);
        return *this;
    }
    static SBE_CONSTEXPR std::size_t reporting_exgEncodingLength()
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint16_t tsId()
    {
        return 4;
    }

    static SBE_CONSTEXPR std::uint64_t tsSinceVersion()
    {
        return 0;
    }

    bool tsInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= tsSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t tsEncodingOffset()
    {
        return 20;
    }


    static const char *tsMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

 private:
    Timestamp m_ts;

 public:

    Timestamp &ts()
    {
        m_ts.wrap(m_buffer, m_offset + 20, m_actingVersion, m_bufferLength);
        return m_ts;
    }

    static SBE_CONSTEXPR std::uint16_t priceId()
    {
        return 5;
    }

    static SBE_CONSTEXPR std::uint64_t priceSinceVersion()
    {
        return 0;
    }

    bool priceInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= priceSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t priceEncodingOffset()
    {
        return 34;
    }


    static const char *priceMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

 private:
    Price m_price;

 public:

    Price &price()
    {
        m_price.wrap(m_buffer, m_offset + 34, m_actingVersion, m_bufferLength);
        return m_price;
    }

    static SBE_CONSTEXPR std::uint16_t sizeId()
    {
        return 6;
    }

    static SBE_CONSTEXPR std::uint64_t sizeSinceVersion()
    {
        return 0;
    }

    bool sizeInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= sizeSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t sizeEncodingOffset()
    {
        return 41;
    }


    static const char *sizeMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

    static SBE_CONSTEXPR std::uint32_t sizeNullValue()
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t sizeMinValue()
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t sizeMaxValue()
    {
        return 4294967293;
    }

    static SBE_CONSTEXPR std::size_t sizeEncodingLength()
    {
        return 4;
    }

    std::uint32_t size() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *) (m_buffer + m_offset + 41)));
    }

    Equity_trade &size(const std::uint32_t value)
    {
        *((std::uint32_t *) (m_buffer + m_offset + 41)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t volId()
    {
        return 7;
    }

    static SBE_CONSTEXPR std::uint64_t volSinceVersion()
    {
        return 0;
    }

    bool volInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= volSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t volEncodingOffset()
    {
        return 45;
    }


    static const char *volMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

    static SBE_CONSTEXPR std::uint32_t volNullValue()
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t volMinValue()
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t volMaxValue()
    {
        return 4294967293;
    }

    static SBE_CONSTEXPR std::size_t volEncodingLength()
    {
        return 4;
    }

    std::uint32_t vol() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *) (m_buffer + m_offset + 45)));
    }

    Equity_trade &vol(const std::uint32_t value)
    {
        *((std::uint32_t *) (m_buffer + m_offset + 45)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t t_volId()
    {
        return 8;
    }

    static SBE_CONSTEXPR std::uint64_t t_volSinceVersion()
    {
        return 0;
    }

    bool t_volInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= t_volSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t t_volEncodingOffset()
    {
        return 49;
    }


    static const char *t_volMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

    static SBE_CONSTEXPR std::uint32_t t_volNullValue()
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t t_volMinValue()
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t t_volMaxValue()
    {
        return 4294967293;
    }

    static SBE_CONSTEXPR std::size_t t_volEncodingLength()
    {
        return 4;
    }

    std::uint32_t t_vol() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *) (m_buffer + m_offset + 49)));
    }

    Equity_trade &t_vol(const std::uint32_t value)
    {
        *((std::uint32_t *) (m_buffer + m_offset + 49)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t conditionId()
    {
        return 9;
    }

    static SBE_CONSTEXPR std::uint64_t conditionSinceVersion()
    {
        return 0;
    }

    bool conditionInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= conditionSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t conditionEncodingOffset()
    {
        return 53;
    }


    static const char *conditionMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

    TradeCondition::Value condition() const
    {
        return TradeCondition::get((*((std::uint8_t *) (m_buffer + m_offset + 53))));
    }

    Equity_trade &condition(const TradeCondition::Value value)
    {
        *((std::uint8_t *) (m_buffer + m_offset + 53)) = (value);
        return *this;
    }
    static SBE_CONSTEXPR std::size_t conditionEncodingLength()
    {
        return 1;
    }
};
}
}
}
#endif
