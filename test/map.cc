#include <iostream>
#include <map>
#include <string>
using namespace std;

typedef map<int, string> sub_map;
typedef map<int, sub_map> main_map;
int main(int argc, char const *argv[])
{
  main_map m;
  m[1][1] = "a";
  m[1][2] = "b";
  cout << m[1][1] << " " << m[1][2] << endl;
  return 0;
}
