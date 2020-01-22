#include <stdio.h>
int main()
{
  unsigned int a = 0x01;
  unsigned int b = 0x03;
  if (a & b) // error
    printf("a is equal to b");
  return 0;
}
