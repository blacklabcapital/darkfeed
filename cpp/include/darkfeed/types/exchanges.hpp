#pragma once
#include <string>
#include "darkfeed/generated/flatbuffers/exchanges_generated.h"

namespace darkfeed
{

typedef schemas::fb::MIC MIC;

inline const char **EnumNamesExgName()
{
    static const char *names[] = {"NONE", "NASDAQ", "NYSE", "AMEX", "CBOE", "ARCA", "NSX", "PHLX", "OPRA", "BEX",
                                  "NASDAQ", "NASDAQ", "BATS", "BATY", "DRCTEDGE", "EDGX", "CHX", "PINK", "EDGEA",
                                  "SMART", "ISLAND", "IEX", nullptr}; //common names
    return names;
}

inline const char *EnumNameExgName(MIC e)
{ return EnumNamesExgName()[static_cast<int>(e)]; }


/// @brief Represents a stock exchange or ECN
struct Exchange {
    MIC mic;  ///< the ISO 10383 Market Identifier Code

 public:
    Exchange();                              ///< default constructor
    Exchange(const MIC m);          ///< constructor with parsed MIC
    Exchange(const std::string &);  ///< constructor using raw MIC or exchange abbreviation

    // comparison operators
    bool operator==(const Exchange &e) const
    { return e.mic == mic; }

    bool operator!=(const Exchange &e) const
    { return e.mic != mic; }

    /// @brief Get String ISO 10383 MIC
    /// @return ISO 10383 MIC corresponding to exchange.
    std::string mic_str() const;
    /// @brief Get Broker Compatible (Currently IB) Exchange Abbreviation
    /// @return
    std::string abbrev_str() const;
};

}  // darkfeed
