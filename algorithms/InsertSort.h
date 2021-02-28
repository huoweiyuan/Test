#ifndef __INSERTSORT_H__
#define __INSERTSORT_H__

#include "sort.h"
#include "comparable.h"

class InsertSort : public Sort<IntComparable>
{
 public:
  void sort(std::vector<IntComparable> &a)
  {
    int n = a.size();
    for (int i = 1; i < n; i++)
    {
      for (int j = i; j > 0 && a[j - 1] > a[j]; j--)
      {
	exch(a, j - 1, j);
      }
    }
  }
};

#endif // __INSERTSORT_H__
