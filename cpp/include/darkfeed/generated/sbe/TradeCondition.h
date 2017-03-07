/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _DARKFEED_SCHEMAS_SBE_TRADECONDITION_H_
#define _DARKFEED_SCHEMAS_SBE_TRADECONDITION_H_

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

class TradeCondition {
 public:

    enum Value {
        none = (std::uint8_t) 0,
        regular = (std::uint8_t) 1,
        cash = (std::uint8_t) 2,
        avg_price = (std::uint8_t) 3,
        cash_trade = (std::uint8_t) 4,
        next_day_market = (std::uint8_t) 5,
        opening_detail = (std::uint8_t) 6,
        intraday_detail = (std::uint8_t) 7,
        rule_127 = (std::uint8_t) 8,
        rule_155 = (std::uint8_t) 9,
        sold_last = (std::uint8_t) 10,
        next_day = (std::uint8_t) 11,
        opened = (std::uint8_t) 12,
        seller = (std::uint8_t) 13,
        sold = (std::uint8_t) 14,
        stopped_stock = (std::uint8_t) 15,
        imbalance_more_buyers = (std::uint8_t) 16,
        imbalance_more_sellers = (std::uint8_t) 17,
        opening_price = (std::uint8_t) 18,
        manual = (std::uint8_t) 19,
        iso = (std::uint8_t) 20,
        bargain_condition = (std::uint8_t) 21,
        converted_price_indicator = (std::uint8_t) 22,
        exchange_last = (std::uint8_t) 23,
        final_price = (std::uint8_t) 24,
        ex_pit = (std::uint8_t) 25,
        crossed = (std::uint8_t) 26,
        cancel = (std::uint8_t) 27,
        volume_only = (std::uint8_t) 28,
        direct_plus = (std::uint8_t) 29,
        acquisition = (std::uint8_t) 30,
        bunched = (std::uint8_t) 31,
        distribution = (std::uint8_t) 32,
        bunched_sale = (std::uint8_t) 33,
        split = (std::uint8_t) 34,
        cancel_stopped = (std::uint8_t) 35,
        cancel_eth = (std::uint8_t) 36,
        cancel_stopped_eth = (std::uint8_t) 37,
        out_of_seq_eth = (std::uint8_t) 38,
        cancel_last_eth = (std::uint8_t) 39,
        sold_last_eth = (std::uint8_t) 40,
        cancel_last = (std::uint8_t) 41,
        sold_last_sale = (std::uint8_t) 42,
        cancel_open = (std::uint8_t) 43,
        cancel_open_eth = (std::uint8_t) 44,
        opened_sale_eth = (std::uint8_t) 45,
        cancel_only = (std::uint8_t) 46,
        cancel_only_eth = (std::uint8_t) 47,
        late_open_eth = (std::uint8_t) 48,
        auto_exec_eth = (std::uint8_t) 49,
        reopen = (std::uint8_t) 50,
        reopen_eth = (std::uint8_t) 51,
        adjusted = (std::uint8_t) 52,
        adjusted_eth = (std::uint8_t) 53,
        spread = (std::uint8_t) 54,
        spread_eth = (std::uint8_t) 55,
        straddle = (std::uint8_t) 56,
        straddle_eth = (std::uint8_t) 57,
        stopped = (std::uint8_t) 58,
        stopped_eth = (std::uint8_t) 59,
        regular_eth = (std::uint8_t) 60,
        combo = (std::uint8_t) 61,
        combo_eth = (std::uint8_t) 62,
        closing = (std::uint8_t) 63,
        prior_ref = (std::uint8_t) 64,
        stopped_sold_last = (std::uint8_t) 65,
        stopped_out_of_seq = (std::uint8_t) 66,
        fast_market = (std::uint8_t) 67,
        auto_exec = (std::uint8_t) 68,
        form_t = (std::uint8_t) 69,
        basket_idx = (std::uint8_t) 70,
        burst_basket = (std::uint8_t) 71,
        NULL_VALUE = (std::uint8_t) 255
    };

    static TradeCondition::Value get(const std::uint8_t value)
    {
        switch (value)
        {
        case 0: return none;
        case 1: return regular;
        case 2: return cash;
        case 3: return avg_price;
        case 4: return cash_trade;
        case 5: return next_day_market;
        case 6: return opening_detail;
        case 7: return intraday_detail;
        case 8: return rule_127;
        case 9: return rule_155;
        case 10: return sold_last;
        case 11: return next_day;
        case 12: return opened;
        case 13: return seller;
        case 14: return sold;
        case 15: return stopped_stock;
        case 16: return imbalance_more_buyers;
        case 17: return imbalance_more_sellers;
        case 18: return opening_price;
        case 19: return manual;
        case 20: return iso;
        case 21: return bargain_condition;
        case 22: return converted_price_indicator;
        case 23: return exchange_last;
        case 24: return final_price;
        case 25: return ex_pit;
        case 26: return crossed;
        case 27: return cancel;
        case 28: return volume_only;
        case 29: return direct_plus;
        case 30: return acquisition;
        case 31: return bunched;
        case 32: return distribution;
        case 33: return bunched_sale;
        case 34: return split;
        case 35: return cancel_stopped;
        case 36: return cancel_eth;
        case 37: return cancel_stopped_eth;
        case 38: return out_of_seq_eth;
        case 39: return cancel_last_eth;
        case 40: return sold_last_eth;
        case 41: return cancel_last;
        case 42: return sold_last_sale;
        case 43: return cancel_open;
        case 44: return cancel_open_eth;
        case 45: return opened_sale_eth;
        case 46: return cancel_only;
        case 47: return cancel_only_eth;
        case 48: return late_open_eth;
        case 49: return auto_exec_eth;
        case 50: return reopen;
        case 51: return reopen_eth;
        case 52: return adjusted;
        case 53: return adjusted_eth;
        case 54: return spread;
        case 55: return spread_eth;
        case 56: return straddle;
        case 57: return straddle_eth;
        case 58: return stopped;
        case 59: return stopped_eth;
        case 60: return regular_eth;
        case 61: return combo;
        case 62: return combo_eth;
        case 63: return closing;
        case 64: return prior_ref;
        case 65: return stopped_sold_last;
        case 66: return stopped_out_of_seq;
        case 67: return fast_market;
        case 68: return auto_exec;
        case 69: return form_t;
        case 70: return basket_idx;
        case 71: return burst_basket;
        case 255: return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum TradeCondition [E103]");
    }
};
}
}
}
#endif
