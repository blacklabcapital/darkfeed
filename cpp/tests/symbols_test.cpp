#define GTEST_HAS_TR1_TUPLE 0
#include <gtest/gtest.h>
#include "darkfeed/types/symbol.hpp"

using namespace darkfeed;
//Base constructor
TEST(Symbol, Constructor)
{
    Symbol s;
    ASSERT_STREQ("\0", s.root);
    ASSERT_EQ('\0', s.series);
    ASSERT_EQ(IssueType::normal, s.issue_type);
}


TEST(Symbol, StrConstructor)
{
    const char *root_sym = "BRKB";
    const char series = 'A';
    const MIC le = MIC::XNYS;
    const IssueType st = IssueType::preferred;
    Symbol s(root_sym, le, series, st);
    ASSERT_STREQ(root_sym, s.root);
    ASSERT_EQ(series, s.series);
    ASSERT_EQ(st, s.issue_type);
}


TEST(Symbol, CopyConstructor)
{
    const char *root_sym = "BRKB";
    const char series = 'A';
    const MIC le = MIC::XNYS;
    const IssueType st = IssueType::preferred;
    Symbol s(root_sym, le, series, st);

    auto sc = s;

    ASSERT_EQ(s, sc);
}


TEST(Symbol, ParseConstructor)
{
    MIC le = MIC::XNYS;
    const char *sym = "BRKB.PR.A";
    const char *root_sym = "BRKB";
    const char series = 'A';
    auto st = IssueType::preferred;
    Symbol s(le, sym);
    ASSERT_STREQ(root_sym, s.root);
    ASSERT_EQ(series, s.series);
    ASSERT_EQ(st, s.issue_type);

    const char *sym2 = "AAPL";
    le = MIC::XNGS;
    Symbol s2(le, sym2);
    ASSERT_STREQ(sym2,s2.root);
    ASSERT_EQ(0,s2.series);
    ASSERT_EQ(IssueType::normal, s2.issue_type);
}
