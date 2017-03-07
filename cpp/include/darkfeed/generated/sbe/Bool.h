/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _DARKFEED_SCHEMAS_SBE_BOOL_H_
#define _DARKFEED_SCHEMAS_SBE_BOOL_H_

#if defined(SBE_HAVE_CMATH)
/* cmath needed for std::numeric_limits<double>::quiet_NaN() */
#  include <cmath>
#  define SBE_FLOAT_NAN std::numeric_limits<float>::quiet_NaN()
#  define SBE_DOUBLE_NAN std::numeric_limits<double>::quiet_NaN()
#else
/* math.h needed for NAN */
#  include <math.h>
#  define SBE_FLOAT_NAN NAN
#  define SBE_DOUBLE_NAN NAN
#endif

#if __cplusplus >= 201103L
#  include <cstdint>
#  include <string>
#  include <cstring>
#endif

#if __cplusplus >= 201103L
#  define SBE_CONSTEXPR constexpr
#else
#  define SBE_CONSTEXPR
#endif

#include <sbe/sbe.h>

using namespace sbe;

namespace darkfeed
{
namespace schemas
{
namespace sbe
{

class Bool {
 public:

    enum Value {
        FALSE = (std::uint8_t) 0,
        TRUE = (std::uint8_t) 1,
        NULL_VALUE = (std::uint8_t) 255
    };

    static Bool::Value get(const std::uint8_t value)
    {
        switch (value)
        {
        case 0: return FALSE;
        case 1: return TRUE;
        case 255: return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum Bool [E103]");
    }
};
}
}
}
#endif
