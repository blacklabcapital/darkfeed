#pragma once
#include <flatbuffers/flatbuffers.h>

namespace darkfeed
{
/// @addtogroup serialization
/// @brief utilities for serializing market data for transmission or storage

/// @brief Serializes messages using flatbuffer encoding and adds a 64 bit header
/// @ingroup serialization
class FBSerializer {
 public:
    /// @brief Serializes argument using appropriate Flatbuffers schema. Framing is added
    /// @note The header frame is a 32 bit little endian message length (not including the header) and a 32 bit CRC32C checksum (of the following message). If you need to access the message, it's offset by 8 bytes
    /// @param buf The buffer to serialize the object to.
    /// @param buf_size The size of the buffer in bytes
    /// @warning buf must be sufficiently large to accomodate the resulting data. It's recommended to round it up an order of magnitude larger than the sum of the fields in bytes. Eg; for a 200 byte message, make this 1kB.
    /// @param x The object to serialize
    /// @return The number of bytes written to buf
    template<typename T> static std::size_t serialize(char *buf, std::size_t buf_size, const T &x);
    /// @brief Deserializes argument using appropriate flatbuffer schema. No framing is assumed.
    /// @param b The buffer containing the flatbuffer serialized data
    /// @return a pair containing the deserialized object and a status indicator. If the status indicator is true, deserialization was successful.
    template<typename T> static std::pair<T, bool> deserialize(const char *b, std::size_t len);
};
} //darkfeed