#include <iostream>
#include <set>
using namespace std;
struct ss
{
  uint32_t a;
  char c[4];
};
int main()
{
  set<int> s;
  cout << sizeof(s) << endl;
  s.insert(1);
  cout << sizeof(s) << endl;
  cout << sizeof(ss::a) << endl; // c++ 11
  return 0;
}
