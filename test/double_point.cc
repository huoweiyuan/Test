#include <stdio.h>

void test(int **t)
{
  (*t)++;
}

int main()
{
  int t[2] = {1, 2};
  int *t1 = t;
  test(&t1);
  printf("%d", *t1);
  return 0;
}
