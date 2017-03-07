/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _DARKFEED_SCHEMAS_SBE_QUOTECONDITION_H_
#define _DARKFEED_SCHEMAS_SBE_QUOTECONDITION_H_

#if defined(SBE_HAVE_CMATH)
/* cmath needed for std::numeric_limits<double>::quiet_NaN() */
#  include <cmath>
#  define SBE_FLOAT_NAN std::numeric_limits<float>::quiet_NaN()
#  define SBE_DOUBLE_NAN std::numeric_limits<double>::quiet_NaN()
#else
/* math.h needed for NAN */
#  include <math.h>
#  define SBE_FLOAT_NAN NAN
#  define SBE_DOUBLE_NAN NAN
#endif

#if __cplusplus >= 201103L
#  include <cstdint>
#  include <string>
#  include <cstring>
#endif

#if __cplusplus >= 201103L
#  define SBE_CONSTEXPR constexpr
#else
#  define SBE_CONSTEXPR
#endif

#include <sbe/sbe.h>

using namespace sbe;

namespace darkfeed
{
namespace schemas
{
namespace sbe
{

class QuoteCondition {
 public:

    enum Value {
        none = (std::uint8_t) 0,
        regular = (std::uint8_t) 1,
        active = (std::uint8_t) 2,
        inactive = (std::uint8_t) 3,
        exchange_best = (std::uint8_t) 4,
        consolidated_best = (std::uint8_t) 5,
        locked = (std::uint8_t) 6,
        crossed = (std::uint8_t) 7,
        depth = (std::uint8_t) 8,
        fast_trading = (std::uint8_t) 9,
        non_firm = (std::uint8_t) 10,
        manual = (std::uint8_t) 11,
        outright_price = (std::uint8_t) 12,
        implied_price = (std::uint8_t) 13,
        depth_on_offer = (std::uint8_t) 14,
        depth_on_bid = (std::uint8_t) 15,
        depth_on_bid_offer = (std::uint8_t) 16,
        closing = (std::uint8_t) 17,
        news = (std::uint8_t) 18,
        trading_range = (std::uint8_t) 19,
        order_influx = (std::uint8_t) 20,
        due_to_related = (std::uint8_t) 21,
        news_pending = (std::uint8_t) 22,
        additional_info = (std::uint8_t) 23,
        additional_info_due_to_related = (std::uint8_t) 24,
        resume = (std::uint8_t) 25,
        view_of_common = (std::uint8_t) 26,
        volume_alert = (std::uint8_t) 27,
        order_imbalance = (std::uint8_t) 28,
        equipment = (std::uint8_t) 29,
        no_open_resume = (std::uint8_t) 30,
        regular_eth = (std::uint8_t) 31,
        auto_exec = (std::uint8_t) 32,
        auto_exec_eth = (std::uint8_t) 33,
        fast_market_eth = (std::uint8_t) 34,
        inactive_eth = (std::uint8_t) 35,
        rotation = (std::uint8_t) 36,
        rotation_eth = (std::uint8_t) 37,
        halt = (std::uint8_t) 38,
        halt_eth = (std::uint8_t) 39,
        due_to_news = (std::uint8_t) 40,
        due_to_news_pending = (std::uint8_t) 41,
        trading_resume = (std::uint8_t) 42,
        out_of_seq = (std::uint8_t) 43,
        bid_specialist = (std::uint8_t) 44,
        offer_specialist = (std::uint8_t) 45,
        bid_offer_specialist = (std::uint8_t) 46,
        end_of_day_sam = (std::uint8_t) 47,
        forbidden_sam = (std::uint8_t) 48,
        frozen_sam = (std::uint8_t) 49,
        pre_opening_sam = (std::uint8_t) 50,
        opening_sam = (std::uint8_t) 51,
        open_sam = (std::uint8_t) 52,
        surveillance_sam = (std::uint8_t) 53,
        suspended_sam = (std::uint8_t) 54,
        reserved_sam = (std::uint8_t) 55,
        no_active_sam = (std::uint8_t) 56,
        restricted = (std::uint8_t) 57,
        NULL_VALUE = (std::uint8_t) 255
    };

    static QuoteCondition::Value get(const std::uint8_t value)
    {
        switch (value)
        {
        case 0: return none;
        case 1: return regular;
        case 2: return active;
        case 3: return inactive;
        case 4: return exchange_best;
        case 5: return consolidated_best;
        case 6: return locked;
        case 7: return crossed;
        case 8: return depth;
        case 9: return fast_trading;
        case 10: return non_firm;
        case 11: return manual;
        case 12: return outright_price;
        case 13: return implied_price;
        case 14: return depth_on_offer;
        case 15: return depth_on_bid;
        case 16: return depth_on_bid_offer;
        case 17: return closing;
        case 18: return news;
        case 19: return trading_range;
        case 20: return order_influx;
        case 21: return due_to_related;
        case 22: return news_pending;
        case 23: return additional_info;
        case 24: return additional_info_due_to_related;
        case 25: return resume;
        case 26: return view_of_common;
        case 27: return volume_alert;
        case 28: return order_imbalance;
        case 29: return equipment;
        case 30: return no_open_resume;
        case 31: return regular_eth;
        case 32: return auto_exec;
        case 33: return auto_exec_eth;
        case 34: return fast_market_eth;
        case 35: return inactive_eth;
        case 36: return rotation;
        case 37: return rotation_eth;
        case 38: return halt;
        case 39: return halt_eth;
        case 40: return due_to_news;
        case 41: return due_to_news_pending;
        case 42: return trading_resume;
        case 43: return out_of_seq;
        case 44: return bid_specialist;
        case 45: return offer_specialist;
        case 46: return bid_offer_specialist;
        case 47: return end_of_day_sam;
        case 48: return forbidden_sam;
        case 49: return frozen_sam;
        case 50: return pre_opening_sam;
        case 51: return opening_sam;
        case 52: return open_sam;
        case 53: return surveillance_sam;
        case 54: return suspended_sam;
        case 55: return reserved_sam;
        case 56: return no_active_sam;
        case 57: return restricted;
        case 255: return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum QuoteCondition [E103]");
    }
};
}
}
}
#endif
