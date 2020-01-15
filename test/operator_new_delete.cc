#include <iostream>
#include <new>
using std::cout;
using std::endl;

/*
  8个可重载的操作
*/
void* operator new(size_t size) throw(std::bad_alloc)
{
  void *mem = NULL;
  if ((mem = malloc(size)) != NULL)
  {
    cout << "custom new" << endl;
  }
  return mem;
}

void* operator new[](size_t size) throw(std::bad_alloc)
{
  void *mem = NULL;
  if ((mem = malloc(size)) != NULL)
  {
    cout << "custom new" << endl;
  }
  return mem;
}

// 定位 new 表达式
void* operator new(size_t size, int id) throw(std::bad_alloc)
{
  void *mem = NULL;
  if ((mem = malloc(size)) != NULL)
  {
    cout << "custom new " << id << endl;
  }
  return mem;
}

void* operator new[](size_t size, int id) throw(std::bad_alloc)
{
  void *mem = NULL;
  if ((mem = malloc(size)) != NULL)
  {
    cout << "custom new " << id << endl;
  }
  return mem;
}

void operator delete(void *mem) throw()
{
  cout << "custom delete" << endl;
  free(mem);
}

void operator delete[](void *mem) throw()
{
  cout << "custom delete" << endl;
  free(mem);
}

class Test
{
  int i;
 public:
  Test():i(1)
  {
    cout << "Test()" << endl;
  }
  Test(int r):i(r)
  {
    cout << "Test(int)" << endl;
  }
  ~Test()
  {
    cout << "~Test()" << endl;
  }
 public:
  void print()
  {
    cout << "print i " << i << endl;
  }
};
int main()
{
  Test *t = new Test[3];
  t[0].print();
  delete[] t;

  t = new(4) Test[3];
  t[0].print();
  delete[] t;
  return 0;
}
