#ifndef _ZY_ALLOCATOR_
#define _ZY_ALLOCATOR_

#include <cstddef>
#include <utility>
namespace zy
{

class Allocator
{
 private:
  const int OBJ_NUM_HEAD_SIZE = sizeof(size_t);
  const int READ_OBJ_NUM_OFFSET = -(OBJ_NUM_HEAD_SIZE);

 public:
  virtual void* alloc(std::size_t size) = 0;
  virtual void* realloc(void *ptr, size_t size) = 0;
  virtual void free(void *ptr) = 0;

 public:
  template<typename Class, size_t Num, typename... P>
  Class* create_obj(P&&... args)
  {
    const size_t _class_size = sizeof(Class);
    void *_ptr = alloc(_class_size * Num + OBJ_NUM_HEAD_SIZE);
    if (_ptr == nullptr)
      return nullptr;

    *(static_cast<size_t*>(_ptr)) = Num;
    _ptr = static_cast<char*>(_ptr) + OBJ_NUM_HEAD_SIZE;

    Class *_construct_ptr = static_cast<Class*>(_ptr);
    for (size_t i = 0; i < Num; i++)
    {
      new(_construct_ptr + i) Class(std::forward<P>(args)...);
    }
    return _construct_ptr;
  }

  template<typename Class>
  void delete_obj(Class *ptr)
  {
    if (ptr == nullptr)
      return;
    char *_alloc_ptr = reinterpret_cast<char*>(ptr) + READ_OBJ_NUM_OFFSET;
    const size_t _obj_num = *(reinterpret_cast<size_t*>(_alloc_ptr));
    Class *_destruct_ptr = ptr;
    for (size_t i = 0; i < _obj_num; i++)
    {
      (_destruct_ptr + i)->~Class();
    }
    free(_alloc_ptr);
  }


 public:
  Allocator() noexcept = default;
  virtual ~Allocator() noexcept = default;

  // friend void* g_alloc(Allocator*, size_t);
  // friend void* g_realloc(Allocator*, void*, size_t);
  // friend void g_free(Allocator*, void*);
  // template<typename Class, size_t Num, typename... P>
  // friend Class* g_new(Allocator*, P...);
  // template<typename Class>
  // friend void g_delete(Allocator*,Class*);
};

inline void* g_alloc(Allocator *allocator, size_t size)
{
  if (allocator == nullptr)
    return nullptr;
  return allocator->alloc(size);
}

inline void* g_realloc(Allocator *allocator, void *ptr, size_t size)
{
  if (allocator == nullptr)
    return nullptr;
  return allocator->realloc(ptr, size);
}

inline void g_free(Allocator *allocator, void *ptr)
{
  if (allocator == nullptr || ptr == nullptr)
    return;
  allocator->free(ptr);
}

template<typename Class, size_t Num = 1, typename... P>
Class* g_new(Allocator *allocator, P&&... args)
{
  if (allocator == nullptr)
    return nullptr;
  Class *_ptr = allocator->create_obj<Class, Num>(std::forward<P>(args)...);
  return _ptr;
}

template<typename Class>
void g_delete(Allocator *allocator, Class *ptr)
{
  if (allocator == nullptr || ptr == nullptr)
    return;
  allocator->delete_obj(ptr);
}

}

#endif // _ZY_ALLOCATOR_
