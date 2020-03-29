#include<iostream>
int a = 1;
void test1()
{
  int a = 2;
  std::cout << a << std::endl;
}

int main()
{
  test1();
  std::cout << a << std::endl;
  return 0;
}
