#ifndef __SELECTIONSORT_H__
#define __SELECTIONSORT_H__

#include "sort.h"
#include "comparable.h"

class SelectionSort : public Sort<IntComparable>
{
 public:
  void sort(std::vector<IntComparable> &a)
  {
    for (int i = 0; i < a.size(); i++)
    {
      int min = i;
      for (int j = i + 1; j < a.size(); j++)
      {
	if (a[j] < a[min]) min = j;
      }
      if (min != i)
	exch(a, i, min);
    }
  }
};

#endif // __SELECTIONSORT_H__
