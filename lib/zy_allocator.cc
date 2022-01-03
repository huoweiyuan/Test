#include "zy_allocator.h"

using namespace zy;

Allocator::Allocator()
{
}

Allocator::~Allocator()
{}

void* Allocator::alloc(size_t size)
{
  
}

Allocator *g_allocator = new Allocator();
