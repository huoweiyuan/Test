#include "calculate.h"
#include <iostream>
#include <cstring>
void print(char &c)
{
  std::cout << c;
}
int main(int argc, char **argv)
{
  Calculate<char> cal;
  // char c[] = "(a*(b+c)/d*(e+f*g))%h";
  // char c[] = "(f*g)";
  // char c[] = "(x+y)/(c*a)";
  cal.build_calculate(argv[1], strlen(argv[1]));
  cal.postOrder(print);
  std::cout<<std::endl;
  cal.inOrder(print);
  std::cout<<std::endl;
  cal.preOrder(print);
  return 0;
}
