#include <iostream>
#include <string.h>
int main(int argc, char **argv)
{
  char test[] = "1\"";
  std::cout << test << " " << strlen(test) << std::endl;
  return 0;
}
