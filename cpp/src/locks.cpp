#include "darkfeed/util/locks.hpp"

namespace darkfeed {
    void Spinlock::lock()
    {
        while (l.test_and_set(std::memory_order_acquire))
            ;
    }

    void Spinlock::unlock()
    {
        l.clear(std::memory_order_release);
    }
}
