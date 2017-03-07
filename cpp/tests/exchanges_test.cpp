#define GTEST_HAS_TR1_TUPLE 0
#include <gtest/gtest.h>
#include "darkfeed/types/exchanges.hpp"

TEST(Exchange, DefaultConstructor)
{
    darkfeed::Exchange e;
    EXPECT_EQ(darkfeed::MIC::NONE, e.mic);
}

TEST(Exchange, IDConstructor)
{
    const std::string estr = "XNYS";
    darkfeed::MIC mic = darkfeed::MIC::XNYS;
    darkfeed::Exchange e(mic);
    EXPECT_EQ(darkfeed::MIC::XNYS, e.mic);
    EXPECT_EQ(estr, e.mic_str());
}

TEST(Exchange, StrConstructor)
{
    std::string estr = "XNYS";
    darkfeed::Exchange e(estr);
    EXPECT_EQ(darkfeed::MIC::XNYS, e.mic);
    EXPECT_EQ(estr, e.mic_str());
    estr = "ICEL";
    e = std::string(estr);
    EXPECT_EQ(darkfeed::MIC::ICEL, e.mic);
    EXPECT_EQ(estr, e.mic_str());
}

TEST(Exchange, CopyConstructor)
{
    const std::string estr = "XNYS";
    darkfeed::Exchange e(estr);
    darkfeed::Exchange ne = e;

    EXPECT_EQ(darkfeed::MIC::XNYS, e.mic);
    EXPECT_EQ(darkfeed::MIC::XNYS, ne.mic);
}
