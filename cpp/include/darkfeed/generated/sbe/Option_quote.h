/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _DARKFEED_SCHEMAS_SBE_OPTION_QUOTE_H_
#define _DARKFEED_SCHEMAS_SBE_OPTION_QUOTE_H_

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

class Option_quote {
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

    Option_quote() : m_buffer(nullptr), m_bufferLength(0), m_offset(0)
    {}

    Option_quote(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    Option_quote(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength()
    {
        return (std::uint16_t) 79;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId()
    {
        return (std::uint16_t) 2;
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

    Option_quote &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    Option_quote &wrapForDecode(
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

    Option_quote &seq_num(const std::uint64_t value)
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

    Option_quote &reporting_exg(const MIC::Value value)
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

    static SBE_CONSTEXPR std::uint16_t option_typeId()
    {
        return 5;
    }

    static SBE_CONSTEXPR std::uint64_t option_typeSinceVersion()
    {
        return 0;
    }

    bool option_typeInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= option_typeSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t option_typeEncodingOffset()
    {
        return 34;
    }


    static const char *option_typeMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

    OptionType::Value option_type() const
    {
        return OptionType::get((*((std::uint8_t *) (m_buffer + m_offset + 34))));
    }

    Option_quote &option_type(const OptionType::Value value)
    {
        *((std::uint8_t *) (m_buffer + m_offset + 34)) = (value);
        return *this;
    }
    static SBE_CONSTEXPR std::size_t option_typeEncodingLength()
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint16_t expirationId()
    {
        return 6;
    }

    static SBE_CONSTEXPR std::uint64_t expirationSinceVersion()
    {
        return 0;
    }

    bool expirationInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= expirationSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t expirationEncodingOffset()
    {
        return 35;
    }


    static const char *expirationMetaAttribute(const MetaAttribute::Attribute metaAttribute)
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
    Timestamp m_expiration;

 public:

    Timestamp &expiration()
    {
        m_expiration.wrap(m_buffer, m_offset + 35, m_actingVersion, m_bufferLength);
        return m_expiration;
    }

    static SBE_CONSTEXPR std::uint16_t strikeId()
    {
        return 7;
    }

    static SBE_CONSTEXPR std::uint64_t strikeSinceVersion()
    {
        return 0;
    }

    bool strikeInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= strikeSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t strikeEncodingOffset()
    {
        return 49;
    }


    static const char *strikeMetaAttribute(const MetaAttribute::Attribute metaAttribute)
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
    Price m_strike;

 public:

    Price &strike()
    {
        m_strike.wrap(m_buffer, m_offset + 49, m_actingVersion, m_bufferLength);
        return m_strike;
    }

    static SBE_CONSTEXPR std::uint16_t bidId()
    {
        return 8;
    }

    static SBE_CONSTEXPR std::uint64_t bidSinceVersion()
    {
        return 0;
    }

    bool bidInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= bidSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t bidEncodingOffset()
    {
        return 56;
    }


    static const char *bidMetaAttribute(const MetaAttribute::Attribute metaAttribute)
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
    Price m_bid;

 public:

    Price &bid()
    {
        m_bid.wrap(m_buffer, m_offset + 56, m_actingVersion, m_bufferLength);
        return m_bid;
    }

    static SBE_CONSTEXPR std::uint16_t askId()
    {
        return 9;
    }

    static SBE_CONSTEXPR std::uint64_t askSinceVersion()
    {
        return 0;
    }

    bool askInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= askSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t askEncodingOffset()
    {
        return 63;
    }


    static const char *askMetaAttribute(const MetaAttribute::Attribute metaAttribute)
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
    Price m_ask;

 public:

    Price &ask()
    {
        m_ask.wrap(m_buffer, m_offset + 63, m_actingVersion, m_bufferLength);
        return m_ask;
    }

    static SBE_CONSTEXPR std::uint16_t bid_sizeId()
    {
        return 10;
    }

    static SBE_CONSTEXPR std::uint64_t bid_sizeSinceVersion()
    {
        return 0;
    }

    bool bid_sizeInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= bid_sizeSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t bid_sizeEncodingOffset()
    {
        return 70;
    }


    static const char *bid_sizeMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

    static SBE_CONSTEXPR std::uint32_t bid_sizeNullValue()
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t bid_sizeMinValue()
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t bid_sizeMaxValue()
    {
        return 4294967293;
    }

    static SBE_CONSTEXPR std::size_t bid_sizeEncodingLength()
    {
        return 4;
    }

    std::uint32_t bid_size() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *) (m_buffer + m_offset + 70)));
    }

    Option_quote &bid_size(const std::uint32_t value)
    {
        *((std::uint32_t *) (m_buffer + m_offset + 70)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t ask_sizeId()
    {
        return 11;
    }

    static SBE_CONSTEXPR std::uint64_t ask_sizeSinceVersion()
    {
        return 0;
    }

    bool ask_sizeInActingVersion()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
        return m_actingVersion >= ask_sizeSinceVersion();
#pragma clang diagnostic pop
    }

    static SBE_CONSTEXPR std::size_t ask_sizeEncodingOffset()
    {
        return 74;
    }


    static const char *ask_sizeMetaAttribute(const MetaAttribute::Attribute metaAttribute)
    {
        switch (metaAttribute)
        {
        case MetaAttribute::EPOCH: return "unix";
        case MetaAttribute::TIME_UNIT: return "nanosecond";
        case MetaAttribute::SEMANTIC_TYPE: return "";
        }

        return "";
    }

    static SBE_CONSTEXPR std::uint32_t ask_sizeNullValue()
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t ask_sizeMinValue()
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t ask_sizeMaxValue()
    {
        return 4294967293;
    }

    static SBE_CONSTEXPR std::size_t ask_sizeEncodingLength()
    {
        return 4;
    }

    std::uint32_t ask_size() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *) (m_buffer + m_offset + 74)));
    }

    Option_quote &ask_size(const std::uint32_t value)
    {
        *((std::uint32_t *) (m_buffer + m_offset + 74)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t conditionId()
    {
        return 12;
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
        return 78;
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

    QuoteCondition::Value condition() const
    {
        return QuoteCondition::get((*((std::uint8_t *) (m_buffer + m_offset + 78))));
    }

    Option_quote &condition(const QuoteCondition::Value value)
    {
        *((std::uint8_t *) (m_buffer + m_offset + 78)) = (value);
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
