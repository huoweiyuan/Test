#include <iostream>
#include <set>

using namespace std;


int main()
{
  set<int> int_set;
  pair<set<int>::iterator, bool> iter = int_set.insert(1);
  cout << iter.second << endl;
  iter = int_set.insert(1);
  cout << iter.second << endl;
  return 0;
}
