#include <iostream>
#include <bitset>
int main()
{
  double a = 1.1;
  int b = int(a);
  std::cout << std::bitset<sizeof(double) * 8>((*(int *)&a)) << std::endl;
  std::cout << std::bitset<sizeof(int) * 8>(b) << std::endl;

  std::cout << sizeof(short) * 8 << std::endl;
  unsigned short c = 0xffff;
  short d = c;
  std::cout << c << std::endl;
  std::cout << d << std::endl;

  int e = -1;
  unsigned int f = 1;
  std::cout << std::hex << e - f << std::endl;
  return 0;
}
