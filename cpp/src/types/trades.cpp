#include "darkfeed/types/trades.hpp"
#include "darkfeed/generated/flatbuffers/trade_generated.h"

namespace darkfeed
{
const char *Trade::condition_str() const
{
    return schemas::fb::EnumNameTradeCondition(condition);
}

bool Trade::sets_last() const
{
    bool last = false;
    switch (condition)
    {
    case darkfeed::TradeCondition::regular:last = true;
        break;
    case darkfeed::TradeCondition::opening_detail:last = true;
        break;
    case darkfeed::TradeCondition::bunched:last = true;
        break;
    case darkfeed::TradeCondition::rule_127:last = true;
        break;
    case darkfeed::TradeCondition::auto_exec:last = true;
        break;
    case darkfeed::TradeCondition::reopen:last = true;
        break;
    case darkfeed::TradeCondition::acquisition:last = true;
        break;
    case darkfeed::TradeCondition::cash:last = true;
        break;
    case darkfeed::TradeCondition::next_day_market:last = true;
        break;
    case darkfeed::TradeCondition::burst_basket:last = true;
        break;
    case darkfeed::TradeCondition::rule_155:last = true;
        break;
    case darkfeed::TradeCondition::distribution:last = true;
        break;
    case darkfeed::TradeCondition::split:last = true;
        break;
    case darkfeed::TradeCondition::adjusted:last = true;
        break;
    case darkfeed::TradeCondition::spread:last = true;
        break;
    case darkfeed::TradeCondition::straddle:last = true;
        break;
    case darkfeed::TradeCondition::combo:last = true;
        break;
    case darkfeed::TradeCondition::stopped:last = true;
        break;
    case darkfeed::TradeCondition::crossed:last = true;
        break;
    case darkfeed::TradeCondition::fast_market:last = true;
        break;
    case darkfeed::TradeCondition::stopped_sold_last:last = true;
        break;
    default:break;
    }
    return last;
}

bool Trade::sets_high() const
{
    bool high = false;
    switch (condition)
    {
    case TradeCondition::regular:high = true;
        break;
    case TradeCondition::sold:high = true;
        break;
    case TradeCondition::opened:high = true;
        break;
    case TradeCondition::opening_price:high = true;
        break;
    case TradeCondition::opening_detail:high = true;
        break;
    case TradeCondition::closing:high=true;
        break;
    case TradeCondition::bunched:high = true;
        break;
    case TradeCondition::sold_last:high = true;
        break;
    case TradeCondition::rule_127:high = true;
        break;
    case TradeCondition::auto_exec:high = true;
        break;
    case TradeCondition::reopen:high = true;
        break;
    case TradeCondition::acquisition:high = true;
        break;
    case TradeCondition::cash:high = true;
        break;
    case TradeCondition::next_day_market:high = true;
        break;
    case TradeCondition::burst_basket:high = true;
        break;
    case TradeCondition::rule_155:high = true;
        break;
    case TradeCondition::distribution:high = true;
        break;
    case TradeCondition::split:high = true;
        break;
    case TradeCondition::spread:high = true;
        break;
    case TradeCondition::straddle:high = true;
        break;
    case TradeCondition::combo:high = true;
        break;
    case TradeCondition::stopped:high = true;
        break;
    case TradeCondition::crossed:high = true;
        break;
    case TradeCondition::fast_market:high = true;
        break;
    case TradeCondition::stopped_sold_last:high = true;
        break;
    case TradeCondition::stopped_out_of_seq:high = true;
        break;
    case TradeCondition::iso:high=true;
        break;
    default:break;
    }
    return high;
}

bool Trade::sets_low() const
{
    bool low = false;
    switch (condition)
    {
    case TradeCondition::regular:low = true;
        break;
    case TradeCondition::sold:low = true;
        break;
    case TradeCondition::opened:low = true;
        break;
    case TradeCondition::opening_price:low = true;
        break;
    case TradeCondition::opening_detail:low = true;
        break;
    case TradeCondition::closing:low = true;
        break;
    case TradeCondition::bunched:low = true;
        break;
    case TradeCondition::sold_last:low = true;
        break;
    case TradeCondition::rule_127:low = true;
        break;
    case TradeCondition::auto_exec:low = true;
        break;
    case TradeCondition::reopen:low = true;
        break;
    case TradeCondition::acquisition:low = true;
        break;
    case TradeCondition::cash:low = true;
        break;
    case TradeCondition::next_day_market:low = true;
        break;
    case TradeCondition::burst_basket:low = true;
        break;
    case TradeCondition::rule_155:low = true;
        break;
    case TradeCondition::distribution:low = true;
        break;
    case TradeCondition::split:low = true;
        break;
    case TradeCondition::spread:low = true;
        break;
    case TradeCondition::straddle:low = true;
        break;
    case TradeCondition::combo:low = true;
        break;
    case TradeCondition::stopped:low = true;
        break;
    case TradeCondition::crossed:low = true;
        break;
    case TradeCondition::fast_market:low = true;
        break;
    case TradeCondition::stopped_sold_last:low = true;
        break;
    case TradeCondition::stopped_out_of_seq:low = true;
        break;
    case TradeCondition::iso:low=true;
        break;
    default:break;
    }
    return low;
}

bool Trade::sets_vol() const
{
    // more conditions than not set the volume
    bool vol = true;
    switch (condition)
    {
    case TradeCondition::opening_detail:vol = false;
        break;
    case TradeCondition::cancel:vol = false;
        break;
    case TradeCondition::cancel_last:vol = false;
        break;
    case TradeCondition::cancel_only:vol = false;
        break;
    case TradeCondition::cancel_stopped:vol = false;
        break;
    case TradeCondition::none:vol = false;
        break;
    case TradeCondition::closing:vol = false;
        break;
    case TradeCondition::stopped_sold_last:vol = false;
        break;
    case TradeCondition::stopped_out_of_seq:vol = false;
        break;
    case TradeCondition::opening_price:vol = false;
        break;
    default:break;
    }
    return vol;
}
} // darkfeed