#include <darkfeed/util/hashing.hpp>
#include "darkfeed/generated/flatbuffers/trade_generated.h"
#include "darkfeed/generated/flatbuffers/quote_generated.h"
#include "darkfeed/generated/flatbuffers/nbbo_generated.h"
#include "darkfeed/serialization/flatbuffers_serializer.hpp"
#include "darkfeed/types/quotes.hpp"
#include "darkfeed/types/trades.hpp"
#include "darkfeed/types/halts.hpp"

namespace darkfeed
{
template<> std::size_t FBSerializer::serialize(char *buf, std::size_t buf_size, const Quote &x)
{
    flatbuffers::FlatBufferBuilder fbb;
    auto fsymstr = fbb.CreateString(x.symbol.root);
    auto fsymbuilder = schemas::fb::SymbolBuilder(fbb);
    fsymbuilder.add_root(fsymstr);
    fsymbuilder.add_series(x.symbol.series);
    fsymbuilder.add_listing_exg(x.symbol.listing_exg.mic);
    fsymbuilder.add_issue_type(x.symbol.issue_type);
    auto sym_offset = fsymbuilder.Finish();
    schemas::fb::EquityQuoteBuilder eqb(fbb);
    schemas::fb::Timestamp qts((std::uint32_t) x.ts.ts, x.ts.ns, x.ts.offset, x.ts.dst);
    eqb.add_symbol(sym_offset);
    eqb.add_ts(&qts);
    eqb.add_seq_num(x.seq_num);
    auto bp = schemas::fb::Price(x.bid.price, x.bid.precision, x.bid.tick_size, x.bid.currency);
    eqb.add_bid(&bp);
    auto ap = schemas::fb::Price(x.ask.price, x.ask.precision, x.ask.tick_size, x.ask.currency);
    eqb.add_ask(&ap);
    eqb.add_bid_size(x.bid_size);
    eqb.add_ask_size(x.ask_size);
    eqb.add_condition(x.condition);
    eqb.add_reporting_exg(x.reporting_exg.mic);
    auto eqb_offset = eqb.Finish();
    fbb.Finish(eqb_offset);
    std::size_t finalLen = fbb.GetSize();
    auto buf_ptr = fbb.ReleaseBufferPointer();
    char *raw_buf_ptr = (char *) buf_ptr.get();
    if (finalLen > buf_size)
        throw std::runtime_error("Serialized size exceeds provided buffer");
    std::copy(raw_buf_ptr, raw_buf_ptr + finalLen, buf + 8); //copy to message sector
    //populate 64 bit header (length,checksum)
    *(std::uint32_t *) buf = (std::uint32_t) finalLen;
    *(std::uint32_t *) (buf + 4) = CRC32C_FINISH(crc32c(CRC32C_INIT, raw_buf_ptr, finalLen));
    return finalLen + 8;
}

template<> std::size_t FBSerializer::serialize(char *buf, std::size_t buf_size, const OptionQuote &x)
{
    flatbuffers::FlatBufferBuilder fbb;
    auto fsymstr = fbb.CreateString(x.symbol.root);
    auto fsymbuilder = schemas::fb::SymbolBuilder(fbb);
    fsymbuilder.add_root(fsymstr);
    fsymbuilder.add_series(x.symbol.series);
    fsymbuilder.add_listing_exg(x.symbol.listing_exg.mic);
    fsymbuilder.add_issue_type(x.symbol.issue_type);
    auto sym_offset = fsymbuilder.Finish();
    schemas::fb::OptionQuoteBuilder eqb(fbb);
    schemas::fb::Timestamp qts((std::uint32_t) x.ts.ts, x.ts.ns, x.ts.offset, x.ts.dst);
    schemas::fb::Timestamp ets((std::uint32_t) x.expiration.ts, x.expiration.ns, x.expiration.offset, x.expiration.dst);
    eqb.add_symbol(sym_offset);
    eqb.add_option_type(x.option_type);
    eqb.add_ts(&qts);
    eqb.add_expiration(&ets);
    eqb.add_seq_num(x.seq_num);
    auto bp = schemas::fb::Price(x.bid.price, x.bid.precision, x.bid.tick_size, x.bid.currency);
    eqb.add_bid(&bp);
    auto ap = schemas::fb::Price(x.ask.price, x.ask.precision, x.ask.tick_size, x.ask.currency);
    eqb.add_ask(&ap);
    auto sp = schemas::fb::Price(x.strike.price, x.strike.precision, x.strike.tick_size, x.strike.currency);
    eqb.add_strike(&sp);
    eqb.add_bid_size(x.bid_size);
    eqb.add_ask_size(x.ask_size);
    eqb.add_condition(x.condition);
    eqb.add_reporting_exg(x.reporting_exg.mic);
    auto eqb_offset = eqb.Finish();
    fbb.Finish(eqb_offset);
    std::size_t finalLen = fbb.GetSize();
    auto buf_ptr = fbb.ReleaseBufferPointer();
    char *raw_buf_ptr = (char *) buf_ptr.get();
    if (finalLen > buf_size)
        throw std::runtime_error("Serialized size exceeds provided buffer");
    std::copy(raw_buf_ptr, raw_buf_ptr + finalLen, buf + 8); //copy to message sector
    //populate 64 bit header (length,checksum)
    *(std::uint32_t *) buf = (std::uint32_t) finalLen;
    *(std::uint32_t *) (buf + 4) = CRC32C_FINISH(crc32c(CRC32C_INIT, raw_buf_ptr, finalLen));
    return finalLen + 8;
}

template<> std::size_t FBSerializer::serialize(char *buf, std::size_t buf_size, const NBBO &x)
{
    flatbuffers::FlatBufferBuilder fbb;
    auto fsymstr = fbb.CreateString(x.symbol.root);
    auto fsymbuilder = schemas::fb::SymbolBuilder(fbb);
    fsymbuilder.add_root(fsymstr);
    fsymbuilder.add_series(x.symbol.series);
    fsymbuilder.add_listing_exg(x.symbol.listing_exg.mic);
    fsymbuilder.add_issue_type(x.symbol.issue_type);
    auto sym_offset = fsymbuilder.Finish();
    schemas::fb::NBBOBuilder eqb(fbb);
    schemas::fb::Timestamp qts((std::uint32_t) x.ts.ts, x.ts.ns, x.ts.offset, x.ts.dst);
    eqb.add_symbol(sym_offset);
    eqb.add_ts(&qts);
    eqb.add_seq_num(x.seq_num);
    auto bb = schemas::fb::Price(x.best_bid.price, x.best_bid.precision, x.best_bid.tick_size, x.best_bid.currency);
    eqb.add_best_bid(&bb);
    auto ba = schemas::fb::Price(x.best_ask.price, x.best_ask.precision, x.best_ask.tick_size, x.best_ask.currency);
    eqb.add_best_ask(&ba);
    eqb.add_best_bid_size(x.best_bid_size);
    eqb.add_best_ask_size(x.best_ask_size);
    eqb.add_best_bid_condition(x.best_bid_condition);
    eqb.add_best_ask_condition(x.best_ask_condition);
    eqb.add_best_bid_exg(x.best_bid_exg.mic);
    eqb.add_best_ask_exg(x.best_ask_exg.mic);
    auto eqb_offset = eqb.Finish();
    fbb.Finish(eqb_offset);
    std::size_t finalLen = fbb.GetSize();
    auto buf_ptr = fbb.ReleaseBufferPointer();
    char *raw_buf_ptr = (char *) buf_ptr.get();
    if (finalLen > buf_size)
        throw std::runtime_error("Serialized size exceeds provided buffer");
    std::copy(raw_buf_ptr, raw_buf_ptr + finalLen, buf + 8); //copy to message sector
    //populate 64 bit header (length,checksum)
    *(std::uint32_t *) buf = (std::uint32_t) finalLen;
    *(std::uint32_t *) (buf + 4) = CRC32C_FINISH(crc32c(CRC32C_INIT, raw_buf_ptr, finalLen));
    return finalLen + 8;
}

template<> std::size_t FBSerializer::serialize(char *buf, std::size_t buf_size, const Trade &x)
{
    flatbuffers::FlatBufferBuilder fbb;
    auto fsymstr = fbb.CreateString(x.symbol.root);
    auto fsymbuilder = schemas::fb::SymbolBuilder(fbb);
    fsymbuilder.add_root(fsymstr);
    fsymbuilder.add_series(x.symbol.series);
    fsymbuilder.add_listing_exg(x.symbol.listing_exg.mic);
    fsymbuilder.add_issue_type(x.symbol.issue_type);
    auto sym_offset = fsymbuilder.Finish();
    schemas::fb::TradeBuilder etb(fbb);
    schemas::fb::Timestamp tts((std::uint32_t) x.ts.ts, x.ts.ns, (std::int8_t) x.ts.offset, x.ts.dst);
    etb.add_symbol(sym_offset);
    etb.add_seq_num(x.seq_num);
    etb.add_ts(&tts);
    etb.add_reporting_exg(x.reporting_exg.mic);
    auto sp = schemas::fb::Price(x.price.price, x.price.precision, x.price.tick_size, x.price.currency);
    etb.add_price(&sp);
    etb.add_size(x.size);
    etb.add_condition(x.condition);
    etb.add_vol(x.vol);
    etb.add_t_vol(x.t_vol);
    auto etb_offset = etb.Finish();
    fbb.Finish(etb_offset);
    std::size_t finalLen = fbb.GetSize();
    auto buf_ptr = fbb.ReleaseBufferPointer();
    char *raw_buf_ptr = (char *) buf_ptr.get();
    if (finalLen > buf_size)
        throw std::runtime_error("Serialized size exceeds provided buffer");
    std::copy(raw_buf_ptr, raw_buf_ptr + finalLen, buf + 8); //copy to message sector
    //populate 64 bit header (length,checksum)
    *(std::uint32_t *) buf = (std::uint32_t) finalLen;
    *(std::uint32_t *) (buf + 4) = CRC32C_FINISH(crc32c(CRC32C_INIT, raw_buf_ptr, finalLen));
    return finalLen + 8;
}

template<> std::size_t FBSerializer::serialize(char *buf, std::size_t buf_size, const Halt &x)
{
    flatbuffers::FlatBufferBuilder fbb;
    auto fsym_str = fbb.CreateString(x.symbol.root);
    schemas::fb::SymbolBuilder fsymbuilder(fbb);
    fsymbuilder.add_root(fsym_str);
    fsymbuilder.add_listing_exg(x.symbol.listing_exg.mic);
    fsymbuilder.add_series(x.symbol.series);
    fsymbuilder.add_issue_type(x.symbol.issue_type);
    auto sym_offset = fsymbuilder.Finish();
    schemas::fb::HaltBuilder hb(fbb);
    schemas::fb::Timestamp tts((uint32_t) x.ts.ts, x.ts.ns, x.ts.offset, x.ts.dst);
    hb.add_ts(&tts);
    hb.add_symbol(sym_offset);
    hb.add_seq_num(x.seq_num);
    hb.add_reporting_exg(x.reporting_exg.mic);
    hb.add_halt_type(x.halt_type);
    hb.add_halt_status(x.halt_status);
    auto hb_offset = hb.Finish();
    fbb.Finish(hb_offset);
    std::size_t finalLen = fbb.GetSize();
    auto buf_ptr = fbb.ReleaseBufferPointer();
    char *raw_buf_ptr = (char *) buf_ptr.get();
    if (finalLen > buf_size)
        throw std::runtime_error("Serialized size exceeds provided buffer");
    std::copy(raw_buf_ptr, raw_buf_ptr + finalLen, buf + 8); //copy to message sector
    //populate 64 bit header (length,checksum)
    *(std::uint32_t *) buf = (std::uint32_t) finalLen;
    *(std::uint32_t *) (buf + 4) = CRC32C_FINISH(crc32c(CRC32C_INIT, raw_buf_ptr, finalLen));
    return finalLen + 8;
}

inline Price from_fb_price(const schemas::fb::Price &x)
{
    Price p;
    p.price = x.price();
    p.precision = x.precision();
    p.tick_size = x.tick_size();
    p.currency = x.currency();
    return p;
}

inline Timestamp from_fb_timestamp(const schemas::fb::Timestamp &x)
{
    return Timestamp(x.unix(), x.ns(), 0, x.dst());
}

inline Symbol from_fb_symbol(const schemas::fb::Symbol &x)
{
    return Symbol(x.root()->c_str(), x.listing_exg(), x.series(), x.issue_type());
}

template<> std::pair<Quote, bool> FBSerializer::deserialize(const char *b, std::size_t len)
{
    //flatbuffer start pointer
    const std::uint8_t *fb_ptr = reinterpret_cast<const std::uint8_t *> (b + 8);

#ifndef NDEBUG
    flatbuffers::Verifier verifier(fb_ptr, len);
    if ((b == nullptr)
        || !schemas::fb::VerifyEquityQuoteBuffer(verifier))
        return std::make_pair(Quote{}, false);
#endif
    //validate msg size
    std::size_t msg_size = *(std::uint32_t *) b;
    if (msg_size != (len - 8))
        return std::make_pair(Quote{}, false);
    //validate checksum
    std::uint32_t crc = CRC32C_FINISH(crc32c(CRC32C_INIT, fb_ptr, msg_size));
    if (crc != *(std::uint32_t *) (b + 4))
        return std::make_pair(Quote{}, false);

    auto quote_buf = schemas::fb::GetEquityQuote(fb_ptr);
    Quote q;
    q.symbol = from_fb_symbol(*quote_buf->symbol());
    q.seq_num = quote_buf->seq_num();
    q.reporting_exg = Exchange(MIC(quote_buf->reporting_exg()));
    q.ts = from_fb_timestamp(*quote_buf->ts());
    q.condition = quote_buf->condition();
    q.bid = from_fb_price(*quote_buf->bid());
    q.ask = from_fb_price(*quote_buf->ask());
    q.bid_size = quote_buf->bid_size();
    q.ask_size = quote_buf->ask_size();
    return std::make_pair(q, true);
};

template<> std::pair<OptionQuote, bool> FBSerializer::deserialize(const char *b, std::size_t len)
{
    //flatbuffer start pointer
    const std::uint8_t *fb_ptr = reinterpret_cast<const std::uint8_t *> (b + 8);

#ifndef NDEBUG
    flatbuffers::Verifier verifier(fb_ptr, len);
    if ((b == nullptr)
        || !schemas::fb::VerifyOptionQuoteBuffer(verifier))
        return std::make_pair(OptionQuote{}, false);
#endif
    //validate msg size
    std::size_t msg_size = *(std::uint32_t *) b;
    if (msg_size != (len - 8))
        return std::make_pair(OptionQuote{}, false);
    //validate checksum
    std::uint32_t crc = CRC32C_FINISH(crc32c(CRC32C_INIT, fb_ptr, msg_size));
    if (crc != *(std::uint32_t *) (b + 4))
        return std::make_pair(OptionQuote{}, false);
    OptionQuote q;
    auto quote_buf = schemas::fb::GetOptionQuote(fb_ptr);
    q.symbol = from_fb_symbol(*quote_buf->symbol());
    q.seq_num = quote_buf->seq_num();
    q.reporting_exg = Exchange(MIC(quote_buf->reporting_exg()));
    q.ts = from_fb_timestamp(*quote_buf->ts());
    q.condition = quote_buf->condition();
    q.bid = from_fb_price(*quote_buf->bid());
    q.ask = from_fb_price(*quote_buf->ask());
    q.bid_size = quote_buf->bid_size();
    q.ask_size = quote_buf->ask_size();
    q.strike = from_fb_price(*quote_buf->strike());
    q.expiration = from_fb_timestamp(*quote_buf->expiration());
    q.option_type = quote_buf->option_type();
    return std::make_pair(q, true);
}

template<> std::pair<NBBO, bool> FBSerializer::deserialize(const char *b, std::size_t len)
{
    //flatbuffer start pointer
    const std::uint8_t *fb_ptr = reinterpret_cast<const std::uint8_t *> (b + 8);

#ifndef NDEBUG
    flatbuffers::Verifier verifier(fb_ptr, len);
    if ((b == nullptr)
        || !schemas::fb::VerifyNBBOBuffer(verifier))
        return std::make_pair(NBBO{}, false);
#endif
    //validate msg size
    std::size_t msg_size = *(std::uint32_t *) b;
    if (msg_size != (len - 8))
        return std::make_pair(NBBO{}, false);
    //validate checksum
    std::uint32_t crc = CRC32C_FINISH(crc32c(CRC32C_INIT, fb_ptr, msg_size));
    if (crc != *(std::uint32_t *) (b + 4))
        return std::make_pair(NBBO{}, false);
    NBBO n;
    auto nbbo_buf = schemas::fb::GetNBBO(fb_ptr);
    n.symbol = from_fb_symbol(*nbbo_buf->symbol());
    n.seq_num = nbbo_buf->seq_num();
    n.best_bid_exg = MIC(nbbo_buf->best_bid_exg());
    n.best_ask_exg = MIC(nbbo_buf->best_ask_exg());
    n.ts = from_fb_timestamp(*nbbo_buf->ts());
    n.best_bid_condition = nbbo_buf->best_bid_condition();
    n.best_ask_condition = nbbo_buf->best_ask_condition();
    n.best_bid = from_fb_price(*nbbo_buf->best_bid());
    n.best_ask = from_fb_price(*nbbo_buf->best_ask());
    n.best_bid_size = nbbo_buf->best_bid_size();
    n.best_ask_size = nbbo_buf->best_ask_size();
    return std::make_pair(n, true);
};

template<> std::pair<Trade, bool> FBSerializer::deserialize(const char *b, std::size_t len)
{
    //flatbuffer start pointer
    const std::uint8_t *fb_ptr = reinterpret_cast<const std::uint8_t *> (b + 8);

#ifndef NDEBUG
    flatbuffers::Verifier verifier(fb_ptr, len);
    if ((b == nullptr)
        || !schemas::fb::VerifyTradeBuffer(verifier))
        return std::make_pair(Trade{}, false);
#endif
    //validate msg size
    std::size_t msg_size = *(std::uint32_t *) b;
    if (msg_size != (len - 8))
        return std::make_pair(Trade{}, false);
    //validate checksum
    std::uint32_t crc = CRC32C_FINISH(crc32c(CRC32C_INIT, fb_ptr, msg_size));
    if (crc != *(std::uint32_t *) (b + 4))
        return std::make_pair(Trade{}, false);
    Trade t;
    auto trade_buf = schemas::fb::GetTrade(fb_ptr);

    t.symbol = from_fb_symbol(*trade_buf->symbol());
    t.reporting_exg = trade_buf->reporting_exg();
    t.seq_num = trade_buf->seq_num();
    t.ts = from_fb_timestamp(*trade_buf->ts());
    t.condition = trade_buf->condition();
    t.size = trade_buf->size();
    t.price = from_fb_price(*trade_buf->price());
    t.vol = trade_buf->vol();
    t.t_vol = trade_buf->t_vol();
    return std::make_pair(t, true);
}

template<> std::pair<Halt, bool> FBSerializer::deserialize(const char *b, std::size_t len)
{
    //flatbuffer start pointer
    const std::uint8_t *fb_ptr = reinterpret_cast<const std::uint8_t *> (b + 8);

#ifndef NDEBUG
    flatbuffers::Verifier verifier(fb_ptr, len);
    if ((b == nullptr)
        || !schemas::fb::VerifyHaltBuffer(verifier))
        return std::make_pair(Halt{}, false);
#endif
    //validate msg size
    std::size_t msg_size = *(std::uint32_t *) b;
    if (msg_size != (len - 8))
        return std::make_pair(Halt{}, false);
    //validate checksum
    std::uint32_t crc = CRC32C_FINISH(crc32c(CRC32C_INIT, fb_ptr, msg_size));
    if (crc != *(std::uint32_t *) (b + 4))
        return std::make_pair(Halt{}, false);
    auto halt_buf = schemas::fb::GetHalt(fb_ptr);
    Halt h;
    h.symbol = from_fb_symbol(*halt_buf->symbol());
    h.seq_num = halt_buf->seq_num();
    h.reporting_exg = halt_buf->reporting_exg();
    h.ts = from_fb_timestamp(*halt_buf->ts());
    h.halt_type = halt_buf->halt_type();
    h.halt_status = halt_buf->halt_status();
    return std::make_pair(h, true);
};

} //darkfeed
