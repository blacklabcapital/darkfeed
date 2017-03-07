#include <darkfeed/types/halts.hpp>
#include "darkfeed/serialization/sbe_serializer.hpp"
#include "darkfeed/util/hashing.hpp"
#include "darkfeed/types/quotes.hpp"
#include "darkfeed/types/trades.hpp"
#include "darkfeed/generated/sbe/MessageHeader.h"
#include "darkfeed/generated/sbe/Equity_quote.h"
#include "darkfeed/generated/sbe/Option_quote.h"
#include "darkfeed/generated/sbe/Halt.h"
#include "darkfeed/generated/sbe/Equity_trade.h"
#include "darkfeed/generated/sbe/Equity_nbbo.h"

namespace darkfeed
{
template<> std::size_t SBESerializer::serialize(char *buf, std::size_t buf_size, const Quote &x)
{
    schemas::sbe::MessageHeader h;
    schemas::sbe::Equity_quote q;
    h.wrap(buf, 0, 0, buf_size).checksum(0).msgLength(0).blockLength(q.sbeBlockLength()).templateId(q.sbeTemplateId()).schemaId(q.sbeSchemaId()).version(q.sbeSchemaVersion());
    std::size_t h_len = h.encodedLength();
    q.wrapForEncode(buf, h_len, buf_size);
    q.symbol()
        .putRoot(x.symbol.root)
        .series(x.symbol.series)
        .listing_exg((schemas::sbe::MIC::Value) x.symbol.listing_exg.mic)
        .issue_type((schemas::sbe::IssueType::Value) x.symbol.issue_type);
    q.seq_num(x.seq_num);
    q.reporting_exg((schemas::sbe::MIC::Value) x.reporting_exg.mic);
    q.ts()
        .unix((uint64_t) x.ts.ts)
        .ns(x.ts.ns)
        .utc_offset(x.ts.offset)
        .dst(x.ts.dst ? schemas::sbe::Bool::TRUE : schemas::sbe::Bool::FALSE);
    q.bid()
        .price(x.bid.price)
        .precision(x.bid.precision)
        .tick_size(x.bid.tick_size)
        .currency((schemas::sbe::Currency::Value) x.bid.currency);
    q.ask()
        .price(x.ask.price)
        .precision(x.ask.precision)
        .tick_size(x.ask.tick_size)
        .currency((schemas::sbe::Currency::Value) x.ask.currency);
    q.bid_size(x.bid_size);
    q.ask_size(x.ask_size);
    q.condition((schemas::sbe::QuoteCondition::Value) x.condition);
    std::size_t msg_len = q.encodedLength();
    h.checksum((std::uint16_t) CRC32C_FINISH(crc32c(CRC32C_INIT,
                                                    buf + h_len, msg_len))); //get lowest 16 bits for checksum
    h.msgLength((std::uint16_t) msg_len);
    return msg_len + h_len;
}

template<> std::pair<Quote, bool> SBESerializer::deserialize(const char *buf, std::size_t len)
{
    //decode header
    schemas::sbe::MessageHeader hdr;
    hdr.wrap(const_cast<char *>(buf), 0, 0, len);
    std::uint16_t block_len = hdr.blockLength();
    std::uint16_t checksum = hdr.checksum();
    std::uint16_t msg_len = hdr.msgLength();
    std::uint16_t schema_id = hdr.schemaId();
    std::uint16_t schema_ver = hdr.version();

    //our header checks must match what we think we're receiving
    if ((hdr.templateId() != schemas::sbe::Equity_quote::sbeTemplateId())
        || (block_len != schemas::sbe::Equity_quote::sbeBlockLength())
        || (schema_id != schemas::sbe::Equity_quote::sbeSchemaId())
        || (schema_ver != schemas::sbe::Equity_quote::sbeSchemaVersion()))
        return std::make_pair(Quote(), false);
    std::size_t hdrlen = hdr.encodedLength();
    //verify our checksum
    std::uint16_t msg_checksum = (std::uint16_t) CRC32C_FINISH(crc32c(CRC32C_INIT, buf + hdrlen, msg_len));
    if (msg_checksum != checksum)
        return std::make_pair(Quote(), false); //checksum verification failed
    //decode EquityQuote
    Quote q;
    schemas::sbe::Equity_quote eq;
    eq.wrapForDecode(const_cast<char *>(buf), hdrlen, block_len, schema_ver, len);
    const char *sym_root_ptr = eq.symbol().root();
    std::copy(sym_root_ptr, sym_root_ptr + DARKFEED_ROOT_SYMBOL_SIZE, q.symbol.root);
    q.symbol.listing_exg = MIC((std::uint8_t) eq.symbol().listing_exg());
    q.symbol.series = eq.symbol().series();
    q.symbol.issue_type = IssueType((std::uint8_t) eq.symbol().issue_type());
    q.reporting_exg = MIC((std::uint8_t) eq.reporting_exg());
    q.seq_num = eq.seq_num();
    q.ts.ts = (std::time_t) eq.ts().unix();
    q.ts.ns = eq.ts().ns();
    q.ts.offset = eq.ts().utc_offset();
    q.ts.dst = eq.ts().dst();
    q.bid = Price((std::uint32_t) eq.bid().price(), Currency((std::uint8_t) eq.bid().currency()), eq.bid().precision(), eq.bid().tick_size());
    q.ask = Price((std::uint32_t) eq.ask().price(), Currency((std::uint8_t) eq.ask().currency()), eq.ask().precision(), eq.ask().tick_size());
    q.bid_size = eq.bid_size();
    q.ask_size = eq.ask_size();
    q.condition = QuoteCondition((std::uint8_t) eq.condition());
    return std::make_pair(q, true);
}

template<> std::size_t SBESerializer::serialize(char *buf, std::size_t buf_size, const OptionQuote &x)
{
    schemas::sbe::MessageHeader h;
    schemas::sbe::Option_quote q;
    h.wrap(buf, 0, 0, buf_size).checksum(0).msgLength(0).blockLength(q.sbeBlockLength()).templateId(q.sbeTemplateId()).schemaId(q.sbeSchemaId()).version(q.sbeSchemaVersion());
    std::size_t h_len = h.encodedLength();
    q.wrapForEncode(buf, h_len, buf_size);
    q.symbol()
        .putRoot(x.symbol.root)
        .series(x.symbol.series)
        .listing_exg((schemas::sbe::MIC::Value) x.symbol.listing_exg.mic)
        .issue_type((schemas::sbe::IssueType::Value) x.symbol.issue_type);
    q.seq_num(x.seq_num);
    q.reporting_exg((schemas::sbe::MIC::Value) x.reporting_exg.mic);
    q.ts()
        .unix((std::uint64_t) x.ts.ts)
        .ns(x.ts.ns)
        .utc_offset(x.ts.offset)
        .dst(x.ts.dst ? schemas::sbe::Bool::TRUE : schemas::sbe::Bool::FALSE);
    q.option_type((schemas::sbe::OptionType::Value) x.option_type);
    q.expiration()
        .unix((std::uint64_t) x.expiration.ts)
        .ns(x.expiration.ns)
        .utc_offset(x.expiration.offset)
        .dst(x.expiration.dst ? schemas::sbe::Bool::TRUE : schemas::sbe::Bool::FALSE);
    q.strike()
        .price(x.strike.price)
        .precision(x.strike.precision)
        .tick_size(x.strike.tick_size)
        .currency((schemas::sbe::Currency::Value) x.strike.currency);
    q.bid()
        .price(x.bid.price)
        .precision(x.bid.precision)
        .tick_size(x.bid.tick_size)
        .currency((schemas::sbe::Currency::Value) x.bid.currency);
    q.ask()
        .price(x.ask.price)
        .precision(x.ask.precision)
        .tick_size(x.ask.tick_size)
        .currency((schemas::sbe::Currency::Value) x.ask.currency);
    q.bid_size(x.bid_size);
    q.ask_size(x.ask_size);
    q.condition((schemas::sbe::QuoteCondition::Value) x.condition);
    std::size_t msg_len = q.encodedLength();
    h.checksum((std::uint16_t) CRC32C_FINISH(crc32c(CRC32C_INIT,
                                                    buf + h_len, msg_len))); //get lowest 16 bits for checksum
    h.msgLength((std::uint16_t) msg_len);
    return msg_len + h_len;
}

template<> std::pair<OptionQuote, bool> SBESerializer::deserialize(const char *buf, std::size_t len)
{
    //decode header
    schemas::sbe::MessageHeader hdr;
    hdr.wrap(const_cast<char *>(buf), 0, 0, len);
    std::uint16_t block_len = hdr.blockLength();
    std::uint16_t checksum = hdr.checksum();
    std::uint16_t msg_len = hdr.msgLength();
    std::uint16_t schema_id = hdr.schemaId();
    std::uint16_t schema_ver = hdr.version();
    //our header checks must match what we think we're receiving
    if ((hdr.templateId() != schemas::sbe::Option_quote::sbeTemplateId())
        || (block_len != schemas::sbe::Option_quote::sbeBlockLength())
        || (schema_id != schemas::sbe::Option_quote::sbeSchemaId())
        || (schema_ver != schemas::sbe::Option_quote::sbeSchemaVersion()))
        return std::make_pair(OptionQuote(), false);
    std::size_t hdrlen = hdr.encodedLength();
    //verify our checksum
    std::uint16_t msg_checksum = (std::uint16_t) CRC32C_FINISH(crc32c(CRC32C_INIT, buf + hdrlen, msg_len));
    if (msg_checksum != checksum)
        return std::make_pair(OptionQuote(), false); //checksum verification failed

    //decode OptionQuote
    OptionQuote q;
    schemas::sbe::Option_quote oq;
    oq.wrapForDecode(const_cast<char *>(buf), hdrlen, block_len, schema_ver, len);
    const char *sym_root_ptr = oq.symbol().root();
    std::copy(sym_root_ptr, sym_root_ptr + DARKFEED_ROOT_SYMBOL_SIZE, q.symbol.root);
    q.symbol.listing_exg = MIC((std::uint8_t) oq.symbol().listing_exg());
    q.symbol.series = oq.symbol().series();
    q.symbol.issue_type = IssueType((std::uint8_t) oq.symbol().issue_type());
    q.seq_num = oq.seq_num();
    q.reporting_exg = MIC((std::uint8_t) oq.reporting_exg());
    q.ts.ts = (std::time_t) oq.ts().unix();
    q.ts.ns = oq.ts().ns();
    q.ts.offset = oq.ts().utc_offset();
    q.ts.dst = oq.ts().dst();
    q.option_type = OptionType((std::uint8_t) oq.option_type());
    q.expiration.ts = (std::time_t) oq.expiration().unix();
    q.expiration.ns = oq.expiration().ns();
    q.expiration.offset = oq.expiration().utc_offset();
    q.expiration.dst = oq.ts().dst();
    q.strike = Price(oq.strike().price(), Currency((std::uint8_t) oq.strike().currency()), oq.strike().precision(), oq.strike().tick_size());
    q.bid = Price(oq.bid().price(), Currency((std::uint8_t) oq.bid().currency()), oq.bid().precision(), oq.bid().tick_size());
    q.ask = Price(oq.ask().price(), Currency((std::uint8_t) oq.ask().currency()), oq.ask().precision(), oq.ask().tick_size());
    q.bid_size = oq.bid_size();
    q.ask_size = oq.ask_size();
    q.condition = QuoteCondition((std::uint8_t) oq.condition());
    return std::make_pair(q, true);
}

template<> std::size_t SBESerializer::serialize(char *buf, std::size_t buf_size, const Halt &x)
{

    schemas::sbe::MessageHeader hdr;
    schemas::sbe::Halt h;
    hdr.wrap(buf, 0, 0, buf_size).checksum(0).msgLength(0).blockLength(h.sbeBlockLength()).templateId(h.sbeTemplateId()).schemaId(h.sbeSchemaId()).version(h.sbeSchemaVersion());
    std::size_t h_len = hdr.encodedLength();

    h.wrapForEncode(buf, h_len, buf_size);
    h.symbol()
        .putRoot(x.symbol.root)
        .series(x.symbol.series)
        .listing_exg((schemas::sbe::MIC::Value) x.symbol.listing_exg.mic)
        .issue_type((schemas::sbe::IssueType::Value) x.symbol.issue_type);
    h.seq_num(x.seq_num);
    h.reporting_exg((schemas::sbe::MIC::Value) x.reporting_exg.mic);
    h.ts()
        .unix((std::uint64_t) x.ts.ts)
        .ns(x.ts.ns)
        .utc_offset(x.ts.offset)
        .dst(x.ts.dst ? schemas::sbe::Bool::TRUE : schemas::sbe::Bool::FALSE);
    h.halt_type((schemas::sbe::HaltType::Value) x.halt_type);
    h.halt_status((schemas::sbe::HaltStatus::Value) x.halt_status);
    std::size_t msg_len = h.encodedLength();
    hdr.checksum((std::uint16_t) CRC32C_FINISH(crc32c(CRC32C_INIT,
                                                      buf + h_len, msg_len))); //get lowest 16 bits for checksum
    hdr.msgLength((std::uint16_t) msg_len);
    return msg_len + h_len;
}

template<> std::pair<Halt, bool> SBESerializer::deserialize(const char *buf, std::size_t len)
{
    //decode header
    schemas::sbe::MessageHeader hdr;
    hdr.wrap(const_cast<char *>(buf), 0, 0, len);
    std::uint16_t block_len = hdr.blockLength();
    std::uint16_t checksum = hdr.checksum();
    std::uint16_t msg_len = hdr.msgLength();
    std::uint16_t schema_id = hdr.schemaId();
    std::uint16_t schema_ver = hdr.version();
    //our header checks must match what we think we're receiving
    if ((hdr.templateId() != schemas::sbe::Halt::sbeTemplateId())
        || (block_len != schemas::sbe::Halt::sbeBlockLength())
        || (schema_id != schemas::sbe::Halt::sbeSchemaId())
        || (schema_ver != schemas::sbe::Halt::sbeSchemaVersion()))
        return std::make_pair(Halt(), false);
    std::size_t hdrlen = hdr.encodedLength();
    //verify our checksum
    std::uint16_t msg_checksum = (std::uint16_t) CRC32C_FINISH(crc32c(CRC32C_INIT, buf + hdrlen, msg_len));
    if (msg_checksum != checksum)
        return std::make_pair(Halt(), false); //checksum verification failed

    //decode Halt
    Halt h;
    schemas::sbe::Halt oh;
    oh.wrapForDecode(const_cast<char *>(buf), hdrlen, block_len, schema_ver, len);
    const char *sym_root_ptr = oh.symbol().root();
    std::copy(sym_root_ptr, sym_root_ptr + DARKFEED_ROOT_SYMBOL_SIZE, h.symbol.root);
    h.symbol.listing_exg = MIC((std::uint8_t) oh.symbol().listing_exg());
    h.symbol.series = oh.symbol().series();
    h.symbol.issue_type = IssueType((std::uint8_t) oh.symbol().issue_type());
    h.seq_num = oh.seq_num();
    h.reporting_exg = MIC((std::uint8_t) oh.reporting_exg());
    h.ts.ts = (std::time_t) oh.ts().unix();
    h.ts.ns = oh.ts().ns();
    h.ts.offset = oh.ts().utc_offset();
    h.ts.dst = oh.ts().dst();
    h.halt_type = HaltType((std::uint8_t) oh.halt_type());
    h.halt_status = HaltStatus((std::uint8_t) oh.halt_status());
    return std::make_pair(h, true);
}

template<> std::size_t SBESerializer::serialize(char *buf, std::size_t buf_size, const Trade &x)
{
    schemas::sbe::MessageHeader h;
    schemas::sbe::Equity_trade t;
    h.wrap(buf, 0, 0, buf_size).checksum(0).msgLength(0).blockLength(t.sbeBlockLength()).templateId(t.sbeTemplateId()).schemaId(t.sbeSchemaId()).version(t.sbeSchemaVersion());
    std::size_t h_len = h.encodedLength();
    t.wrapForEncode(buf, h_len, buf_size);
    t.symbol()
        .putRoot(x.symbol.root)
        .series(x.symbol.series)
        .listing_exg((schemas::sbe::MIC::Value) x.symbol.listing_exg.mic)
        .issue_type((schemas::sbe::IssueType::Value) x.symbol.issue_type);
    t.seq_num(x.seq_num);
    t.reporting_exg((schemas::sbe::MIC::Value) x.reporting_exg.mic);
    t.ts()
        .unix((std::uint64_t) x.ts.ts)
        .ns(x.ts.ns)
        .utc_offset(x.ts.offset)
        .dst(x.ts.dst ? schemas::sbe::Bool::TRUE : schemas::sbe::Bool::FALSE);
    t.price()
        .price(x.price.price)
        .precision(x.price.precision)
        .tick_size(x.price.tick_size)
        .currency((schemas::sbe::Currency::Value) x.price.currency);
    t.size(x.size);
    t.vol(x.vol);
    t.t_vol(x.t_vol);
    t.condition((schemas::sbe::TradeCondition::Value) x.condition);
    std::size_t msg_len = t.encodedLength();
    h.checksum((std::uint16_t) CRC32C_FINISH(crc32c(CRC32C_INIT,
                                                    buf + h_len, msg_len))); //get lowest 16 bits for checksum
    h.msgLength((std::uint16_t) msg_len);
    return msg_len + h_len;
}

template<> std::pair<Trade, bool> SBESerializer::deserialize(const char *buf, std::size_t len)
{
    //decode header
    schemas::sbe::MessageHeader hdr;
    hdr.wrap(const_cast<char *>(buf), 0, 0, len);
    std::uint16_t block_len = hdr.blockLength();
    std::uint16_t checksum = hdr.checksum();
    std::uint16_t msg_len = hdr.msgLength();
    std::uint16_t schema_id = hdr.schemaId();
    std::uint16_t schema_ver = hdr.version();
    //our header checks must match what we think we're receiving
    if ((hdr.templateId() != schemas::sbe::Equity_trade::sbeTemplateId())
        || (block_len != schemas::sbe::Equity_trade::sbeBlockLength())
        || (schema_id != schemas::sbe::Equity_trade::sbeSchemaId())
        || (schema_ver != schemas::sbe::Equity_trade::sbeSchemaVersion()))
        return std::make_pair(Trade(), false);
    std::size_t hdrlen = hdr.encodedLength();
    //verify our checksum
    std::uint16_t msg_checksum = (std::uint16_t) CRC32C_FINISH(crc32c(CRC32C_INIT, buf + hdrlen, msg_len));
    if (msg_checksum != checksum)
        return std::make_pair(Trade(), false); //checksum verification failed

    //decode Trade
    Trade t;
    schemas::sbe::Equity_trade ot;
    ot.wrapForDecode(const_cast<char *>(buf), hdrlen, block_len, schema_ver, len);
    const char *sym_root_ptr = ot.symbol().root();
    std::copy(sym_root_ptr, sym_root_ptr + DARKFEED_ROOT_SYMBOL_SIZE, t.symbol.root);
    t.symbol.listing_exg = MIC((std::uint8_t) ot.symbol().listing_exg());
    t.symbol.series = ot.symbol().series();
    t.symbol.issue_type = IssueType((std::uint8_t) ot.symbol().issue_type());
    t.seq_num = ot.seq_num();
    t.reporting_exg = MIC((std::uint8_t) ot.reporting_exg());
    t.ts.ts = (std::time_t) ot.ts().unix();
    t.ts.ns = ot.ts().ns();
    t.ts.offset = ot.ts().utc_offset();
    t.ts.dst = ot.ts().dst();
    t.price = Price(ot.price().price(), Currency((std::uint8_t) ot.price().currency()), ot.price().precision(), ot.price().tick_size());
    t.size = ot.size();
    t.vol = ot.vol();
    t.t_vol = ot.t_vol();
    t.condition = TradeCondition((std::uint8_t) ot.condition());
    return std::make_pair(t, true);
}

template<> std::size_t SBESerializer::serialize(char *buf, std::size_t buf_size, const NBBO &x)
{
    schemas::sbe::MessageHeader h;
    schemas::sbe::Equity_nbbo q;
    h.wrap(buf, 0, 0, buf_size).checksum(0).msgLength(0).blockLength(q.sbeBlockLength()).templateId(q.sbeTemplateId()).schemaId(q.sbeSchemaId()).version(q.sbeSchemaVersion());
    std::size_t h_len = h.encodedLength();
    q.wrapForEncode(buf, h_len, buf_size);
    q.symbol()
        .putRoot(x.symbol.root)
        .series(x.symbol.series)
        .listing_exg((schemas::sbe::MIC::Value) x.symbol.listing_exg.mic)
        .issue_type((schemas::sbe::IssueType::Value) x.symbol.issue_type);
    q.seq_num(x.seq_num);
    q.best_bid_exg((schemas::sbe::MIC::Value) x.best_bid_exg.mic);
    q.best_ask_exg((schemas::sbe::MIC::Value) x.best_ask_exg.mic);
    q.ts()
        .unix((uint64_t) x.ts.ts)
        .ns(x.ts.ns)
        .utc_offset(x.ts.offset)
        .dst(x.ts.dst ? schemas::sbe::Bool::TRUE : schemas::sbe::Bool::FALSE);
    q.best_bid()
        .price(x.best_bid.price)
        .precision(x.best_bid.precision)
        .tick_size(x.best_bid.tick_size)
        .currency((schemas::sbe::Currency::Value) x.best_bid.currency);
    q.best_ask()
        .price(x.best_ask.price)
        .precision(x.best_ask.precision)
        .tick_size(x.best_ask.tick_size)
        .currency((schemas::sbe::Currency::Value) x.best_ask.currency);
    q.best_bid_size(x.best_bid_size);
    q.best_ask_size(x.best_ask_size);
    q.best_bid_condition((schemas::sbe::QuoteCondition::Value) x.best_bid_condition);
    q.best_ask_condition((schemas::sbe::QuoteCondition::Value) x.best_ask_condition);
    std::size_t msg_len = q.encodedLength();
    h.checksum((std::uint16_t) CRC32C_FINISH(crc32c(CRC32C_INIT,
                                                    buf + h_len, msg_len))); //get lowest 16 bits for checksum
    h.msgLength((std::uint16_t) msg_len);
    return msg_len + h_len;
}

template<> std::pair<NBBO, bool> SBESerializer::deserialize(const char *buf, std::size_t len)
{
    //decode header
    schemas::sbe::MessageHeader hdr;
    hdr.wrap(const_cast<char *>(buf), 0, 0, len);
    std::uint16_t block_len = hdr.blockLength();
    std::uint16_t checksum = hdr.checksum();
    std::uint16_t msg_len = hdr.msgLength();
    std::uint16_t schema_id = hdr.schemaId();
    std::uint16_t schema_ver = hdr.version();
    //our header checks must match what we think we're receiving
    if ((hdr.templateId() != schemas::sbe::Equity_nbbo::sbeTemplateId())
        || (block_len != schemas::sbe::Equity_nbbo::sbeBlockLength())
        || (schema_id != schemas::sbe::Equity_nbbo::sbeSchemaId())
        || (schema_ver != schemas::sbe::Equity_nbbo::sbeSchemaVersion()))
        return std::make_pair(NBBO(), false);
    std::size_t hdrlen = hdr.encodedLength();
    //verify our checksum
    std::uint16_t msg_checksum = (std::uint16_t) CRC32C_FINISH(crc32c(CRC32C_INIT, buf + hdrlen, msg_len));
    if (msg_checksum != checksum)
        return std::make_pair(NBBO(), false); //checksum verification failed

    //decode EquityNBBO
    NBBO q;
    schemas::sbe::Equity_nbbo eq;
    eq.wrapForDecode(const_cast<char *>(buf), hdrlen, block_len, schema_ver, len);
    const char *sym_root_ptr = eq.symbol().root();
    std::copy(sym_root_ptr, sym_root_ptr + DARKFEED_ROOT_SYMBOL_SIZE, q.symbol.root);
    q.symbol.listing_exg = MIC((std::uint8_t) eq.symbol().listing_exg());
    q.symbol.series = eq.symbol().series();
    q.symbol.issue_type = IssueType((std::uint8_t) eq.symbol().issue_type());
    q.best_bid_exg = MIC((std::uint8_t) eq.best_bid_exg());
    q.best_ask_exg = MIC((std::uint8_t) eq.best_ask_exg());
    q.seq_num = eq.seq_num();
    q.ts.ts = (std::time_t) eq.ts().unix();
    q.ts.ns = eq.ts().ns();
    q.ts.offset = eq.ts().utc_offset();
    q.ts.dst = eq.ts().dst();
    q.best_bid = Price((std::uint32_t) eq.best_bid().price(), Currency((std::uint8_t) eq.best_bid().currency()), eq.best_bid().precision(), eq.best_bid().tick_size());
    q.best_ask = Price((std::uint32_t) eq.best_ask().price(), Currency((std::uint8_t) eq.best_ask().currency()), eq.best_ask().precision(), eq.best_ask().tick_size());
    q.best_bid_size = eq.best_bid_size();
    q.best_ask_size = eq.best_ask_size();
    q.best_bid_condition = QuoteCondition((std::uint8_t) eq.best_bid_condition());
    q.best_ask_condition = QuoteCondition((std::uint8_t) eq.best_ask_condition());
    return std::make_pair(q, true);
}
} //darkfeed
