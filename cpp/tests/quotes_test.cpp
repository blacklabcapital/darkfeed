#include <gtest/gtest.h>
#include "darkfeed/types/quotes.hpp"

using namespace darkfeed;


TEST(Quote, DefaultConstructor) //Note actually add a default constructor
{
    Quote q{};
    ASSERT_STREQ("", q.symbol.root);
    ASSERT_EQ(MIC::NONE, q.symbol.listing_exg.mic);
    ASSERT_EQ(MIC::NONE, q.reporting_exg.mic);
    ASSERT_EQ((std::uint32_t) 0, q.bid.price);
    ASSERT_EQ((std::uint32_t) 0, q.ask.price);
    ASSERT_EQ((std::uint32_t)0, q.bid_size);
    ASSERT_EQ((std::uint32_t)0, q.ask_size);
    ASSERT_EQ((std::uint32_t)0, q.ts.ts);
    ASSERT_EQ(QuoteCondition::none, q.condition);
}

TEST(Quote, CopyConstructor)
{
    Quote q;
    q.symbol = Symbol("GE", Exchange(MIC::XNYS));
    q.reporting_exg = Exchange(MIC::XNAS);
    q.ts = Timestamp(1436779860, 0, -5, false);
    q.condition = QuoteCondition::fast_trading;
    q.bid = Price(29.51);
    q.ask = Price(29.52);
    q.bid_size = 500;
    q.ask_size = 400;

    Quote cq = q;

    ASSERT_EQ(q.bid, cq.bid);
    ASSERT_EQ(q.ask, cq.ask);

    ASSERT_EQ(q.bid_size, cq.bid_size);
    ASSERT_EQ(q.ask_size, cq.ask_size);
    ASSERT_EQ(q.condition, cq.condition);

    ASSERT_EQ(MIC::XNYS, cq.symbol.listing_exg.mic);
    ASSERT_EQ(MIC::XNAS, cq.reporting_exg.mic);
    ASSERT_EQ(q.symbol, cq.symbol);
}
