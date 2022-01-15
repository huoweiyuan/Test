#include "zy_allocator.h"
#include <iostream>
#include <cstdlib>
#include <cstdlib>

using namespace std;
using namespace zy;
class Test
{
 public:
  Test()
  {
    cout << "Test::Test" << endl;
  }

  Test(int a)
  {
    cout << "Test::Test(int)" << endl;
  }

  Test(int a, int b)
  {
    cout << "Test::Test(int,int)" << endl;
  }

  Test(Allocator *a, int b)
  {
    cout << "Test::Test(Allocator*,int)" << endl;
  }

  ~Test()
  {
    cout << "Test::~Test()" << endl;
  }
};

class TestAllocator : public Allocator
{
 private:
  const int ALLOC_HEAD_SIZE = sizeof(size_t);
  const int READ_ALLOC_SIZE_OFFSET = -(ALLOC_HEAD_SIZE);

 public:
  void* alloc(std::size_t size)
  {
    size_t _alloc_size = size + ALLOC_HEAD_SIZE;
    void *ptr = ::malloc(_alloc_size);
    *static_cast<size_t*>(ptr) = _alloc_size;
    return static_cast<char*>(ptr) + ALLOC_HEAD_SIZE;
  }

  void* realloc(void *ptr, size_t size)
  {
    if (ptr != nullptr)
    {
      ptr = static_cast<char*>(ptr) + READ_ALLOC_SIZE_OFFSET;
    }

    size_t _realloc_size = size + ALLOC_HEAD_SIZE;
    ptr = ::realloc(ptr, _realloc_size);
    *static_cast<size_t*>(ptr) = _realloc_size;
    return static_cast<char*>(ptr) + ALLOC_HEAD_SIZE;
  }

  void free(void *ptr)
  {
    ::free(static_cast<char*>(ptr) + READ_ALLOC_SIZE_OFFSET);
  }

};

TestAllocator *g_allocator = new TestAllocator();

int main()
{
  Test *t1 = new Test[2];
  delete [] t1;

  Test *t2 = g_new<Test, 10>(g_allocator, 1, 1);
  g_delete(g_allocator, t2);

  char *t3 = static_cast<char*>(g_alloc(g_allocator, 1024));
  t3 = static_cast<char*>(g_realloc(g_allocator, t3, 2048));
  g_free(g_allocator, t3);

  char *t4 = static_cast<char*>(g_alloc(g_allocator, 1024));
  t4 = static_cast<char*>(g_realloc(g_allocator, t4, 512));
  g_free(g_allocator, t4);

  char *t5 = static_cast<char*>(g_realloc(g_allocator, NULL, 1024));
  g_free(g_allocator, t5);

  return 0;
}
