#pragma once
#include <cstring>
#include <string>
#include <xxhash.h>
#include "darkfeed/types/symbol.hpp"
#include "crc32c.h"


namespace darkfeed
{

/// @brief Computes a hash of a symbol using the XXHash32 algorithm with offset
/// @param s the symbol
/// @return the hash as a std::uint32_t
inline std::uint32_t xxhash_sym_32(const Symbol &s)
{
    //get hash of root symbol
    std::uint32_t base_hash = XXH32(s.root, std::strlen(s.root), 0);
    //stride by type and series
    base_hash += (std::uint32_t) IssueType::MAX * s.series + (std::uint32_t) s.issue_type;
    return base_hash;
}


/// @brief Struct used to check for equality between symbols in a dense hash table
struct eqsym {
    bool operator()(const Symbol &a, const Symbol &b) const
    {
        return a == b;
    }
};


/// @brief Struct used to check for equality between exchanges
struct eqexg {
    bool operator()(const Exchange &a, const Exchange &b) const
    {
        return a.mic == b.mic;
    }
};


/// @brief Computes the hash of a std::string using the XXHash32 algorithm
/// @param s the string
/// @return the hash as a std::uint32_t
inline std::uint32_t xxhash_str_32(const std::string &s)
{
    const char *str = s.c_str();
    return XXH32(str, s.length(), 0);
}

/// @brief Computes the ahsh of a C-string using the XXHash32 algorithm
/// @param s the string
/// @return the hash as a std::uint32_t
inline std::uint32_t xxhash_c_str_32(const char *s)
{ return XXH32(s, std::strlen(s), 0); }


/// @brief Struct used to check for equality between std::string objects in a dense hash table
struct eqstr {
    bool operator()(const std::string &a, const std::string &b) const
    {
        return b == a;
    }
};


/// @brief Struct used to check for equality between C-strings in a dense hash table
struct eq_c_str {
    bool operator()(const char *a, const char *b) const
    { return !std::strcmp(a, b); }
};


/// @brief Struct used to hash symbols for a dense hash table
struct XXSymHasher32 {
    inline std::uint32_t operator()(const Symbol &s) const
    { return xxhash_sym_32(s); }
};


/// @brief Struct used to hash exchanges for reporting/listing exchange keyed hash tables
struct XXExchangeHasher32 {
    inline std::uint32_t operator()(const Exchange &e) const
    {
        return static_cast<std::uint32_t>(e.mic);
    }
};


/// @brief Struct used to hash std::string objects for a dense hash table
struct XXStrHasher32 {
    inline std::uint32_t operator()(const std::string &s) const
    { return xxhash_str_32(s); }
};


/// @brief Struct used to hash C-strings for a dense hash table
struct XXCStrHasher32 {
    inline std::uint32_t operator()(const char *s) const
    { return xxhash_c_str_32(s); }
};


/// @brief Computes the CRC32C checksum using slicing-by-8 method or SSE 4.2 CRC32C instruction if HAS_SSE_4_2 defined at compile time
/// @param crc Carryover checksum
/// @param s The buffer to hash
/// @param len The length of the buffer in bytes
/// @return The checksum as an unsigned 32 bit integer
std::uint32_t crc32c(std::uint32_t crc, const void *buf, std::size_t len);

/// @brief Struct used to hash strings using CRC32C
struct CRC32CStrHasher {
    inline std::uint32_t operator()(const std::string &s)
    {
        return CRC32C_FINISH(crc32c(CRC32C_INIT, s.c_str(), s.size()));
    }
};

/// @brief Struct used to hash C-strings using CRC32C
struct CRC32CCStrHasher {
    inline std::uint32_t operator()(const char *s)
    {
        std::size_t len = std::strlen(s);
        return CRC32C_FINISH(crc32c(CRC32C_INIT, s, len));
    }
};


/// @brief Struct used to hash Symbols using CRC32C
struct CRC32CSymHasher {
    inline std::uint32_t operator()(const Symbol &s)
    {
        std::size_t len = std::strlen(s.root);
        auto post_root = crc32c(CRC32C_INIT, s.root, len);
        char modifiers[3] = {s.series, (char) s.listing_exg.mic, (char) s.issue_type};
        return CRC32C_FINISH(crc32c(post_root, modifiers, 3));
    }
};


/// @brief Struct used as a std::hash wrapper for identity hash
struct IdentityHasher {
    inline std::uint32_t operator()(const std::uint64_t x)
    {
        return (std::uint32_t) x;
    }
};
}


