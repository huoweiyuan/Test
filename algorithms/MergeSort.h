#ifndef __MERGESORT_H__
#define __MERGESORT_H__

#include "sort.h"
#include "comparable.h"

class MergeSort : public Sort<IntComparable>
{
 private:
  std::vector<IntComparable> aux;
 private:
  void merge(std::vector<IntComparable> &a, int lo, int mi, int hi)
  {
    int l1 = lo, l2 = mi + 1;
    aux = a;
    for (int i = lo; i <= hi; i++)
    {
      if (l1 > mi) a[i] = aux[l2++];
      else if (l2 > hi) a[i] = aux[l1++];
      else
	aux[l1] < aux[l2] ? a[i] = aux[l1++] : a[i] = aux[l2++];
    }
  }

  void sort(std::vector<IntComparable> &a, int lo, int hi)
  {
    if (lo >= hi) return;
    int mi = (lo + hi) / 2;
    sort(a, lo, mi);
    sort(a, mi + 1, hi);
    merge(a,lo, mi, hi);
  }

 public:
  void sort(std::vector<IntComparable> &a)
  {
    aux.reserve(a.size());
    sort(a, 0, a.size() - 1);
  }
};

#endif // __MERGESORT_H__
