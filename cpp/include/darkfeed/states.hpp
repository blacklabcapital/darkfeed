#pragma once
#include <atomic>
#include <google/dense_hash_map>
#include "darkfeed/types/quotes.hpp"
#include "darkfeed/types/trades.hpp"
#include "darkfeed/types/halts.hpp"
#include "darkfeed/types/exchanges.hpp"
#include "darkfeed/types/quotes.hpp"
#include "darkfeed/types/timestamp.hpp"
#include "darkfeed/util/hashing.hpp"
#include "darkfeed/util/ring_allocator.hpp"
#include <boost/circular_buffer.hpp>

#define EQUITYSTATE_RING_SIZE 2 //only one simultaneous write operation

namespace darkfeed
{

typedef google::dense_hash_map<Exchange, size_t, XXExchangeHasher32, eqexg> ReportingExgIdxHT;


/// @brief holds the latest top of book (TOB) quotes for a given symbol for N reporting exchanges
/// @details uses one ring allocator per reporting exchange to hold memory while a new quote is staged.
/// then the relevant reporting exchange quote's pointer is atomically swapped with the staged quote's pointer
/// a copy and similar atomic pointer swap updates best_bid and best_ask if needed.
/// EquityTOBState requires a single writer thread but allows many reader threads.
class EquityTOBState {
    ReportingExgIdxHT exg_idx_ht;
    std::vector<RingAllocator<EquityQuote,4>> q_ring_vec; //holds ring allocators for each exchange
    std::vector<std::atomic<EquityQuote*>> quotes;
    std::atomic<const EquityQuote *> best_bid;
    std::atomic<const EquityQuote *> best_ask;
    std::atomic_uint_fast64_t q_vol;
    /// @brief Returns next memory slot from exchange's ring allocator
    /// @param e The reporting exchange for the quote
    /// @warning if e doesn't exist, memory will be allocated
    /// @return Pointer to the quote's memory slot
    EquityQuote* get_quote_ptr(mfeed::Exchange e);
 public:
    EquityTOBState();
    ~EquityTOBState();

    /// @brief retrieve current NBBO
    /// @return snapshot of best bid and ask. If either best_bid or best_ask aren't yet populated, will return an empty NBBO struct
    NBBO get_nbbo() const;
    /// @brief retrieve current best bid quote
    /// @return the best bid quote if set. Otherwise an empty quote.
    EquityQuote get_best_bid();
    /// @brief retrieve current best ask quote
    /// @return the best ask quote if set. Otherwise an empty quote.
    EquityQuote get_best_ask();
    /// @brief retrieve number of eligible quotes for this symbol today (thread-safe, lockfree)
    /// only quotes eligible to set the NBBO increment this value
    /// @return number of NBBO-setting quotes for the symbol
    std::uint32_t get_q_vol() const
    { return q_vol.load(std::memory_order_acquire); };
    /// @brief returns the current top of book quote at the given exchange
    /// @param e the exchange
    /// @return the quote. An empty (symbol root is "") quote will be returned if quote doesn't exist.
    EquityQuote get_quote(const Exchange &e) const;
    /// @brief Pushes a new quote to the tracker. Quote is expected to be of the correct symbol and allocated on the heap
    /// @param q The quote to push
    void push_quote(const EquityQuote *q);
    /// @brief releases underlying memory and resets lookup table
    void clear();
};

struct EquityTradeStateMeta {
    Price high;
    Price low;
    Price last;
};

/// @brief holds the latest trades and computed trade statistics for a given symbol
/// @note Threadsafe (and lockfree) for readers only. Only one producer is permitted.
class EquityTradeState {
    boost::circular_buffer<EquityTrade> trade_buf;
    boost::circular_buffer<Price> high_hist;
    boost::circular_buffer<Price> low_hist;
    boost::circular_buffer<Price> last_hist;
    std::atomic<EquityTradeStateMeta*> meta;
    RingAllocator<EquityTradeStateMeta,4> meta_ring;

 public:
    /// @brief Constructor for EquityTradeState
    /// @param buf_cap Most recent # of trades to store in buffer for corrections
    /// @param range_cap Most recent # of high/low/last
    EquityTradeState(size_t buf_cap = 100, size_t range_cap = 100);
};
} //darkfeed
