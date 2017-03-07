#include <gtest/gtest.h>
#include "darkfeed/types/trades.hpp"
#include "darkfeed/types/quotes.hpp"
#include "darkfeed/types/halts.hpp"
#include "darkfeed/serialization/sbe_serializer.hpp"

using namespace darkfeed;


TEST(SBESerializer, SerializeDeserializeQuote)
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
    SBESerializer sbs;
    char buf[1024];
    std::size_t size = sbs.serialize(buf, 1024, q);
    char *q_flatbuf = new char[size];
    // simulate network transfer
    std::copy(buf, buf + size, q_flatbuf);
    ASSERT_TRUE(!std::memcmp(q_flatbuf, buf, size));
    auto cqp = sbs.deserialize<Quote>(buf, size);
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


TEST(SBESerializer, SerializeDeserializeNBBO)
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
    SBESerializer sbs;
    char buf[1024];

    std::size_t size = sbs.serialize(buf, 1024, q);

    char *q_flatbuf = new char[size];
    // simulate network transfer
    std::copy(buf, buf + size, q_flatbuf);

    auto cqp = sbs.deserialize<NBBO>(q_flatbuf, size);
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


TEST(SBESerializer, SerializeDeserializeOptionQuote)
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
    SBESerializer fbs;
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


TEST(SBESerializer, SerializeDeserializeHalt)
{
    Halt h;
    h.symbol = Symbol("GE", MIC::XNYS);
    h.reporting_exg = Exchange(MIC::XNAS);
    h.ts = Timestamp(1436779860, 0, -5, false);
    h.halt_status = HaltStatus::no_open_resume;
    h.halt_type = HaltType::equipment_change;
    h.seq_num = 19038189031;
    SBESerializer sbs;
    char buf[1024];
    std::size_t size = sbs.serialize(buf, 1024, h);
    char *h_flatbuf = new char[size];
    // simulate network transfer
    std::copy(buf, buf + size, h_flatbuf);
    auto hcp = sbs.deserialize<Halt>(buf, size);
    Halt hc = hcp.first;
    ASSERT_TRUE(hcp.second);
    ASSERT_EQ(h.seq_num, hc.seq_num);
    ASSERT_EQ(h.halt_status, hc.halt_status);
    ASSERT_EQ(h.halt_type, hc.halt_type);
    ASSERT_EQ(h.ts, hc.ts);

    ASSERT_EQ(h.symbol.listing_exg, hc.symbol.listing_exg);
    ASSERT_EQ(h.reporting_exg, hc.reporting_exg);
    ASSERT_EQ(h.symbol, hc.symbol);
    delete[] h_flatbuf;
}


TEST(SBESerializer, SerializeDeserializeTrade)
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
    SBESerializer sbs;
    char buf[1024];
    std::size_t size = sbs.serialize(buf, 1024, t);
    char *t_flatbuf = new char[size];
// simulate network transfer
    std::copy(buf, buf + size, t_flatbuf);

// create a copy trade
    auto ctp = sbs.deserialize<Trade>(t_flatbuf, size);
    auto ct = ctp.first;
    ASSERT_EQ(t.symbol, ct.symbol);
    ASSERT_EQ(t.ts, ct.ts);
    ASSERT_EQ(t.seq_num, ct.seq_num);
    ASSERT_EQ(t.price, ct.price);
    ASSERT_EQ(t.size, ct.size);
    ASSERT_EQ(t.vol, ct.vol);
    ASSERT_EQ(t.t_vol, ct.t_vol);
    ASSERT_EQ(t.condition, ct.condition);
    delete[] t_flatbuf;
}
