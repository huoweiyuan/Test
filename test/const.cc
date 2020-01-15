#include <iostream>

int main()
{
  int t = 1, d = 2;
  const int *i = &t;
  std::cout << *i << std::endl;
  i = &d;
  std::cout << *i << std::endl;
  return 0;
}
