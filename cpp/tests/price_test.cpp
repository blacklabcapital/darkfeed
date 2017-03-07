#include <gtest/gtest.h>
#include <darkfeed/types/price.hpp>

using namespace darkfeed;


TEST(Price, DecimalConstructor)
{
    //minimal decimal constructor
    Price p1(132.15);
    ASSERT_EQ(13215, p1.price);
    ASSERT_EQ(-2, p1.precision);
    ASSERT_EQ(1, p1.tick_size);
    ASSERT_EQ(Currency::USD, p1.currency);

    //tenth of cent precision, 5 tenth of cent minimum tick size
    Price p2(132.155, Currency::CAD, -3, 5);
    ASSERT_EQ(132155, p2.price);
    ASSERT_EQ(-3, p2.precision);
    ASSERT_EQ(5, p2.tick_size);
    ASSERT_EQ(Currency::CAD, p2.currency);
}


TEST(Price, IntegerConstructor)
{
    //minimal integer constructor
    Price p1((uint32_t) 13852);
    ASSERT_EQ(13852, p1.price);
    ASSERT_EQ(-2, p1.precision);
    ASSERT_EQ(1, p1.tick_size);
    ASSERT_EQ(Currency::USD, p1.currency);

    //hundredth of cent precision, 7 hundredth of cent minimum tick size
    Price p2((uint32_t) 1385217, Currency::GBP, -4, 7);
    ASSERT_EQ(1385216, p2.price); //should round down due to tick size of 7
    ASSERT_EQ(-4, p2.precision);
    ASSERT_EQ(7, p2.tick_size);
    ASSERT_EQ(Currency::GBP, p2.currency);
}

TEST(Price, CopyConstructor)
{
    Price p((std::uint32_t) 138523, Currency::GBP, -4, 7);
    Price p2 = p;
    ASSERT_EQ(p.price, p2.price);
    ASSERT_EQ(p.precision, p2.precision);
    ASSERT_EQ(p.tick_size, p2.tick_size);
    ASSERT_EQ(p.currency, p2.currency);
}


TEST(Price, AsInteger)
{
    Price p((uint32_t) 1385221, Currency::GBP, -4, 7);
    uint32_t ip = p.as<uint32_t>();
    ASSERT_EQ(1385223, ip); //should round up due to tick size
}


TEST(Price, AsFloat)
{
    Price p((uint32_t) 1385221, Currency::GBP, -4, 7);
    double fp = p.as<double>();
    ASSERT_DOUBLE_EQ(138.5223, fp); //should round down due to tick size
}


TEST(Price, AsDouble)
{
    Price p((uint32_t) 1385217, Currency::GBP, -4, 7);
    float fp = p.as<float>();
    ASSERT_FLOAT_EQ(138.5216, fp);
}


TEST(Price, SetPrecision)
{
    Price p((uint32_t) 1385217, Currency::GBP, -4, 7);
    p.set_precision(-6);
    ASSERT_EQ(-6, p.precision);
    ASSERT_EQ(138521600, p.price);
    p.set_precision(-2, 5);
    ASSERT_EQ(-2, p.precision);
    ASSERT_EQ(13850, p.price); //gets rounded down due to 5 minimum tick size
}


TEST(Price, LessThan)
{
    //Two prices with unequal currencies should throw
    Price p(138.50);
    Price gbp(138.50, Currency::GBP);
    ASSERT_THROW(p < gbp, std::invalid_argument);

    //Price with equal precision that's higher
    Price p2(138.52);
    ASSERT_TRUE(p < p2);
    //Price with equal precision that's lower
    Price p3(138.49);
    ASSERT_FALSE(p < p3);
    //Price with greater precision that's higher
    Price p4(138.52, Currency::USD, -4);
    ASSERT_TRUE(p < p4);
    //Price with greater precision that's lower
    Price p5(138.49, Currency::USD, -4);
    ASSERT_FALSE(p < p5);
    //Price with lower precision that's higher
    Price p6(138.6, Currency::USD, -1); //this one's different due to truncation
    ASSERT_TRUE(p < p6);
    //Price with lower precision that's lower
    Price p7(138.49, Currency::USD, -1); //this one's different due to truncation
    ASSERT_FALSE(p < p7);
}


TEST(Price, LessThanEqual)
{
    //Two prices with unequal currencies should throw
    Price p(138.50);
    Price gbp(138.50, Currency::GBP);
    ASSERT_THROW(p <= gbp, std::invalid_argument);

    //Price with equal precision that's higher
    Price p2(138.52);
    ASSERT_TRUE(p <= p2);
    //Price with equal precision that's lower
    Price p3(138.49);
    ASSERT_FALSE(p <= p3);
    //Price with equal precision that's equal
    Price p4(138.50);
    ASSERT_TRUE(p <= p4);
    //Price with greater precision that's higher
    Price p5(138.52, Currency::USD, -4);
    ASSERT_TRUE(p <= p5);
    //Price with greater precision that's lower
    Price p6(138.49, Currency::USD, -4);
    ASSERT_FALSE(p <= p6);
    //Price with greater precision that's equal
    Price p7(138.50, Currency::USD, -4);
    ASSERT_TRUE(p <= p7);
    //Price with lower precision that's higher
    Price p8(138.6, Currency::USD, -1); //this one's different due to truncation
    ASSERT_TRUE(p <= p8);
    //Price with lower precision that's lower
    Price p9(138.49, Currency::USD, -1); //this one's different due to truncation
    ASSERT_FALSE(p < p9);
    //Price with lower precision that's equal
    Price p10(138.50, Currency::USD, -1); //this one's different due to truncation
    ASSERT_TRUE(p <= p10);
}


