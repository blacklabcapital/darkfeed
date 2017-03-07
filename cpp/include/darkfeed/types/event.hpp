#pragma once 
#include <flatbuffers/flatbuffers.h>
#include "darkfeed/generated/flatbuffers/securities_generated.h"
#include "exchanges.hpp"
#include "timestamp.hpp"
#include "symbol.hpp"
namespace darkfeed
{
/// @addtogroup types

/// @defgroup events
/// @brief Market events sent by an exchange or information processor
/// @ingroup types

/// @brief Denotes the type of market event
/// @ingroup events
enum class EventType {
    EquityQuote = 1,
    OptionQuote = 2,
    Halt = 3,
    EquityTrade = 4,
    EquityNBBO = 5,
};

/// @brief Denotes a piece of market data
/// @ingroup events
struct Event {
    Symbol symbol; ///< The symbol data for the event
    Exchange reporting_exg; ///< The exchange reporting the event
    Timestamp ts; ///< The high resolution timestamp corresponding to the event. Currently derived from exchange
    std::uint64_t seq_num = 0; ///< A sequence number guaranteed to be monotonically increasing for a given feed of events
};
}
