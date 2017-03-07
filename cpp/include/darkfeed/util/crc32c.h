// Copyright 2008,2009,2010 Massachusetts Institute of Technology.
// All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.
// NOTE: Modified from github.com/htot/crc32c

#pragma once
#include <cstddef>
#include <cstdint>

namespace darkfeed
{
#define CRC32C_INIT 0xFFFFFFFF //Initial value if no previous checksum

/** Converts a partial CRC32-C computation to the final value. */
#define CRC32C_FINISH(CRC_VAL) ~CRC_VAL

/// @brief Computes CRC32C checksum using lookup table 8 bytes at a time
/// @param crc Partial CRC from previous computation or CRC32C_INIT
/// @param data The buffer to checksum on
/// @param length The number of bytes to checksum on
/// @return Partial CRC32C checksum. Use CRC32C_FINISH to digest.
std::uint32_t crc32cSlicingBy8(std::uint32_t crc, const void *data, size_t length);
#ifdef HAS_SSE_4_2
/// @brief Computes CRC32C checksum using Intel SSE Instructions
/// @param crc The partial checksum from previous computation or CRC32C_INIT
/// @param data The buffer to checksum on
/// @param length The number of bytes to checksum on
/// @return Partial CRC32C checksum,. Use CRC32C_FINISH to digest.
std::uint32_t crc32cIntelC(std::uint32_t crc, const void *data, size_t length);
#endif
} //darkfeed
