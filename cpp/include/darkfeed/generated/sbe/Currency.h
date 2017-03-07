/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _DARKFEED_SCHEMAS_SBE_CURRENCY_H_
#define _DARKFEED_SCHEMAS_SBE_CURRENCY_H_

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

class Currency {
 public:

    enum Value {
        USD = (std::uint8_t) 0,
        AUD = (std::uint8_t) 1,
        CAD = (std::uint8_t) 2,
        CHF = (std::uint8_t) 3,
        EUR = (std::uint8_t) 4,
        GBP = (std::uint8_t) 5,
        HKD = (std::uint8_t) 6,
        JPY = (std::uint8_t) 7,
        NULL_VALUE = (std::uint8_t) 255
    };

    static Currency::Value get(const std::uint8_t value)
    {
        switch (value)
        {
        case 0: return USD;
        case 1: return AUD;
        case 2: return CAD;
        case 3: return CHF;
        case 4: return EUR;
        case 5: return GBP;
        case 6: return HKD;
        case 7: return JPY;
        case 255: return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum Currency [E103]");
    }
};
}
}
}
#endif
