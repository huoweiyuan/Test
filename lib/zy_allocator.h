#ifndef _ZY_ALLOCATOR_
#define _ZY_ALLOCATOR_

#include <cstddef>

namespace zy
{

class Allocator
{
 private:
  // The size of last apply memory
  size_t m_block_size;
 public:
  void* alloc(std::size_t size);
  void free(void *ptr);

 public:
  Allocator() noexcept;
  ~Allocator() noexcept;
};

extern Allocator *g_allocator;

int alloc_init();
int alloc_deinit();

inline void* g_alloc(Allocator *allocator, std::size_t size)
{
  if (allocator == nullptr) return nullptr;
  return allocator->alloc(size);
}

inline void g_free(Allocator *allocator, void *ptr)
{
  if (allocator == nullptr)
    return;

  allocator->free(ptr);
}

template<typename C, size_t Num = 1, typename... P>
inline C* g_new(Allocator *allocator, P... args)
{
  if (allocator == nullptr) return nullptr;
  size_t _class_size = sizeof(C);
  C *_ptr = static_cast<C*>(allocator->alloc(_class_size * Num));
  if (_ptr == nullptr)
    return nullptr;
  C *_construct_ptr = _ptr;
  for (size_t i = 0; i < Num; i++)
  {
    _construct_ptr = new(_construct_ptr + i) C(args...);
  }
  return _ptr;
}

template<typename C>
inline void g_delete(Allocator *allocator, C *ptr)
{
  if (allocator == nullptr || ptr == nullptr)
    return;

  ptr->~C();
  allocator->free(ptr);
}

}

#endif // _ZY_ALLOCATOR_
