/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _DARKFEED_SCHEMAS_SBE_EQUITY_NBBO_H_
#define _DARKFEED_SCHEMAS_SBE_EQUITY_NBBO_H_

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

class Equity_nbbo {
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

    Equity_nbbo() : m_buffer(nullptr), m_bufferLength(0), m_offset(0)
    {}

    Equity_nbbo(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    Equity_nbbo(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength()
    {
        return (std::uint16_t) 59;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId()
    {
        return (std::uint16_t) 5;
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

    Equity_nbbo &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    Equity_nbbo &wrapForDecode(
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

    Equity_nbbo &seq_num(const std::uint64_t value)
    {
        *((std::uint64_t *) (m_buffer + m_offset + 11)) = SBE_LITTLE_ENDIAN_ENCODE_64(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t tsId()
    {
        return 3;
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
        return 19;
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
        m_ts.wrap(m_buffer, m_offset + 19, m_actingVersion, m_bufferLength);
        return m_ts;
    }

    static SBE_CONSTEXPR std::uint16_t best_bid_exgId()
    {
        return 4;
    }

    static SBE_CONSTEXPR std::uint64_t best_bid_exgSinceVersion()
    {
        return 0;
    }

    bool best_bid_exgInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= best_bid_exgSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t best_bid_exgEncodingOffset()
    {
        return 33;
    }


    static const char *best_bid_exgMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

    MIC::Value best_bid_exg() const
    {
        return MIC::get((*((std::uint8_t *) (m_buffer + m_offset + 33))));
    }

    Equity_nbbo &best_bid_exg(const MIC::Value value)
    {
        *((std::uint8_t *) (m_buffer + m_offset + 33)) = (value);
        return *this;
    }
    static SBE_CONSTEXPR std::size_t best_bid_exgEncodingLength()
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint16_t best_ask_exgId()
    {
        return 5;
    }

    static SBE_CONSTEXPR std::uint64_t best_ask_exgSinceVersion()
    {
        return 0;
    }

    bool best_ask_exgInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= best_ask_exgSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t best_ask_exgEncodingOffset()
    {
        return 34;
    }


    static const char *best_ask_exgMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

    MIC::Value best_ask_exg() const
    {
        return MIC::get((*((std::uint8_t *) (m_buffer + m_offset + 34))));
    }

    Equity_nbbo &best_ask_exg(const MIC::Value value)
    {
        *((std::uint8_t *) (m_buffer + m_offset + 34)) = (value);
        return *this;
    }
    static SBE_CONSTEXPR std::size_t best_ask_exgEncodingLength()
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint16_t best_bidId()
    {
        return 6;
    }

    static SBE_CONSTEXPR std::uint64_t best_bidSinceVersion()
    {
        return 0;
    }

    bool best_bidInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= best_bidSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t best_bidEncodingOffset()
    {
        return 35;
    }


    static const char *best_bidMetaAttribute(const MetaAttribute::Attribute metaAttribute)
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
    Price m_best_bid;

 public:

    Price &best_bid()
    {
        m_best_bid.wrap(m_buffer, m_offset + 35, m_actingVersion, m_bufferLength);
        return m_best_bid;
    }

    static SBE_CONSTEXPR std::uint16_t best_askId()
    {
        return 7;
    }

    static SBE_CONSTEXPR std::uint64_t best_askSinceVersion()
    {
        return 0;
    }

    bool best_askInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= best_askSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t best_askEncodingOffset()
    {
        return 42;
    }


    static const char *best_askMetaAttribute(const MetaAttribute::Attribute metaAttribute)
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
    Price m_best_ask;

 public:

    Price &best_ask()
    {
        m_best_ask.wrap(m_buffer, m_offset + 42, m_actingVersion, m_bufferLength);
        return m_best_ask;
    }

    static SBE_CONSTEXPR std::uint16_t best_bid_sizeId()
    {
        return 8;
    }

    static SBE_CONSTEXPR std::uint64_t best_bid_sizeSinceVersion()
    {
        return 0;
    }

    bool best_bid_sizeInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= best_bid_sizeSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t best_bid_sizeEncodingOffset()
    {
        return 49;
    }


    static const char *best_bid_sizeMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

    static SBE_CONSTEXPR std::uint32_t best_bid_sizeNullValue()
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t best_bid_sizeMinValue()
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t best_bid_sizeMaxValue()
    {
        return 4294967293;
    }

    static SBE_CONSTEXPR std::size_t best_bid_sizeEncodingLength()
    {
        return 4;
    }

    std::uint32_t best_bid_size() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *) (m_buffer + m_offset + 49)));
    }

    Equity_nbbo &best_bid_size(const std::uint32_t value)
    {
        *((std::uint32_t *) (m_buffer + m_offset + 49)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t best_ask_sizeId()
    {
        return 9;
    }

    static SBE_CONSTEXPR std::uint64_t best_ask_sizeSinceVersion()
    {
        return 0;
    }

    bool best_ask_sizeInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= best_ask_sizeSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t best_ask_sizeEncodingOffset()
    {
        return 53;
    }


    static const char *best_ask_sizeMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

    static SBE_CONSTEXPR std::uint32_t best_ask_sizeNullValue()
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t best_ask_sizeMinValue()
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t best_ask_sizeMaxValue()
    {
        return 4294967293;
    }

    static SBE_CONSTEXPR std::size_t best_ask_sizeEncodingLength()
    {
        return 4;
    }

    std::uint32_t best_ask_size() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *) (m_buffer + m_offset + 53)));
    }

    Equity_nbbo &best_ask_size(const std::uint32_t value)
    {
        *((std::uint32_t *) (m_buffer + m_offset + 53)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t best_bid_conditionId()
    {
        return 10;
    }

    static SBE_CONSTEXPR std::uint64_t best_bid_conditionSinceVersion()
    {
        return 0;
    }

    bool best_bid_conditionInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= best_bid_conditionSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t best_bid_conditionEncodingOffset()
    {
        return 57;
    }


    static const char *best_bid_conditionMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

    QuoteCondition::Value best_bid_condition() const
    {
        return QuoteCondition::get((*((std::uint8_t *) (m_buffer + m_offset + 57))));
    }

    Equity_nbbo &best_bid_condition(const QuoteCondition::Value value)
    {
        *((std::uint8_t *) (m_buffer + m_offset + 57)) = (value);
        return *this;
    }
    static SBE_CONSTEXPR std::size_t best_bid_conditionEncodingLength()
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint16_t best_ask_conditionId()
    {
        return 11;
    }

    static SBE_CONSTEXPR std::uint64_t best_ask_conditionSinceVersion()
    {
        return 0;
    }

    bool best_ask_conditionInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= best_ask_conditionSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t best_ask_conditionEncodingOffset()
    {
        return 58;
    }


    static const char *best_ask_conditionMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

    QuoteCondition::Value best_ask_condition() const
    {
        return QuoteCondition::get((*((std::uint8_t *) (m_buffer + m_offset + 58))));
    }

    Equity_nbbo &best_ask_condition(const QuoteCondition::Value value)
    {
        *((std::uint8_t *) (m_buffer + m_offset + 58)) = (value);
        return *this;
    }
    static SBE_CONSTEXPR std::size_t best_ask_conditionEncodingLength()
    {
        return 1;
    }
};
}
}
}
#endif
