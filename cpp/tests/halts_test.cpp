#include <gtest/gtest.h>
#include "darkfeed/types/halts.hpp"

using namespace darkfeed;


TEST(Halt, DefaultConstructor) //Need to add a real default constructor
{
    Halt h{};
    ASSERT_STREQ("", h.symbol.root);
    ASSERT_EQ(MIC::NONE, h.symbol.listing_exg.mic);
    ASSERT_EQ(MIC::NONE, h.reporting_exg.mic);
    ASSERT_EQ(HaltStatus::none, h.halt_status);
    ASSERT_EQ(HaltType::none, h.halt_type);
}
/*
TEST(Halt, Deserialize)
{
    Halt h;
    h.symbol = Symbol("GE", MIC::XNYS);
    h.reporting_exg = Exchange(MIC::XNAS);
    h.ts = Timestamp(1436779860, 0, -5, false);
    h.halt_status = HaltStatus::no_open_resume;
    h.halt_type = HaltType::equipment_change;
    h.seq_num = 19038189031;
    auto srz_h = h.serialize();
    char *h_flatbuf = new char[srz_h.second];
    // simulate network transfer
    std::copy(srz_h.first.get(), srz_h.first.get() + srz_h.second, h_flatbuf);
    ASSERT_NE(nullptr, srz_h.first.get());

    Halt hc;
    hc.deserialize((const char *) (srz_h.first.get()), srz_h.second);

    ASSERT_EQ(h.seq_num, hc.seq_num);
    ASSERT_EQ(h.halt_status, hc.halt_status);
    ASSERT_EQ(h.halt_type, hc.halt_type);
    ASSERT_EQ(h.ts, hc.ts);

    ASSERT_EQ(h.symbol.listing_exg, hc.symbol.listing_exg);
    ASSERT_EQ(h.reporting_exg, hc.reporting_exg);
    ASSERT_STREQ(h.symbol.root, hc.symbol.root);
    delete[] h_flatbuf;
}
 */
