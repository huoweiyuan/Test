//#include "comparable.h"
#include "quick_sort.h"
#include "InsertSort.h"
#include "SelectionSort.h"
#include "ShellSort.h"
//#include "sort.h"
using namespace std;
int main()
{
  vector<IntComparable> datas = {2, 2, 1, 1, 3, 3, 10 ,3, 2, 6};
  
  QuickSort qs;
  qs.sort(datas);
  cout << qs.isSorted(datas) << endl;
  qs.show(datas);

  InsertSort is;
  is.sort(datas);
  cout << is.isSorted(datas) << endl;
  is.show(datas);

  SelectionSort ss;
  ss.sort(datas);
  cout << ss.isSorted(datas) << endl;
  ss.show(datas);

  ShellSort ss1;
  ss1.sort(datas);
  cout << ss1.isSorted(datas) << endl;
  ss1.show(datas);
  return 0;
}
