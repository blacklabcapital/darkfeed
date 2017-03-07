/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _DARKFEED_SCHEMAS_SBE_OPTIONTYPE_H_
#define _DARKFEED_SCHEMAS_SBE_OPTIONTYPE_H_

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

class OptionType {
 public:

    enum Value {
        put = (std::uint8_t) 0,
        call = (std::uint8_t) 1,
        NULL_VALUE = (std::uint8_t) 255
    };

    static OptionType::Value get(const std::uint8_t value)
    {
        switch (value)
        {
        case 0: return put;
        case 1: return call;
        case 255: return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum OptionType [E103]");
    }
};
}
}
}
#endif
