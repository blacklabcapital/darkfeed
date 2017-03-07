#include <gtest/gtest.h>
#include <darkfeed/generated/flatbuffers/trade_conditions_generated.h>
#include <darkfeed/types/trades.hpp>
#include <darkfeed/generated/flatbuffers/trade_generated.h>
#include "darkfeed/generated/flatbuffers/nbbo_generated.h"
#include "darkfeed/generated/flatbuffers/quote_generated.h"
#include "darkfeed/types/quotes.hpp"
#include "darkfeed/types/halts.hpp"
#include "darkfeed/serialization/flatbuffers_serializer.hpp"

using namespace darkfeed;

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


TEST(FBSerializer, SerializeQuote)
{
    Quote q;
    q.symbol = Symbol("GE", MIC::XNYS);
    q.reporting_exg = MIC::XNAS;
    q.ts = Timestamp(1436779860, 0, -5, false);
    q.condition = QuoteCondition::fast_trading;
    q.bid = Price(29.51);
    q.ask = Price(29.52);
    q.bid_size = 500;
    q.ask_size = 400;
    q.seq_num = 151313131;
    FBSerializer fbs;
    char buf[1024];
    std::size_t size = fbs.serialize(buf, 1024, q);

    char *q_flatbuf = new char[size];
    // simulate network transfer
    std::copy(buf, buf + size, q_flatbuf);
    ASSERT_EQ(120, *(std::uint32_t *) q_flatbuf);
    ASSERT_EQ(3808629628, *(std::uint32_t *) (q_flatbuf + 4));

    auto quote = schemas::fb::GetEquityQuote(q_flatbuf + 8);
    ASSERT_EQ(q.seq_num, quote->seq_num());
    ASSERT_EQ(q.bid, from_fb_price(*quote->bid()));
    ASSERT_EQ(q.ask, from_fb_price(*quote->ask()));
    ASSERT_NE(nullptr, quote->ts());
    ASSERT_EQ(q.ts, from_fb_timestamp(*quote->ts()));

    ASSERT_EQ(q.bid_size, quote->bid_size());
    ASSERT_EQ(q.ask_size, quote->ask_size());

    ASSERT_EQ(q.symbol, from_fb_symbol(*quote->symbol()));
    delete[] q_flatbuf;
}


TEST(FBSerializer, DeserializeQuote)
{
    Quote q;

    q.symbol = Symbol("GE", MIC::XNYS);
    q.reporting_exg = Exchange(MIC::XNAS);
    q.ts = Timestamp(1436779860, 0, 0, false);
    q.condition = QuoteCondition::fast_trading;
    q.bid = Price(29.51);
    q.ask = Price(29.52);
    q.bid_size = 500;
    q.ask_size = 400;
    q.seq_num = 12314131231;
    FBSerializer fbs;
    char buf[1024];
    std::size_t size = fbs.serialize(buf, 1024, q);
    char *q_flatbuf = new char[size];
    // simulate network transfer
    std::copy(buf, buf + size, q_flatbuf);

    auto cqp = fbs.deserialize<Quote>(q_flatbuf, size);
    Quote cq(cqp.first);
    ASSERT_TRUE(cqp.second);
    ASSERT_EQ(q.ask, cq.ask);
    ASSERT_EQ(q.bid, cq.bid);
    ASSERT_EQ(q.seq_num, cq.seq_num);
    ASSERT_EQ(q.seq_num, cq.seq_num);
    ASSERT_EQ(q.bid_size, cq.bid_size);
    ASSERT_EQ(q.ask_size, cq.ask_size);
    ASSERT_EQ(q.ts, cq.ts);
    ASSERT_EQ(q.symbol, cq.symbol);
    ASSERT_EQ(q.reporting_exg.mic, cq.reporting_exg.mic);
    delete[] q_flatbuf;
}


