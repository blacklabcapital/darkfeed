#pragma once
#include <atomic>
#include <cstdlib>

#define CACHE_LINE_SIZE 64 //TODO get this at compile time

namespace darkfeed
{

template<typename T, std::size_t S = sizeof(T)>
void is_power_of_2()
{
    static_assert((S != 0) && !(S & (S - 1)), "Size must be a power of 2");
}


/// @brief Lockfree Static short-lived allocator used for other lockfree data structures
/// @param T the type of variable to allocate
/// @param N number of elements in allocator
template<typename T, std::size_t N> class RingAllocator {
    T *arena = nullptr;
    std::atomic_size_t arena_idx;
    const std::size_t size_mask;
 public:
    /// @brief Creates a new RingAllocator
    /// @param size The number of elements in the underlying arena. Make this large enough to avoid overwriting fresh data
    RingAllocator<T, N>() : size_mask(N - 1)
    {
        static_assert((N != 0) && !(N & (N - 1)), "N must be a power of 2");
        static_assert((CACHE_LINE_SIZE != 0) && !(CACHE_LINE_SIZE & (N - 1)), "cache line size must be a power of 2");
        //allocate pool
        int alloc_code = posix_memalign(static_cast<void **>(&arena), CACHE_LINE_SIZE, sizeof(T) * N);
        if (alloc_code == EINVAL)
            throw std::logic_error("invalid alignment specified for implementation. Must be power of 2");
        else if (alloc_code == ENOMEM)
        {
            throw std::bad_alloc();
        }
        //make sure arena starts at the right spot
        arena_idx = 0;
    }

    ~RingAllocator()
    {
        if (arena != nullptr)
            std::free(arena);
    }

    /// @brief Return next element's pointer. Thread-safe
    /// @return pointer to next available element
    T *get_next()
    {
        auto idx = arena_idx.fetch_add(1, std::memory_order_relaxed);
        idx &= size_mask;
        return &arena[idx];
    }
};
} //darkfeed
