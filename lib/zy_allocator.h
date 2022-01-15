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

  const int ALLOC_HEAD_SIZE = sizeof(size_t);
  const int OBJ_NUM_HEAD_SIZE = sizeof(size_t);
  const int READ_ALLOC_SIZE_OFFSET = -(ALLOC_HEAD_SIZE);
  const int READ_OBJ_NUM_OFFSET = -(OBJ_NUM_HEAD_SIZE);

 private:
  void* alloc(std::size_t size);
  void free(void *ptr);
  template<typename C, size_t Num, typename... P>
  C* create_obj(P... args);
  template<typename C>
  void delete_obj(C *ptr);


 public:
  Allocator() noexcept;
  ~Allocator() noexcept;

  friend void* g_alloc(Allocator*, size_t);
  friend void g_free(Allocator*, void*);
  template<typename C, size_t Num, typename... P>
  friend C* g_new(Allocator*, P...);
  template<typename C>
  friend void g_delete(Allocator*,C*);
};

template<typename C, size_t Num,  typename... P>
C* Allocator::create_obj(P... args)
{
  const size_t _class_size = sizeof(C);
  void *_ptr = alloc(_class_size * Num);
  if (_ptr == nullptr)
    return nullptr;

  *(static_cast<size_t*>(_ptr)) = Num;
  _ptr = static_cast<char*>(_ptr) + OBJ_NUM_HEAD_SIZE;

  C *_construct_ptr = static_cast<C*>(_ptr);
  for (size_t i = 0; i < Num; i++)
  {
    new(_construct_ptr + i) C(args...);
  }
  return _construct_ptr;
}

template<typename C>
void Allocator::delete_obj(C *ptr)
{
  if (ptr == nullptr)
    return;
  char *_alloc_ptr = reinterpret_cast<char*>(ptr) + READ_OBJ_NUM_OFFSET;
  const size_t _obj_num = *(reinterpret_cast<size_t*>(_alloc_ptr));
  C *_destruct_ptr = ptr;
  for (size_t i = 0; i < _obj_num; i++)
  {
    (_destruct_ptr + i)->~C();
  }
  free(_alloc_ptr);
}

int alloc_init();
int alloc_deinit();

inline void* g_alloc(Allocator *allocator, size_t size)
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
C* g_new(Allocator *allocator, P... args)
{
  if (allocator == nullptr) return nullptr;
  C *_ptr = allocator->create_obj<C, Num>(args...);
  return _ptr;
}

template<typename C>
void g_delete(Allocator *allocator, C *ptr)
{
  if (allocator == nullptr)
    return;
  allocator->delete_obj(ptr);
}

}

#endif // _ZY_ALLOCATOR_
