#pragma once
#include <atomic>

namespace darkfeed
{
/// @brief A user-space spinlock class for low-contention situations with no context-switch overhead
class Spinlock {
    std::atomic_flag l = ATOMIC_FLAG_INIT; ///< The underlying atomic state variable

 public:
    /// @brief Locks the spinlock
    void lock();
    /// @brief Unlocks the spinlock
    void unlock();
};


/// @brief A class used to provide easy and safe multi-thread access to a spinlock by using RAII
/// Locks when created, unlocks when it goes out of scope
class SafeSpinlock {
    Spinlock &l;
 public:
    /// @brief Instantiates SafeSpinlock using an underlying Spinlock
    /// @param lk The underlying Spinlock to use
    /// @return A SafeSpinlock only after acquiring a lock on the underlying Spinlock
    SafeSpinlock(Spinlock &lk) : l(lk)
    { l.lock(); };

    /// @brief Destructs a SafeSpinlock and releases the lock on the underlying Spinlock
    ~SafeSpinlock()
    { l.unlock(); }
};
}
