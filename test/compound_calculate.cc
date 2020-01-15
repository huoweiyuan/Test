#include <iostream>
int main()
{
  int a, b, c;
  a = b = c = 1;
  a = b += c;
  std::cout << a << " " << b << " " << c << std::endl;
  a = b = c = 1;
  a += b = c;
  std::cout << a << " " << b << " " << c << std::endl;
}
