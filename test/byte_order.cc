#include <stdio.h>

union data//共用体
{
    char ch;
    int i;
}un;
int main()
{
  un.i = 0x12345678;
  printf("存入值：%x\n",un.i);
  printf("最低地址为：%x\n",un.ch);
  if(un.ch == 0x78)
  {
    printf("小端\n");
  }
  else
  {
    printf("大端\n");
  }
  return 0;
}
