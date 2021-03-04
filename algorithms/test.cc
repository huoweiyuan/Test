//#include "comparable.h"
#include "quick_sort.h"
#include "InsertSort.h"
#include "SelectionSort.h"
#include "ShellSort.h"
#include "MergeSort.h"
#include "PriorityQueue.h"
#include "AlgUtil.h"
#include "HeapSort.h"
using namespace std;
int main()
{
  vector<IntComparable> datas = {2, 2, 1, 1, 3, 3, 10 ,3, 2, 6};

  QuickSort qs;
  qs.show(datas);
  cout << ">" << endl;

  
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


  PriorityQueue<IntComparable> pq;
  vector<IntComparable> datas5 = {2, 2, 1, 1, 3, 3, 10 ,3, 2, 6};
  vector<IntComparable>::iterator iter = datas5.begin();
  while (iter != datas5.end())
  {
    pq.insert(*iter);
    if (pq.size() > 5)
      cout << "Delete Max: " << pq.delMax() << endl;
    iter++;
  }
  vector<IntComparable> show_vector;
  while (!pq.empty()) show_vector.push_back(pq.delMax());
  show<IntComparable>(show_vector);


  vector<IntComparable> datas6 = {2, 2, 1, 1, 3, 3, 10 ,3, 2, 6};
  HeapSort hs;
  hs.sort(datas6);
  cout << hs.isSorted(datas6) << endl;
  hs.show(datas6);

  return 0;
}
