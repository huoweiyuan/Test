#ifndef __BUCKETSORT_H__
#define __BUCKETSORT_H__

#include "sort.h"
#include "comparable.h"

class BucketSort : public Sort<IntComparable>
{
 private:
  std::vector<IntComparable> __data;
 public:
  BucketSort() = delete;
  BucketSort(int n)
  {
    __data.resize(n);
  }
 public:
  void sort(std::vector<IntComparable> &a)
  {
    for (IntComparable i : a)
    {
      __data[i.data].data++;
    }
    a.clear();
    for (int i = 0; i < __data.size(); i++)
    {
      for (int j = 0; j < __data[i].data; j++)
      {
	a.push_back(i);
      }
    }
  }
};

#endif // __BUCKETSORT_H__
