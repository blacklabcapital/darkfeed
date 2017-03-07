#include "darkfeed/util/hashing.hpp"
//#define HAS_SSE_4_2
#include "darkfeed/util/crc32c.h"

namespace darkfeed
{

std::uint32_t crc32c(std::uint32_t crc, const void *buf, std::size_t len)
{
#ifdef HAS_SSE_4_2
    return crc32cIntelC(crc, buf, len);
#else
    return crc32cSlicingBy8(crc,buf,len);
#endif
}
}