#include "htp_sds.h"
#include <iostream>
#include <set>
// HotXA74692656_25_2_7
using namespace std;
int main()
{
  Htp_sds a,b;
  a = (const char*)"HotXA74692656_25_2_7";
  b = (const char*)"HotXA74692656_25_2_7";
  set<Htp_sds> test;
  pair<set<Htp_sds>::iterator, bool> insert = test.insert(a);
  cout << insert.second << endl;
  insert = test.insert(b);
  cout << insert.second << endl;
  return 0;
}
