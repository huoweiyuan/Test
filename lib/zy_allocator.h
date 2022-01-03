#ifndef _ZY_ALLOCATOR_
#define _ZY_ALLOCATOR_

namespace zy
{

class Allocator
{
 private:
  // The size of last apply memory
  size_t m_block_size;
 public:
  void* alloc(size_t size);
  void free(void *ptr);
};

extern Allocator *g_allocator;

int alloc_init();
int alloc_deinit();

inline void* g_alloc(Allocator *allocator = g_allocator, size_t size)
{
  if (allocator == nullptr) return nullptr;
  return allocator->alloc(size);
}

inline void g_free(void *ptr)
{
  allocator->free(ptr);
}

template<typename C, size_t Num = 1, typename... P>
inline C* g_new(Allocator *allocator = g_allocator, P... args)
{
  if (allocator == nullptr) return nullptr;
  void *_ptr = allocator->alloc(sizeof(C));
  if (_ptr == nullptr)
    return nullptr;
  _ptr = new(_ptr) C(args...);
  return static_cast<C>(_ptr);
}

template<typename C>
inline void g_delete(C *ptr)
{
  if (ptr == nullptr)
    return;
  ptr->~C();
  allocator->free(ptr);
}

}

#endif // _ZY_ALLOCATOR_
