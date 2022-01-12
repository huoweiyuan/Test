#include "zy_allocator.h"
#include <cstdlib>

using namespace zy;
using namespace std;

Allocator::Allocator() noexcept
: m_block_size(0)
{
}

Allocator::~Allocator() noexcept
{}

void* Allocator::alloc(size_t size)
{
  void *ptr = ::malloc(size + ALLOC_HEAD_SIZE);
  return static_cast<char*>(ptr) + ALLOC_HEAD_SIZE;
}

void Allocator::free(void *ptr)
{
  ::free(static_cast<char*>(ptr) + READ_ALLOC_SIZE_OFFSET);
}

