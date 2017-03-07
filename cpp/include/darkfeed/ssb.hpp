#pragma once

#include <fstream>
#include "darkfeed/schemas/flatbuffers/ssb_generated.h"
#include "darkfeed/types/quotes.hpp"
#include "darkfeed/types/halts.hpp"
#include "darkfeed/types/trades.hpp"
#include "states.hpp"
#include "state_utils.hpp"
#include "darkfeed/util/locks.hpp"

namespace darkfeed
{
struct SecondState {
  Timestamp ts;
  std::uint32_t bid;
  std::uint32_t ask;
  std::uint32_t last;
  std::uint32_t low;
  std::uint32_t high;
  std::uint32_t t_vol;
  std::uint32_t vol;
  Halt halt;

  SecondState()
  {};
};

typedef google::dense_hash_map<Symbol, std::vector<SecondState>, XXSymHasher32, eqsym> SecondStateHT;

/// @brief Extends MarketState to provide serialization capabilities.
class SSBWriter : public MarketState {
  SecondStateHT sstates;
  Spinlock sstates_lock;
  std::ofstream f;

  /// @brief generates SecondState from underlying MarketState
  /// @return snapshot of SecondState
  SecondState extract_state(const Symbol &s);
  void capture_event(const Event &e);

 public:
  SSBWriter();
  /// @brief instantiates a SecondState for the given symbol (if it doesn't exist already)
  /// @param s the symbol to instantiate
  virtual void register_symbol(const Symbol &s);
  /// @brief write current states to file. Note that this overwrites the destination
  /// @param filename the destination to write to
  /// @return number of bytes written
  std::size_t write(const std::string &filename);
  // Modifiers
  /// @brief Push latest NBBO
  /// @param n the NBBO quote
  virtual void push_nbbo(const NBBO &n);
  /// @brief Push last trade
  /// @param t the trade
  virtual void push_trade(const Trade &t);
  /// @brief set halt for a given symbol
  /// @param h the halt
  virtual void push_halt(const Halt &h);
  /// @brief reset MarketState to default-constructed state. Useful for end of day
  virtual void clear();
};

class SSBReader {
  SecondStateHT sstates;
  std::ifstream f;
};

} //darkfeed