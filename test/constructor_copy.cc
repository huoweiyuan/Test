#include <iostream>
#include <cstring>
struct test_struct
{
  char s[6];
  test_struct()
  {}
  test_struct(const char *s_)
  {
    std::cout << 0 << std::endl;
    strcpy(s, s_);
  }
  test_struct(const test_struct &t)
  {
    std::cout << 1 << std::endl;
    strcpy(s, t.s);
  }

  test_struct& operator=(const test_struct &t)
  {
    std::cout << 2 << std::endl;
    strcpy(s, t.s);
    return *this;
  }
};

int main()
{
  test_struct s1("nihao");
  test_struct s2;
  s2 = s1;
  return 0;
}
