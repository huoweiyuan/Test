#include <iostream>
#include <list>
#include <fstream>
using namespace std;
int a;
int test(int a)
{
  return 0;
}
int main()
{
  ifstream dataFile("test.txt");
  list<int> data((istream_iterator<int>(dataFile)), istream_iterator<int>());
  cout << data.front() << endl;
}
