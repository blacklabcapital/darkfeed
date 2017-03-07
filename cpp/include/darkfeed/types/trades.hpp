#pragma once

#include <flatbuffers/flatbuffers.h>
#include "darkfeed/types/exchanges.hpp"
#include "darkfeed/types/timestamp.hpp"
#include "darkfeed/types/event.hpp"
#include "darkfeed/types/price.hpp"
#include "darkfeed/generated/flatbuffers/trade_conditions_generated.h"

namespace darkfeed
{

typedef schemas::fb::TradeCondition TradeCondition;

/// @brief Base struct describes a trade/execution for a generic instrument
struct Trade : Event {
    TradeCondition condition = TradeCondition::none; ///< The condition under which the trade was made
    Price price;             ///< trade price
    std::uint32_t size = 0;  ///< trade size (units depend on type of trade)
    std::uint32_t vol = 0;   ///< total volume traded as of this trade
    std::uint32_t t_vol = 0; ///< total trades for this symbol in this trading session as of this trade

    /// @brief Returns trade condition as a string
    /// @note We return a const char* to prevent redundant string creation
    /// @return trade condition text
    const char *condition_str() const;

    /// @brief Checks if the trade is eligible to set the last price
    /// @return True if trade is eligible to set last price. False otherwise
    bool sets_last() const;

    /// @brief Checks if the trade is eligible to increment the volume
    /// @return True if the trade is eligible to increment the volume. False otherwise.
    bool sets_vol() const;

    /// @brief Checks if the trade is eligible to set the high price
    /// @return True if the trade is eligible to set the high price. False otherwise
    bool sets_high() const;

    /// @brief Checks if the trade is eligible to set the low price
    /// @return True if the trade is eligible to set the low price. False otherwise
    bool sets_low() const;
};

/// @brief Describes a trade/execution for an equity
struct EquityTrade : Trade {
    /// @brief Serializes a trade to a flatbuffer encoded buffer
    /// @return std::pair containing a smart pointer to the buffer and its size in bytes
    std::pair<flatbuffers::unique_ptr_t, std::size_t> serialize() const;

    /// @brief Deserializes a trade from a flatbuffer encoded buffer
    /// @return True if deserialization was successful. False otherwise.
    bool deserialize(const char *, std::size_t);
};

/// @brief Describes a trade/execution for an option
struct OptionTrade : Trade {
    Price strike;             ///< strike price of underlying option
    Timestamp expiration;     ///< expiration date of underlying option

    /// @brief Serializes a trade to a flatbuffer encoded buffer
    /// @return std::pair containing a smart pointer to the buffer and its size in bytes
    std::pair<flatbuffers::unique_ptr_t, std::size_t> serialize() const;

    /// @brief Deserializes a trade from a flatbuffer encoded buffer
    /// @return True if deserialization was successful. False otherwise.
    bool deserialize(const char *, std::size_t);
};
}
