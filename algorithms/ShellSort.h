#ifndef __SHELLSORT_H__
#define __SHELLSORT_H__

#include "sort.h"
#include "comparable.h"

class ShellSort : public Sort<IntComparable>
{
 public:
  void sort(std::vector<IntComparable> &a)
  {
    int n = a.size();

    int h = 1;
    while (h < n / 3) h = 3 * n + 1;
    while (h >= 1)
    {
      for (int i = h; i < n; i++)
      {
	for (int j = i; j > h && a[j - h] > a[j]; j-=h)
	{
	  exch(a, j - h, j);
	}
      }
      h /= 3;
    }
  }
};

#endif // __SHELLSORT_H__