TEST(Price, GreaterThan)
{
    //Two prices with unequal currencies should throw
    Price p(138.50);
    Price gbp(138.50, Currency::GBP);
    ASSERT_THROW(p < gbp, std::invalid_argument);

    //Price with equal precision that's higher
    Price p2(138.52);
    ASSERT_FALSE(p > p2);
    //Price with equal precision that's lower
    Price p3(138.49);
    ASSERT_TRUE(p > p3);
    //Price with greater precision that's higher
    Price p4(138.52, Currency::USD, -4);
    ASSERT_FALSE(p > p4);
    //Price with greater precision that's lower
    Price p5(138.49, Currency::USD, -4);
    ASSERT_TRUE(p > p5);
    //Price with lower precision that's higher
    Price p6(138.6, Currency::USD, -1); //this one's different due to truncation
    ASSERT_FALSE(p > p6);
    //Price with lower precision that's lower
    Price p7(138.49, Currency::USD, -1); //this one's different due to truncation
    ASSERT_TRUE(p > p7);
}


TEST(Price, GreaterThanEqual)
{
    //Two prices with unequal currencies should throw
    Price p(138.50);
    Price gbp(138.50, Currency::GBP);
    ASSERT_THROW(p >= gbp, std::invalid_argument);
    //Price with equal precision that's higher
    Price p2(138.52);
    ASSERT_FALSE(p >= p2);
    //Price with equal precision that's lower
    Price p3(138.49);
    ASSERT_TRUE(p >= p3);
    //Price with equal precision that's equal
    Price p4(138.50);
    ASSERT_TRUE(p >= p4);
    //Price with greater precision that's higher
    Price p5(138.52, Currency::USD, -4);
    ASSERT_FALSE(p >= p5);
    //Price with greater precision that's lower
    Price p6(138.49, Currency::USD, -4);
    ASSERT_TRUE(p >= p6);
    //Price with greater precision that's equal
    Price p7(138.50, Currency::USD, -4);
    ASSERT_TRUE(p >= p7);
    //Price with lower precision that's higher
    Price p8(138.6, Currency::USD, -1); //this one's different due to truncation
    ASSERT_FALSE(p >= p8);
    //Price with lower precision that's lower
    Price p9(138.49, Currency::USD, -1); //this one's different due to truncation
    ASSERT_TRUE(p >= p9);
    //Price with lower precision that's equal
    Price p10(138.50, Currency::USD, -1); //this one's different due to truncation
    ASSERT_TRUE(p >= p10);
}


TEST(Price, Equal)
{
    //Two prices with unequal currencies should throw
    Price p(138.50);
    Price gbp(138.50, Currency::GBP);
    ASSERT_THROW(p == gbp, std::invalid_argument);
    //Price with equal precision that's higher
    Price p2(138.52);
    ASSERT_FALSE(p == p2);
    //Price with equal precision that's lower
    Price p3(138.49);
    ASSERT_FALSE(p == p3);
    //Price with equal precision that's equal
    Price p4(138.50);
    ASSERT_TRUE(p == p4);
    //Price with greater precision that's higher
    Price p5(138.52, Currency::USD, -4);
    ASSERT_FALSE(p == p5);
    //Price with greater precision that's lower
    Price p6(138.49, Currency::USD, -4);
    ASSERT_FALSE(p == p6);
    //Price with greater precision that's equal
    Price p7(138.50, Currency::USD, -4);
    ASSERT_TRUE(p == p7);
    //Price with lower precision that's higher
    Price p8(138.6, Currency::USD, -1); //this one's different due to truncation
    ASSERT_FALSE(p == p8);
    //Price with lower precision that's lower
    Price p9(138.49, Currency::USD, -1); //this one's different due to truncation
    ASSERT_FALSE(p == p9);
    //Price with lower precision that's equal
    Price p10(138.50, Currency::USD, -1); //this one's different due to truncation
    ASSERT_TRUE(p == p10);
}


TEST(Price, NotEqual)
{
    //Two prices with unequal currencies should throw
    Price p(138.50);
    Price gbp(138.50, Currency::GBP);
    ASSERT_THROW(p != gbp, std::invalid_argument);
    //Price with equal precision that's higher
    Price p2(138.52);
    ASSERT_TRUE(p != p2);
    //Price with equal precision that's lower
    Price p3(138.49);
    ASSERT_TRUE(p != p3);
    //Price with equal precision that's equal
    Price p4(138.50);
    ASSERT_FALSE(p != p4);
    //Price with greater precision that's higher
    Price p5(138.52, Currency::USD, -4);
    ASSERT_TRUE(p != p5);
    //Price with greater precision that's lower
    Price p6(138.49, Currency::USD, -4);
    ASSERT_TRUE(p != p6);
    //Price with greater precision that's equal
    Price p7(138.50, Currency::USD, -4);
    ASSERT_FALSE(p != p7);
    //Price with lower precision that's higher
    Price p8(138.6, Currency::USD, -1); //this one's different due to truncation
    ASSERT_TRUE(p != p8);
    //Price with lower precision that's lower
    Price p9(138.49, Currency::USD, -1); //this one's different due to truncation
    ASSERT_TRUE(p != p9);
    //Price with lower precision that's equal
    Price p10(138.50, Currency::USD, -1); //this one's different due to truncation
    ASSERT_FALSE(p != p10);
}
