#include <iostream>
#include <bitset>
int main()
{
  double a = 1.1;
  int b = int(a);
  std::cout << std::bitset<sizeof(double) * 8>((*(int *)&a)) << std::endl;
  std::cout << std::bitset<sizeof(int) * 8>(b) << std::endl;
  return 0;
}
