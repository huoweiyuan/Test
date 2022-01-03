#include "zy_allocator.h"
#include <iostream>

using namespace std;
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
};

int main()
{
  Allocator _alloc;
  Test *t1 = g_new<Test, &_alloc, 1>();
  // g_delete(t1);
  return 0;
}
