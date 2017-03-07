#pragma once
#include "darkfeed/types/exchanges.hpp"
#include "darkfeed/generated/flatbuffers/symbol_generated.h"

#define DARKFEED_ROOT_SYMBOL_SIZE 8 //size in bytes of largest root symbol (closest power of 2)

namespace darkfeed
{
typedef schemas::fb::IssueType IssueType;


/// @brief Represents a uniquely identifiable security in a broken-out format
/// @ingroup types
struct Symbol {
    char root[DARKFEED_ROOT_SYMBOL_SIZE]; ///< The root symbol as listed on the primary exchange
    Exchange listing_exg; ///< The primary listing exchange for the symbol
    char series; ///< If symbol represents multi-series issue, the series identifier. Otherwise \0
    IssueType issue_type; ///< The type of issue this security represents

    /// @brief Default constructor
    /// @return
    Symbol();

    /// @brief Full constructor using C++ string for root symbol
    /// @param r root symbol (0-8 characters) all uppercase
    /// @param le listing exchange of the symbol
    /// @param s series of the symbol. '\0' if no series
    /// @param t type of symbol. SymbolType::normal in most cases
    /// @return
    Symbol(const char *r, const Exchange &le, const char s = '\0', const IssueType t = IssueType::normal);

    /// @brief Parse symbol from CTA/CQS style symbol
    /// if symbol cannot be parsed, an empty symbol is returned
    /// @param le The listing exchange of the symbol
    /// @param s CTA/CQS style symbol (eg; BRKB.PR.A)
    /// @return
    Symbol(const Exchange &le, const char *s);

    std::string issuetype_str() const;

    /// @brief coerce symbol into std::string
    /// @return formatted symbol
    std::string format() const;

    /// @brief Checks if two symbols are equivalent
    /// @param b The symbol to compare to
    /// @return true if the symbols are equal. false otherwise
    bool operator==(const Symbol &b) const;
};


IssueType str_to_issue_type(const char *str);
}
