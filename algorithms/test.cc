//#include "comparable.h"
#include "quick_sort.h"
#include "InsertSort.h"
#include "SelectionSort.h"
#include "ShellSort.h"
#include "MergeSort.h"

using namespace std;
int main()
{
  vector<IntComparable> datas = {2, 2, 1, 1, 3, 3, 10 ,3, 2, 6};
  QuickSort qs;
  qs.sort(datas);
  cout << qs.isSorted(datas) << endl;
  qs.show(datas);

  vector<IntComparable> datas1 = {2, 2, 1, 1, 3, 3, 10 ,3, 2, 6};
  InsertSort is;
  is.sort(datas1);
  cout << is.isSorted(datas1) << endl;
  is.show(datas1);

  vector<IntComparable> datas2 = {2, 2, 1, 1, 3, 3, 10 ,3, 2, 6};
  SelectionSort ss;
  ss.sort(datas2);
  cout << ss.isSorted(datas2) << endl;
  ss.show(datas2);

  vector<IntComparable> datas3 = {2, 2, 1, 1, 3, 3, 10 ,3, 2, 6};
  ShellSort ss1;
  ss1.sort(datas3);
  cout << ss1.isSorted(datas3) << endl;
  ss1.show(datas3);

  vector<IntComparable> datas4 = {2, 2, 1, 1, 3, 3, 10 ,3, 2, 6};
  MergeSort ms;
  ms.sort(datas4);
  cout << ms.isSorted(datas4) << endl;
  ms.show(datas4);
  return 0;
}
