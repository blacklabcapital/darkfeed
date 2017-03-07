#pragma once

#include <iostream>
#include <fstream>
#include <atomic>
#include <google/dense_hash_map>
#include "darkfeed/types/quotes.hpp"
#include "darkfeed/types/trades.hpp"
#include "darkfeed/types/exchanges.hpp"
#include "darkfeed/types/quotes.hpp"
#include "darkfeed/types/timestamp.hpp"
#include "darkfeed/util/hashing.hpp"
#include "states.hpp"
#include "darkfeed/types/symbol.hpp"

namespace darkfeed
{
typedef google::dense_hash_map<Symbol, EquityTOBState, XXSymHasher32, eqsym> QuoteStateHT;


///@brief Engine for processing real-time top of book quotes
class EquityQuoteTracker {
 protected:
    QuoteStateHT states; ///< hash table of equities keyed on symbol

 public:
    EquityQuoteTracker();
    ~EquityQuoteTracker() {clear();};

    /// @brief retrieve symbols currently registered
    /// @return vector of symbols currently registered
    const std::vector<Symbol> get_symbols() const;

    /// @brief get NBBO for a given symbol
    /// @param s the symbol
    /// @return the NBBO, otherwise an empty NBBO quote if best quote doesn't yet exist
    NBBO get_nbbo(const Symbol &s) const;

    /// @brief get best bid quote for a given symbol
    /// @param s the symbol
    /// @return the best bid quote, otherwise an empty quote if not found
    EquityQuote get_best_bid(const Symbol& s);

    /// @brief get best ask quote for a given symbol
    /// @param s the symbol
    /// @return the best ask quote, otherwise an empty quote if not found
    EquityQuote get_best_ask(const Symbol& s);

    /// @brief Fetches latest top of book quote for given symbol
    /// @param s the symbol to lookup the quote for
    /// @param e the reporting exchange for the quote
    /// @return The matching quote if found. If not, it will be empty
    EquityQuote get_quote(const Symbol& s, const Exchange& e);

    /// @brief Pushes a quote to the tracker.
    /// @param q The pointer to the quote to push. Must be heap-allocated.
    void push_quote(const EquityQuote* q);

    /// @brief Fetches the number of quotes in the current session eligible to set NBBO for a given symbol
    /// @param s The symbol to fetch q_vol for
    std::uint32_t get_q_vol(const Symbol& s) const;

    /// @brief resets the tracker to an empty state (useful for EOD rollover)
    void clear();
};

/// @brief Engine for processing time and sales data
class EquityTradeTracker {

};

class HaltTracker {

};
}
