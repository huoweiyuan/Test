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

Allocator *g_allocator = new Allocator();

int main()
{
  Test *t1 = new Test[2];
  delete [] t1;

  Test *t2 = g_new<Test, 10>(g_allocator, 1, 1);
  g_delete(g_allocator, t2);

  return 0;
}
