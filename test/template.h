#include "template2.h"
template <typename T>
class Test
{
private:
  int i;
public:
  void print()
  {
    out(&i);
  }
};
