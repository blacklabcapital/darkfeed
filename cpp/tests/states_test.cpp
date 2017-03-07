#define GTEST_HAS_TR1_TUPLE 0
#include <gtest/gtest.h>
#include "../include/mfeed/timestamp.hpp"
#include "../include/mfeed/states.hpp"


TEST(EquityState, GetSetHalt)
{
    darkfeed::EquityState ss;
    ASSERT_EQ(darkfeed::HaltType::none, ss.get_halt().halt_type);
    ss.push_halt(darkfeed::Halt(darkfeed::HaltType::news, darkfeed::HaltStatus::halted));
    ASSERT_EQ(darkfeed::HaltType::news, ss.get_halt().halt_type);
    ASSERT_EQ(darkfeed::HaltStatus::halted, ss.get_halt().halt_status);
}


TEST(EquityState, PushNBBO)
{
    darkfeed::EquityState ss;
    darkfeed::NBBO q;
    q.symbol = darkfeed::Symbol("MSFT", darkfeed::MIC::XNGS);
    q.best_bid = 2951;
    q.best_ask = 2952;
    q.best_bid_exg = darkfeed::MIC::BATS;
    q.best_ask_exg = darkfeed::MIC::BATY;
    q.best_bid_size = 400;
    q.best_ask_size = 400;
    q.best_bid_condition = darkfeed::QuoteCondition::regular;
    q.best_ask_condition = darkfeed::QuoteCondition::regular;
    q.ts = darkfeed::Timestamp(1458912900, 0, -5, false);

    // push NBBO
    ss.push_nbbo(q);

    // check we got our same quote back
    auto pq = ss.get_nbbo();
    ASSERT_EQ(q.best_bid, pq.best_bid);
    ASSERT_EQ(q.best_ask, pq.best_ask);

    // overwrite past quote with worse one
    q.best_bid_exg = darkfeed::MIC::BATS;
    q.best_ask_exg = darkfeed::MIC::XNYS;
    q.best_bid = 2949;
    ++q.ts.ts;
    ss.push_nbbo(q);

    pq = ss.get_nbbo();
    ASSERT_EQ((std::uint32_t)2949, pq.best_bid);
    ASSERT_EQ(darkfeed::MIC::BATS, pq.best_bid_exg.mic);
    ASSERT_EQ(darkfeed::MIC::XNYS, pq.best_ask_exg.mic);
}


TEST(EquityState, PushTrade)
{
    darkfeed::EquityState ss;
    darkfeed::Trade t;
    t.symbol = darkfeed::Symbol("MSFT", darkfeed::MIC::XNGS);
    t.price = 10519;
    t.size = 500;
    t.condition = darkfeed::TradeCondition::regular;
    t.reporting_exg = darkfeed::MIC::XNAS;
    t.vol = 45000;
    t.t_vol = 3501;
    t.ts.ts = 1458912900;

    ss.push_trade(t);

    // check we get the same trade back for last
    auto lt = ss.get_last_trade();
    ASSERT_EQ(t.price, lt.price);
    ASSERT_EQ(t.ts.ts, lt.ts.ts);

    //push a new trade that can't affect last (delayed)
    t.vol = 46000;
    t.t_vol = 3703;
    t.price = 10518;
    t.condition = darkfeed::TradeCondition::delayed;
    ++t.ts.ts;
    ss.push_trade(t);
    lt = ss.get_last_trade();
    // check it had an effect on last price
    ASSERT_NE(t.price, lt.price);
    // check it hasn't affected volume
    ASSERT_NE(t.vol, lt.vol);
    ASSERT_NE(t.t_vol, lt.t_vol);
}
