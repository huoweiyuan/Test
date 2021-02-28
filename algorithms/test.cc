//#include "comparable.h"
#include "quick_sort.h"
//#include "sort.h"
using namespace std;
int main()
{
  QuickSort qs;
  // IntComparable a,b;
  // a.data = 2;
  // b.data = 1;

  vector<IntComparable> datas = {2, 2, 1, 1, 3, 3, 10 ,3, 2, 6};
  // qs.less(a, b);
  qs.sort(datas);
  cout << qs.isSorted(datas) << endl;
  qs.show(datas);
  return 0;
}
