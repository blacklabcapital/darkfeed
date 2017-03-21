#pragma once
#include <cstdlib>
#include <cstdint>
#include <utility>

namespace darkfeed
{
/// @brief Serializes data using Simple-Binary-Encoding with internal framing
/// @ingroup serialization
class SBESerializer {
 public:
    /// @brief Serializes argument using appropriate SBE schema. Framing is added within the SBE header.
    /// @param buf The buffer to serialize the object to.
    /// @param buf_size The size of the buffer in bytes
    /// @warning buf must be sufficiently large to accomodate the resulting data. It's recommended to round it up an order of magnitude larger than the sum of the fields in bytes. Eg; for a 200 byte message, make this 1kB.
    /// @param x The object to serialize
    /// @return The number of bytes written to buf
    template<typename T> static std::size_t serialize(char *buf, std::size_t buf_size, const T &x);
    /// @brief Deserializes argument using appropriate flatbuffer schema. No framing is assumed.
    /// @param buf The buffer containing the SBE serialized data
    /// @return a pair containing the deserialized object and a status indicator. If the status indicator is true, deserialization was successful.
    template<typename T> static std::pair<T, bool> deserialize(const char *buf, std::size_t len);
    /// @brief Returns the type of message. Can be cast to darkfeed::EventType
    /// @param buf The buffer containing the SBE serialized data
    /// @param len The size of the buffer in bytes
    /// @return Message type ID (castable to darkfeed::EventType)
    std::uint8_t msg_type(const char *buf, std::size_t len);
};
}
