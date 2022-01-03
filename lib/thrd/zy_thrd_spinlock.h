#ifndef _ZY_THRD_SPINLOCK_
#define _ZY_THRD_SPINLOCK_

#include <atomic>

namespace zy
{
  class Spinlock
  {
   private:
    atomic_bool m_lock;
   public:
    Spinlock()
      : m_lock(0)
    {}
    ~Spinlock()
    {}

   public:
    inline void lock() noexcept
    {
      for(;;)
      {
        if (!m_lock.exchange(true, std::memory_order_acquire))
        {
          return;
        }
        while (m_lock.load(std::memory_order_relaxed))
        {
          __builtin_ia32_pause();
        }
      }
    }

    inline bool try_lock() noexcept
    {
      return !m_lock.load(std::memory_order_relaxed) &&
      !m_lock.exchange(true, std::memory_order_acquire);
    }

    inline void unlock() noexcept
    {
      m_lock.store(false, std::memory_order_release);
    }
  };
}

#endif // _ZY_THRD_SPINLOCK_
