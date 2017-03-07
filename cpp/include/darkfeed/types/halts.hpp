#pragma once
#include "darkfeed/types/event.hpp"
#include "darkfeed/generated/flatbuffers/halt_generated.h"

namespace darkfeed
{
/// @defgroup halts
/// @brief Halt events sent by an exchange
/// @ingroup events

/// @brief Defines the halt code
/// @ingroup halts
typedef schemas::fb::HaltType HaltType;
/// @brief Defines the halt state of the security
/// @ingroup halts
typedef schemas::fb::HaltStatus HaltStatus;


/// @brief Describes a halt event for a security
/// @ingroup halts
struct Halt : Event {
    HaltType halt_type; ///< The halt code issued for this event
    HaltStatus halt_status; ///< The current halt status of the security

    /// @brief fetches halt type as string
    /// @return halt type in text form
    const char *halt_type_str() const;
    /// @brief fetches halt status as string
    /// @return halt status in text form
    const char *halt_status_str() const;
};
}
