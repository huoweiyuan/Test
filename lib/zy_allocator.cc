#include "zy_allocator.h"
#include <cstdlib>

using namespace zy;
using namespace std;

Allocator::Allocator() noexcept
{
}

Allocator::~Allocator() noexcept
{}

void* Allocator::alloc(size_t size)
{
  void *ptr = ::malloc(size);
  return ptr;
}

void Allocator::free(void *ptr)
{
  ::free(ptr);
}

Allocator *g_allocator = new Allocator();
