#include "avl.h"

void test1()
{
  avl<char> a;
  a.insert('a');
  a.insert('b');
  a.insert('c');
}
int main()
{
  test1();
  return 0;
}
