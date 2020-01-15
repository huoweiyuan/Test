#include <map>
#include <iostream>
using namespace std;
int main()
{
  map<int,int> m;
  m[1] = 1;
  m[2] = 2;
  m[3] = 3;
  map<int,int>::const_iterator iter = m.begin();
  while (iter != m.end())
  {
    m[iter->first] = iter->second + 1;
    cout << iter->second << endl;
    iter++;
  }
  return 0;
}
