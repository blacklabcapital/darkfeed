#include <gtest/gtest.h>
#include "darkfeed/types/trades.hpp"
#include "darkfeed/generated/flatbuffers/trade_generated.h"

using namespace darkfeed;

TEST(Trade, DefaultConstructor)
{
    darkfeed::Trade t{};
    ASSERT_STREQ("", t.symbol.root);
    ASSERT_EQ((std::uint32_t) 0, t.price.price);
    ASSERT_EQ((std::uint32_t)0, t.size);
    ASSERT_EQ((std::uint32_t)0, t.vol);
    ASSERT_EQ((std::uint32_t)0, t.t_vol);
    ASSERT_EQ((std::uint32_t)0, t.ts.ts);
    ASSERT_EQ(darkfeed::TradeCondition::none, t.condition);
}

TEST(Trade, CopyConstructor)
{
    darkfeed::Trade t;
    t.symbol = darkfeed::Symbol("MSFT", darkfeed::MIC::XNGS);
    t.ts = darkfeed::Timestamp(1468610956, 0, 0, false);
    std::time_t uts = t.ts.ts;
    t.price = Price(54.21);
    t.size = 100;
    t.condition = darkfeed::TradeCondition::regular;
    t.vol = 35100;
    t.t_vol = 4211;
    auto ct = t;
    ASSERT_EQ(t.symbol, ct.symbol);
    ASSERT_EQ(t.price, ct.price);
    ASSERT_EQ(t.size, ct.size);
    ASSERT_EQ(t.vol, ct.vol);
    ASSERT_EQ(t.t_vol, ct.t_vol);
    ASSERT_EQ(t.condition, ct.condition);
    ASSERT_EQ(uts, ct.ts.ts);
}
