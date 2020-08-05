#include <stdio.h>
#include <stdlib.h>
void test()
{
  void *p = malloc(7);
  printf("%p\n", p);
}

int main()
{
  test();
  return 0;
}