TEST(FBSerializer, SerializeNBBO)
{
    NBBO q;
    q.symbol = Symbol("GE", MIC::XNYS);
    q.best_bid_exg = Exchange(MIC::XNAS);
    q.best_ask_exg = Exchange(MIC::BATY);
    q.ts = Timestamp(1436779860, 0, -5, false);
    q.best_bid_condition = QuoteCondition::fast_trading;
    q.best_ask_condition = QuoteCondition::closing;
    q.best_bid = Price(29.51);
    q.best_ask = Price(29.52);
    q.best_bid_size = 500;
    q.best_ask_size = 400;
    q.seq_num = 1231313;
    FBSerializer fbs;
    char buf[1024];
    std::size_t size = fbs.serialize(buf, 1024, q);

    char *q_flatbuf = new char[size];
    // simulate network transfer
    std::copy(buf, buf + size, q_flatbuf);
    ASSERT_EQ(120, *(std::uint32_t *) q_flatbuf);
    ASSERT_EQ(2266663138, *(std::uint32_t *) (q_flatbuf + 4));

    auto nbbo = schemas::fb::GetNBBO(q_flatbuf + 8);
    ASSERT_EQ(q.seq_num, nbbo->seq_num());
    ASSERT_EQ(q.best_bid, from_fb_price(*nbbo->best_bid()));
    ASSERT_EQ(q.best_ask, from_fb_price(*nbbo->best_ask()));

    ASSERT_EQ(q.best_bid_size, nbbo->best_bid_size());
    ASSERT_EQ(q.best_ask_size, nbbo->best_ask_size());

    ASSERT_EQ(MIC::XNYS, MIC(nbbo->symbol()->listing_exg()));
    ASSERT_EQ(MIC::XNAS, MIC(nbbo->best_bid_exg()));
    ASSERT_EQ(MIC::BATY, MIC(nbbo->best_ask_exg()));
    ASSERT_EQ(q.symbol, from_fb_symbol(*nbbo->symbol()));
    delete[] q_flatbuf;
}


TEST(FBSerializer, DeserializeNBBO)
{
    NBBO q;

    q.symbol = Symbol("GE", MIC::XNYS);
    q.reporting_exg = Exchange(MIC::XNAS);
    q.ts = Timestamp(1436779860, 0, 0, false);
    q.best_bid_condition = QuoteCondition::regular;
    q.best_ask_condition = QuoteCondition::regular;
    q.best_bid = Price(29.51);
    q.best_ask = Price(29.52);
    q.best_bid_size = 500;
    q.best_ask_size = 400;
    q.seq_num = 12931013;
    FBSerializer fbs;
    char buf[1024];
    std::size_t size = fbs.serialize(buf, 1024, q);
    char *q_flatbuf = new char[size];
    // simulate network transfer
    std::copy(buf, buf + size, q_flatbuf);

    auto cqp = fbs.deserialize<NBBO>(q_flatbuf, size);
    NBBO cq = cqp.first;
    ASSERT_EQ(q.seq_num, cq.seq_num);
    ASSERT_EQ(q.best_bid, cq.best_bid);
    ASSERT_EQ(q.best_ask, cq.best_ask);
    ASSERT_EQ(q.ts, cq.ts);

    ASSERT_EQ(q.best_bid_size, cq.best_bid_size);
    ASSERT_EQ(q.best_ask_size, cq.best_ask_size);

    ASSERT_EQ(q.symbol, cq.symbol);
    ASSERT_EQ(q.best_bid_exg.mic, cq.best_bid_exg.mic);
    ASSERT_EQ(q.best_ask_exg.mic, cq.best_ask_exg.mic);
    ASSERT_STREQ(q.symbol.root, cq.symbol.root);
    delete[] q_flatbuf;
}


TEST(FBSerializer, SerializeOptionQuote)
{
    OptionQuote q;
    q.symbol = Symbol("GE", MIC::XNYS);
    q.reporting_exg = MIC::XNAS;
    q.ts = Timestamp(1436779860, 0, -5, false);
    q.condition = QuoteCondition::fast_trading;
    q.bid = Price(29.51);
    q.ask = Price(29.52);
    q.bid_size = 500;
    q.ask_size = 400;
    q.seq_num = 151313131;
    q.expiration = Timestamp(1436979860, 0, -5, false);
    q.strike = Price(31.50);
    q.option_type = OptionType::put;
    FBSerializer fbs;
    char buf[1024];
    std::size_t size = fbs.serialize(buf, 1024, q);

    char *q_flatbuf = new char[size];
    // simulate network transfer
    std::copy(buf, buf + size, q_flatbuf);
    ASSERT_EQ(144, *(std::uint32_t *) q_flatbuf);
    ASSERT_EQ(1755263609, *(std::uint32_t *) (q_flatbuf + 4));
    auto quote = schemas::fb::GetOptionQuote(q_flatbuf + 8);
    ASSERT_EQ(q.seq_num, quote->seq_num());
    ASSERT_EQ(q.bid, from_fb_price(*quote->bid()));
    ASSERT_EQ(q.ask, from_fb_price(*quote->ask()));
    ASSERT_EQ(q.strike, from_fb_price(*quote->strike()));
    ASSERT_EQ(q.bid_size, quote->bid_size());
    ASSERT_EQ(q.ask_size, quote->ask_size());
    ASSERT_NE(nullptr, quote->ts());
    ASSERT_NE(nullptr, quote->expiration());
    ASSERT_EQ(q.ts, from_fb_timestamp(*quote->ts()));
    ASSERT_EQ(q.expiration, from_fb_timestamp(*quote->expiration()));
    ASSERT_EQ(q.option_type, quote->option_type());
    ASSERT_EQ(MIC::XNAS, MIC(quote->reporting_exg()));
    ASSERT_EQ(q.symbol, from_fb_symbol(*quote->symbol()));
    delete[] q_flatbuf;
}


