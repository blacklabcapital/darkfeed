#include <algorithm>
#include "../include/mfeed/state_utils.hpp"

namespace darkfeed
{
    EquityQuoteTracker::EquityQuoteTracker()
    {
        Symbol ds;
        std::strcpy(ds.root,"DELETED");
        ds.listing_exg = MIC::NONE;
        states.set_deleted_key(ds);
        states.set_empty_key(Symbol{});
    }

    void EquityQuoteTracker::clear()
    {
        for(const auto& it: states)
        {
            it.second.clear();
        }
        states.clear();
    }

    const std::vector<Symbol> EquityQuoteTracker::get_symbols() const
    {
        std::vector<Symbol> symbols;
        for(const auto& it : states)
        {
           symbols.push_back(it.first);
        }
        return symbols;
    }

    NBBO EquityQuoteTracker::get_nbbo(const Symbol &s) const
    {
        auto it = states.find(s);
        if (it == states.end())
            return NBBO();
        return it->second.get_nbbo();
    }

    EquityQuote EquityQuoteTracker::get_best_bid(const Symbol &s)
    {
        auto it = states.find(s);
        if (it == states.end())
            return EquityQuote();
        return it->second.get_best_bid();
    }

    EquityQuote EquityQuoteTracker::get_best_ask(const Symbol &s)
    {
        auto it = states.find(s);
        if (it == states.end())
            return EquityQuote();
        return it->second.get_best_ask();
    }

    EquityQuote EquityQuoteTracker::get_quote(const Symbol& s, const Exchange& e)
    {
        auto it = states.find(s);
        if (it == states.end())
            return EquityQuote();
        return it->second.get_quote(e);
    }

    void EquityQuoteTracker::push_quote(const EquityQuote *q)
    {
        //check if symbol already exists
        EquityTOBState* s_ptr = nullptr;
        auto it = states.find(q->symbol);
        if (it == states.end())
        {
            states[q->symbol] = EquityTOBState();
            s_ptr = &states[q->symbol];
        }
        else
            s_ptr = &it->second;
        s_ptr->push_quote(q);
    }

    std::uint32_t EquityQuoteTracker::get_q_vol(const Symbol &s) const
    {
        auto it = states.find(s);
        if (it == states.end())
            return 0;
        return it->second.get_q_vol();
    }
}  // darkfeed
