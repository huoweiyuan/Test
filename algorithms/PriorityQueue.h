#ifndef __PRIORITYQUEUE_H__
#define __PRIORITYQUEUE_H__

#include <vector>

#include "AlgUtil.h"

#define INITIAL_COUNTS (10)
template <typename Key>
class PriorityQueue
{
 public:
  PriorityQueue();
  PriorityQueue(int max);
  PriorityQueue(std::vector<Key> a);
  ~PriorityQueue();
 public:
  void insert(Key v);
  Key max();
  Key delMax();
  bool empty();
  int size();
 private:
  void swim(int idx);
  void sink(int idx);
 private:
  std::vector<Key> __queue;
};

template <typename Key>
PriorityQueue<Key>::PriorityQueue()
{
  __queue.reserve(INITIAL_COUNTS);
}

template <typename Key>
PriorityQueue<Key>::PriorityQueue(int max)
{
  __queue.reserve(max);
}

template <typename Key>
PriorityQueue<Key>::PriorityQueue(std::vector<Key> a)
{
  for (typename std::vector<Key>::iterator iter = a.begin();
       iter != a.end();
       iter++)
  {
    insert(*iter);
  }
}

template <typename Key>
PriorityQueue<Key>::~PriorityQueue() {}

template <typename Key>
void PriorityQueue<Key>::insert(Key v)
{
  __queue.push_back(v);
  swim(__queue.size() - 1);
}

template <typename Key>
Key PriorityQueue<Key>::max()
{
  return __queue[0];
}

template <typename Key>
Key PriorityQueue<Key>::delMax()
{
  Key key = __queue[0];
  __queue[0] = __queue.back();
  __queue.erase(__queue.end() - 1);
  sink(0);
  return key;
}

template <typename Key>
bool PriorityQueue<Key>::empty()
{
  return __queue.empty();
}

template <typename Key>
int PriorityQueue<Key>::size()
{
  return __queue.size();
}

template <typename Key>
void PriorityQueue<Key>::swim(int idx)
{
  while (idx > 0 && __queue[(idx - 1)/ 2] < __queue[idx])
  {
    exch<Key>(__queue, (idx - 1) / 2, idx);
    idx = (idx - 1) / 2;
  }
}

template <typename Key>
void PriorityQueue<Key>::sink(int idx)
{
  while ((2 * idx + 1) <= __queue.size())
  {
    int j = 2 * idx + 1;
    if (j < __queue.size() && __queue[j] < __queue[j + 1]) j++;
    if (__queue[idx] > __queue[j]) break;
    exch<Key>(__queue, idx, j);
    idx = j;
  }
}

#endif // __PRIORITYQUEUE_H__
