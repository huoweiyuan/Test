#include <stdio.h>
int main()
{
  // int a = 1,2; // this is error
  1; // this is ok
  (1,2); // this is ok
  1,2; // this is ok
  int a = (1,2); // this is ok
  printf("%d", a); // result is 2
  a = 1,2;// this is ok
  printf("%d", a); // result is 1
  return 0;
}
