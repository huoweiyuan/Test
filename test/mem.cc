#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
int main()
{
  uint8_t *test = (uint8_t*)malloc(97);
  if (test)
  {
    memset(test,0, 97);
    free(test);
  }
  return 0;
}
