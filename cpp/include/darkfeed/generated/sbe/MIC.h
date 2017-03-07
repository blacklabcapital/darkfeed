/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _DARKFEED_SCHEMAS_SBE_MIC_H_
#define _DARKFEED_SCHEMAS_SBE_MIC_H_

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

class MIC {
 public:

    enum Value {
        NONE = (std::uint8_t) 0,
        XNAS = (std::uint8_t) 1,
        XNYS = (std::uint8_t) 2,
        XASE = (std::uint8_t) 3,
        CBOE = (std::uint8_t) 4,
        ARCX = (std::uint8_t) 5,
        XCIS = (std::uint8_t) 6,
        XPHL = (std::uint8_t) 7,
        OPRA = (std::uint8_t) 8,
        XBOS = (std::uint8_t) 9,
        XNGS = (std::uint8_t) 10,
        XNCM = (std::uint8_t) 11,
        BATS = (std::uint8_t) 12,
        BATY = (std::uint8_t) 13,
        EDGE = (std::uint8_t) 14,
        EDGX = (std::uint8_t) 15,
        XCHI = (std::uint8_t) 16,
        XOTC = (std::uint8_t) 17,
        EDGA = (std::uint8_t) 18,
        SMART = (std::uint8_t) 19,
        ICEL = (std::uint8_t) 20,
        IEX = (std::uint8_t) 21,
        SIP = (std::uint8_t) 22,
        NULL_VALUE = (std::uint8_t) 255
    };

    static MIC::Value get(const std::uint8_t value)
    {
        switch (value)
        {
        case 0: return NONE;
        case 1: return XNAS;
        case 2: return XNYS;
        case 3: return XASE;
        case 4: return CBOE;
        case 5: return ARCX;
        case 6: return XCIS;
        case 7: return XPHL;
        case 8: return OPRA;
        case 9: return XBOS;
        case 10: return XNGS;
        case 11: return XNCM;
        case 12: return BATS;
        case 13: return BATY;
        case 14: return EDGE;
        case 15: return EDGX;
        case 16: return XCHI;
        case 17: return XOTC;
        case 18: return EDGA;
        case 19: return SMART;
        case 20: return ICEL;
        case 21: return IEX;
        case 22: return SIP;
        case 255: return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum MIC [E103]");
    }
};
}
}
}
#endif
