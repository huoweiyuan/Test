#include "zy_allocator.h"
#include <iostream>
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

int main()
{
  Allocator a;
  int *t = (int*)a.alloc(sizeof(int));
  a.free(t);
  Test *t1 = g_new<Test, 2>(&a, 1);
  g_delete(&a, t1);

  Test *t2 = new Test[2];
  delete [] t2;
  return 0;
}
