//#include "comparable.h"
#include "quick_sort.h"
//#include "sort.h"
using namespace std;
int main()
{
  QuickSort qs;
  IntComparable a,b;
  a.data = 1;
  b.data = 2;

  vector<IntComparable> datas = {a, b};
  qs.less(a, b);

  qs.show(datas);
  // IntComparable i;
  return 0;
}
