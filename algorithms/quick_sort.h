#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__
#include "sort.h"
#include "comparable.h"
class QuickSort : public Sort<IntComparable>
{
 private:
  // 切分
  int partition(std::vector<IntComparable> &a, int lo, int hi)
  {
    int j = lo;
    while (lo < j || j < hi)
    {
      while (lo < j && a[lo] <= a[j]) lo++;
      if (lo < j)
      {
	exch(a, lo, j);
	j = lo;
      }
      while (j < hi && a[j] <= a[hi]) hi--;
      if (j < hi)
      {
	exch(a, j, hi);
	j = hi;
      }
    }
    return j;
  }
  // 递归
  void recursion_sort(std::vector<IntComparable> &a, int lo, int hi)
  {
    if (hi <= lo) return;
    int j = partition(a, lo, hi);
    recursion_sort(a, lo, j - 1);
    recursion_sort(a, j + 1, hi);
  }
  
 public:
  void sort(std::vector<IntComparable> &a)
  {
    recursion_sort(a, 0, a.size());
  }
};

#endif // __QUICK_SORT_H__