TEST(FBSerializer, DeserializeOptionQuote)
{
    OptionQuote q;

    q.symbol = Symbol("GE", MIC::XNYS);
    q.reporting_exg = Exchange(MIC::XNAS);
    q.ts = Timestamp(1436779860, 0, 0, false);
    q.expiration = Timestamp(1436998250, 0, 0, false);
    q.condition = QuoteCondition::fast_trading;
    q.option_type = OptionType::call;
    q.bid = Price(29.51);
    q.ask = Price(29.52);
    q.strike = Price(30.66);
    q.bid_size = 500;
    q.ask_size = 400;
    q.seq_num = 12314131231;
    FBSerializer fbs;
    char buf[1024];
    std::size_t size = fbs.serialize(buf, 1024, q);
    char *q_flatbuf = new char[size];
    // simulate network transfer
    std::copy(buf, buf + size, q_flatbuf);

    auto cqp = fbs.deserialize<OptionQuote>(q_flatbuf, size);
    OptionQuote cq = cqp.first;
    ASSERT_TRUE(cqp.second);
    ASSERT_EQ(q.ask, cq.ask);
    ASSERT_EQ(q.bid, cq.bid);
    ASSERT_EQ(q.seq_num, cq.seq_num);
    ASSERT_EQ(q.seq_num, cq.seq_num);
    ASSERT_EQ(q.bid_size, cq.bid_size);
    ASSERT_EQ(q.ask_size, cq.ask_size);
    ASSERT_EQ(q.ts, cq.ts);
    ASSERT_EQ(q.expiration, cq.expiration);
    ASSERT_EQ(q.strike, cq.strike);
    ASSERT_EQ(q.option_type, cq.option_type);
    ASSERT_EQ(q.symbol, cq.symbol);
    ASSERT_EQ(q.reporting_exg.mic, cq.reporting_exg.mic);
    ASSERT_STREQ(q.symbol.root, cq.symbol.root);
    delete[] q_flatbuf;
}


TEST(FBSerializer, SerializeHalt)
{
    Halt h;
    h.symbol = Symbol("GE", MIC::XNYS);
    h.reporting_exg = Exchange(MIC::XNAS);
    h.ts = Timestamp(1436779860, 0, -5, false);
    h.halt_status = HaltStatus::no_open_resume;
    h.halt_type = HaltType::equipment_change;
    h.seq_num = 12903131;
    FBSerializer fbs;
    char buf[1024];
    std::size_t size = fbs.serialize(buf, 1024, h);

    char *q_flatbuf = new char[size];
    // simulate network transfer
    std::copy(buf, buf + size, q_flatbuf);
    ASSERT_EQ(88, *(std::uint32_t *) q_flatbuf);
    ASSERT_EQ(1314324380, *(std::uint32_t *) (q_flatbuf + 4));

    auto halt = schemas::fb::GetHalt(q_flatbuf + 8);

    ASSERT_EQ(h.seq_num, halt->seq_num());
    ASSERT_EQ(h.halt_status, halt->halt_status());
    ASSERT_EQ(h.halt_type, halt->halt_type());
    ASSERT_EQ(h.ts, from_fb_timestamp(*halt->ts()));

    ASSERT_EQ(MIC::XNAS, MIC(halt->reporting_exg()));
    ASSERT_EQ(h.symbol, from_fb_symbol(*halt->symbol()));
    delete[] q_flatbuf;
}


