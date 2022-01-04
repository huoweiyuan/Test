#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

struct Test
{
  static const int m_static_value = 1;
  int m_value = 2;
};

int main()
{
  struct Test test;
  memset(&test, 0, sizeof(struct Test));
  cout << test.m_static_value << " " << test.m_value << endl;
  return 0;
}
