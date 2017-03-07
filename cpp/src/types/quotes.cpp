
#include "darkfeed/types/quotes.hpp"
#include "darkfeed/generated/flatbuffers/quote_generated.h"
#include "darkfeed/generated/flatbuffers/nbbo_generated.h"

namespace darkfeed
{
const char* Quote::condition_str() const
{
    return schemas::fb::EnumNameQuoteCondition(condition);
}

bool Quote::sets_nbbo() const
{
    bool sets = false;
    switch (condition)
    {
    case QuoteCondition::regular:sets = true;
        break;
    case QuoteCondition::auto_exec:sets = true;
        break;
    case QuoteCondition::bid_specialist:sets = true;
        break;
    case QuoteCondition::offer_specialist:sets = true;
        break;
    case QuoteCondition::bid_offer_specialist:sets = true;
        break;
    case QuoteCondition::locked:sets = true;
        break;
    case QuoteCondition::depth_on_bid:sets = true;
        break;
    case QuoteCondition::depth_on_offer:sets = true;
        break;
    case QuoteCondition::depth_on_bid_offer:sets = true;
        break;
    case QuoteCondition::crossed:sets = true;
        break;
    case QuoteCondition::inactive:sets = true;
        break;
    default:break;
    }
    return sets;
}

const char* NBBO::best_bid_condition_str() const
{
    return schemas::fb::EnumNameQuoteCondition(best_bid_condition);
}

const char* NBBO::best_ask_condition_str() const
{
    return schemas::fb::EnumNameQuoteCondition(best_ask_condition);
}
} // darkfeed
