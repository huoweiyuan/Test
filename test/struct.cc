#include <iostream>
using namespace std;
struct s1
{
  char a1;
  char a2;
  int a3;
};

struct s2
{ 
  char a1;
  int a3;
  char a2;
};

struct s3
{ 
  int a3;
  char a2;
  char a1;
};

int main()
{
  cout << sizeof(s1) << " " << sizeof(s2) << " " << sizeof(s3) << endl;
  return 0;
}
