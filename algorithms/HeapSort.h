#ifndef __HEAPSORT_H__
#define __HEAPSORT_H__
#include "sort.h"
#include "comparable.h"
#include "PriorityQueue.h"

class HeapSort: public Sort<IntComparable>
{
 private:
  std::vector<IntComparable> aux;
  PriorityQueue<IntComparable> pq;
 public:
  void sort(std::vector<IntComparable> &a)
  {
    for (IntComparable item : a)
    {
      pq.insert(item);
    }
    a.clear();
    while (!pq.empty())
    {
      a.push_back(pq.delMax());
    }
  }
};

#endif // __HEAPSORT_H__
