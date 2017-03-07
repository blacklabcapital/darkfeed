/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _DARKFEED_SCHEMAS_SBE_ISSUETYPE_H_
#define _DARKFEED_SCHEMAS_SBE_ISSUETYPE_H_

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

class IssueType {
 public:

    enum Value {
        normal = (std::uint8_t) 0,
        preferred = (std::uint8_t) 1,
        warrant = (std::uint8_t) 2,
        right = (std::uint8_t) 3,
        unit = (std::uint8_t) 4,
        non_voting = (std::uint8_t) 5,
        mini = (std::uint8_t) 6,
        whenIssued = (std::uint8_t) 7,
        NULL_VALUE = (std::uint8_t) 255
    };

    static IssueType::Value get(const std::uint8_t value)
    {
        switch (value)
        {
        case 0: return normal;
        case 1: return preferred;
        case 2: return warrant;
        case 3: return right;
        case 4: return unit;
        case 5: return non_voting;
        case 6: return mini;
        case 7: return whenIssued;
        case 255: return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum IssueType [E103]");
    }
};
}
}
}
#endif
