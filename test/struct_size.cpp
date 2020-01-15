#include <iostream>
#include <string>
struct a
{
  char c;
  int i;
  std::string s;
};

struct b
{

};

struct c
{
  int i;
};

struct d
{
  char c[2];
};

struct e
{
  int i;
  char c[2];
};

int main()
{
  struct a t;
  struct b t2;
  struct c t3;
  struct d t4;
  struct e t5;
  std::cout << sizeof(a) << std::endl;
  std::cout << sizeof(t) << std::endl;
  std::cout << sizeof(b) << std::endl;
  std::cout << sizeof(t2) << std::endl;
  std::cout << sizeof(c) << std::endl;
  std::cout << sizeof(t3) << std::endl;
  std::cout << sizeof(d) << std::endl;
  std::cout << sizeof(t4) << std::endl;
    std::cout << sizeof(e) << std::endl;
  std::cout << sizeof(t5) << std::endl;
  return 0;
}
