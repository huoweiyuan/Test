#include <iostream>
using std::cout;
using std::endl;
int main()
{
  const int a = 2;
  const int *b = &a; // 底层 const
  int *c = const_cast<int*>(b); // 去除底层 const
  *c = 3;
  cout << &a << " " << a << endl;
  cout << b << " " << *b << endl;
  cout << c << " " << *c << endl;
  return 0;
}
