#include <climits>
#include "../include/mfeed/states.hpp"

namespace darkfeed
{

EquityTOBState::EquityTOBState()
{
    exg_idx_ht.set_deleted_key(darkfeed::MIC::SMART);
    exg_idx_ht.set_empty_key(darkfeed::MIC::NONE);
}

EquityTOBState::~EquityTOBState()
{
    clear();
}

void EquityTOBState::push_quote(const EquityQuote *q)
{
    //flags for different NBBO scenarios
    bool is_only_quote = false; //only quote means it's NBBO
    bool flushes_best_bid = false; //quote is from best bid exchange and is inferior
    bool flushes_best_ask = false; //quote is from best ask exchange and is inferior
    bool set_best_bid = false; //we set the best bid
    bool set_best_ask = false; //we set the best ask

    //can this quote set top of book?
    if (!q->sets_nbbo())
        return;

    //do we already have an entry in the reporting exchange lookup table?
    auto lookup_it = exg_idx_ht.find(q->reporting_exg);
    if (lookup_it == exg_idx_ht.end()) //not found
    {
        exg_idx_ht[q->reporting_exg] = quotes.size();
        if (!quotes.size())
            is_only_quote = true;

        quotes.push_back(std::atomic<const EquityQuote *>(q));
    }
    else  //found
    {
        auto best_bid_ptr = best_bid.load(std::memory_order_acquire);
        if (best_bid_ptr != nullptr)
        {
            if (q->reporting_exg == best_bid_ptr->reporting_exg
                && (q->bid.as<double>() > best_bid_ptr->bid.as<double>()))
                flushes_best_bid = true;
        }
        auto best_ask_ptr = best_ask.load(std::memory_order_acquire);
        if (best_bid_ptr != nullptr)
        {
            if (q->reporting_exg == best_ask_ptr->reporting_exg
                && (q->ask.as<double>() < best_ask_ptr->ask.as<double>()))
                flushes_best_ask = true;
        }
        quotes[lookup_it->second].store(q, std::memory_order_release);
    }

    //If this is our only reporting exchange, then obviously it is the NBBO
    if (is_only_quote)
    {
        best_bid.store(q);
        set_best_bid = true;
        best_ask.store(q);
        set_best_ask = true;
        return;
    }

    //If this quote flushes the best bid quote or we don't have one, we need to scan for the best bid
    if (flushes_best_bid || best_bid.load(std::memory_order_acquire) == nullptr)
    {
        double best_bid_price = -1.0;
        const EquityQuote *bbq = nullptr;
        for (const auto &abq: quotes)
        {
            auto bq = abq.load(std::memory_order_acquire);
            if (bq->bid.as<double>() > best_bid_price)
            {
                best_bid_price = bq->bid.as<double>();
                bbq = bq;
            }
        }
        best_bid.store(bbq, std::memory_order_release);
        set_best_bid = true;
    }

    //If this quote flushes the best ask quote or we don't have one, we need to scan for the best ask
    if (flushes_best_ask || best_ask.load(std::memory_order_acquire) == nullptr)
    {
        double best_ask_price = UINT32_MAX;
        const EquityQuote *baq = nullptr;
        for (const auto &aaq: quotes)
        {
            auto aq = aaq.load(std::memory_order_acquire);
            if (aq->ask.as<double>() < best_ask_price)
            {
                best_ask_price = aq->ask.as<double>();
                baq = aq;
            }
        }
        best_ask.store(baq, std::memory_order_release);
        set_best_ask = true;
    }

    if (!set_best_bid && q->bid.as<double>() > best_bid.load(std::memory_order_acquire)->bid.as<double>())
        best_bid.store(q, std::memory_order_release);

    if (!set_best_ask && q->ask.as<double>() < best_ask.load(std::memory_order_acquire)->ask.as<double>())
        best_ask.store(q, std::memory_order_release);
}

EquityQuote EquityTOBState::get_quote(const Exchange &e) const
{
    //check if the exchange exists
    auto idx_it = exg_idx_ht.find(e);
    if (idx_it == exg_idx_ht.end())
        return EquityQuote{};
    return *quotes[idx_it->second].load(std::memory_order_acquire);
}

NBBO EquityTOBState::get_nbbo() const
{
    NBBO n;
    n.reporting_exg == darkfeed::MIC::SIP;
    auto bbq = best_bid.load(std::memory_order_acquire);
    auto baq = best_ask.load(std::memory_order_acquire);
    n.best_bid = bbq->bid;
    n.best_ask = bbq->ask;
    n.best_bid_exg = bbq->reporting_exg;
    n.best_ask_exg = baq->reporting_exg;
    n.best_bid_condition = bbq->condition;
    n.best_ask_condition = baq->condition;
    n.best_bid_size = bbq->bid_size;
    n.best_ask_size = baq->ask_size;
    n.symbol = bbq->symbol;
    n.ts.now();
    return n;
}

EquityQuote EquityTOBState::get_best_bid()
{
    auto bbq = best_bid.load(std::memory_order_acquire);
    if (bbq == nullptr)
        return EquityQuote();
    return *bbq;
}

EquityQuote EquityTOBState::get_best_ask()
{
    auto baq = best_ask.load(std::memory_order_acquire);
    if (baq == nullptr)
        return EquityQuote();
    return *baq;
}

void EquityTOBState::clear()
{
    auto bbq = best_bid.load();
    auto baq = best_ask.load();
    bool found_bbq = false; //used to prevent double-free
    bool found_baq = false; //used to prevent double-free

    for (auto aq: quotes)
    {
        auto q_ptr = aq.load();
        if (q_ptr == bbq)
            found_bbq = true;
        if (q_ptr == baq)
            found_baq = true;
        delete q_ptr;
    }
    if (!found_bbq && bbq != nullptr)
        delete bbq;
    if (!found_baq && baq != nullptr)
        delete baq;
    exg_idx_ht.clear();
}

}  // darkfeed
