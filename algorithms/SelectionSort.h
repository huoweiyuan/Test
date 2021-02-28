#ifndef __SELECTIONSORT_H__
#define __SELECTIONSORT_H__

#include "sort.h"
#include "comparable.h"

class SelectionSort : public Sort<IntComparable>
{
 public:
  void sort(std::vector<IntComparable> &a)
  {
    for (int i = 1; i < a.size(); i++)
    {
      for (int j = i; j > 0; j--)
      {
	if (a[j - 1] > a[j]) exch(a, j - 1, j);
      }
    }
  }
};

#endif // __SELECTIONSORT_H__