TEST(FBSerializer, DeserializeHalt)
{
    Halt h;
    h.symbol = Symbol("GE", MIC::XNYS);
    h.reporting_exg = Exchange(MIC::XNAS);
    h.ts = Timestamp(1436779860, 0, -5, false);
    h.halt_status = HaltStatus::no_open_resume;
    h.halt_type = HaltType::equipment_change;
    h.seq_num = 19038189031;
    FBSerializer fbs;
    char buf[1024];
    std::size_t size = fbs.serialize(buf, 1024, h);
    char *q_flatbuf = new char[size];
    // simulate network transfer
    std::copy(buf, buf + size, q_flatbuf);
    auto srz_h = fbs.serialize(q_flatbuf, size, h);
    auto hcp = fbs.deserialize<Halt>(q_flatbuf, size);
    Halt hc = hcp.first;
    ASSERT_TRUE(hcp.second);
    ASSERT_EQ(h.seq_num, hc.seq_num);
    ASSERT_EQ(h.halt_status, hc.halt_status);
    ASSERT_EQ(h.halt_type, hc.halt_type);
    ASSERT_EQ(h.ts, hc.ts);

    ASSERT_EQ(h.symbol.listing_exg, hc.symbol.listing_exg);
    ASSERT_EQ(h.reporting_exg, hc.reporting_exg);
    ASSERT_EQ(h.symbol, hc.symbol);
    delete[] q_flatbuf;
}


TEST(FBSerializer, SerializeTrade)
{
    darkfeed::Trade t;
    t.ts = darkfeed::Timestamp(1468610956, 0, 0, false);
    t.symbol = darkfeed::Symbol("MSFT", darkfeed::MIC::XNGS);
    t.price = Price(54.21);
    t.size = 100;
    t.condition = darkfeed::TradeCondition::regular;
    t.vol = 35100;
    t.t_vol = 4211;
    t.seq_num = 1203810931;
    FBSerializer fbs;
    char buf[1024];
    std::size_t size = fbs.serialize(buf, 1024, t);

    char *q_flatbuf = new char[size];
    // simulate network transfer
    std::copy(buf, buf + size, q_flatbuf);
    ASSERT_EQ(120, *(std::uint32_t *) q_flatbuf);
    ASSERT_EQ(1710647678, *(std::uint32_t *) (q_flatbuf + 4));

    // Now let's read it
    auto trade = schemas::fb::GetTrade(q_flatbuf + 8);
    ASSERT_STREQ(t.symbol.root, trade->symbol()->root()->c_str());
    ASSERT_EQ(t.seq_num, trade->seq_num());
    ASSERT_EQ(t.price, from_fb_price(*trade->price()));
    ASSERT_EQ(t.size, trade->size());
    ASSERT_EQ(t.t_vol, trade->t_vol());
    ASSERT_EQ(t.vol, trade->vol());
    ASSERT_EQ(t.condition, darkfeed::TradeCondition(trade->condition()));
    ASSERT_EQ(t.ts, from_fb_timestamp(*trade->ts()));
    delete[] q_flatbuf;
}


TEST(FBSerializer, DeserializeTrade)
{
    darkfeed::Trade t;
    t.ts = darkfeed::Timestamp(1468610956, 0, 0, false);
    t.symbol = darkfeed::Symbol("MSFT", darkfeed::MIC::XNGS);
    t.price = Price(54.21);
    t.size = 100;
    t.condition = darkfeed::TradeCondition::regular;
    t.vol = 35100;
    t.t_vol = 4211;
    t.seq_num = 123901;
    FBSerializer fbs;
    char buf[1024];
    std::size_t size = fbs.serialize(buf, 1024, t);
    char *q_flatbuf = new char[size];
    // simulate network transfer
    std::copy(buf, buf + size, q_flatbuf);
    auto srz_h = fbs.serialize(q_flatbuf, size, t);
    auto hcp = fbs.deserialize<Trade>(q_flatbuf, size);
    auto srz_t = fbs.serialize(q_flatbuf, size, t);
// create a copy trade
    auto ctp = fbs.deserialize<Trade>(q_flatbuf, size);
    auto ct = ctp.first;
    ASSERT_EQ(t.symbol, ct.symbol);
    ASSERT_EQ(t.ts, ct.ts);
    ASSERT_EQ(t.seq_num, ct.seq_num);
    ASSERT_EQ(t.price, ct.price);
    ASSERT_EQ(t.size, ct.size);
    ASSERT_EQ(t.vol, ct.vol);
    ASSERT_EQ(t.t_vol, ct.t_vol);
    ASSERT_EQ(t.condition, ct.condition);
    delete[] q_flatbuf;
}
