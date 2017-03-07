#include "darkfeed/types/halts.hpp"

namespace darkfeed
{

const char* Halt::halt_type_str() const
{
    return schemas::fb::EnumNameHaltType(halt_type);
}

const char* Halt::halt_status_str() const
{
    return schemas::fb::EnumNameHaltStatus(halt_status);
}
} //darkfeed
