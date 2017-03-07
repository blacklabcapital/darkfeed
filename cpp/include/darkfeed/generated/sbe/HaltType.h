/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _DARKFEED_SCHEMAS_SBE_HALTTYPE_H_
#define _DARKFEED_SCHEMAS_SBE_HALTTYPE_H_

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

class HaltType {
 public:

    enum Value {
        none = (std::uint8_t) 0,
        news = (std::uint8_t) 1,
        news_disseminated = (std::uint8_t) 2,
        order_imbalance = (std::uint8_t) 3,
        equipment_change = (std::uint8_t) 4,
        pending_info = (std::uint8_t) 5,
        suspended = (std::uint8_t) 6,
        sec = (std::uint8_t) 7,
        not_specified = (std::uint8_t) 8,
        luld_pause = (std::uint8_t) 9,
        marketwide_halt_level1 = (std::uint8_t) 10,
        marketwide_halt_level2 = (std::uint8_t) 11,
        marketwide_halt_level3 = (std::uint8_t) 12,
        marketwide_halt_resume = (std::uint8_t) 13,
        luld_straddle = (std::uint8_t) 14,
        extraordinary_market_activity = (std::uint8_t) 15,
        etf = (std::uint8_t) 16,
        non_compliance = (std::uint8_t) 17,
        filings_not_current = (std::uint8_t) 18,
        operations = (std::uint8_t) 19,
        ipo_pending = (std::uint8_t) 20,
        corporate_action = (std::uint8_t) 21,
        quote_unavailable = (std::uint8_t) 22,
        single_stock_pause = (std::uint8_t) 23,
        single_stock_pause_resume = (std::uint8_t) 24,
        NULL_VALUE = (std::uint8_t) 255
    };

    static HaltType::Value get(const std::uint8_t value)
    {
        switch (value)
        {
        case 0: return none;
        case 1: return news;
        case 2: return news_disseminated;
        case 3: return order_imbalance;
        case 4: return equipment_change;
        case 5: return pending_info;
        case 6: return suspended;
        case 7: return sec;
        case 8: return not_specified;
        case 9: return luld_pause;
        case 10: return marketwide_halt_level1;
        case 11: return marketwide_halt_level2;
        case 12: return marketwide_halt_level3;
        case 13: return marketwide_halt_resume;
        case 14: return luld_straddle;
        case 15: return extraordinary_market_activity;
        case 16: return etf;
        case 17: return non_compliance;
        case 18: return filings_not_current;
        case 19: return operations;
        case 20: return ipo_pending;
        case 21: return corporate_action;
        case 22: return quote_unavailable;
        case 23: return single_stock_pause;
        case 24: return single_stock_pause_resume;
        case 255: return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum HaltType [E103]");
    }
};
}
}
}
#endif
