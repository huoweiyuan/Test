#include <stdio.h>
int main()
{
  /*
    逗号运算符的优先级低于赋值操作符
   */
  // int a = 1,2; // this is error
  int a = (1,2); // this is ok
  printf("%d", a); // result is 2
  return 0;
}
