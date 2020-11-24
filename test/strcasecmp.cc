#include <string.h>
#include <iostream>

using namespace std;

void cmp(const char *a, const char *b)
{
  cout << a << " " << b << " " << strcasecmp(a, b) << endl;
}
int main(int argc, char **argv)
{
  const char a[] = "asd";
  const char b[] = "asdc";
  const char c[] = "fgh";
  const char a1[] = "asd";

  cmp(a, b);
  cmp(a, c);
  cmp(a, a1);
  cmp(c, a);

  return 0;

}
