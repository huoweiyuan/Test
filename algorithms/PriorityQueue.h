#ifndef __PRIORITYQUEUE_H__
#define __PRIORITYQUEUE_H__

#include <vector>

template <typename Key>
class PriorityQueue
{
 public:
  PriorityQueue();
  PriorityQueue(int max);
  PriorityQueue(std::vector<Key> a);
  ~PriorityQueue();
 public:
  void Insert(Key v);
  Key max();
  Key delMax();
  bool empty();
  int size();
};

template <typename Key>
PriorityQueue::PriorityQueue()
{
  
}

template <typename Key>
PriorityQueue::PriorityQueue(int max)
{
  
}

template <typename Key>
PriorityQueue::PriorityQueue(std::vector<Key> a)
{
  
}

template <typename Key>
PriorityQueue::~PriorityQueue()
{
  
}

template <typename Key>
void PriorityQueue::insert(Key v)
{
  
}

template <typename Key>
Key PriorityQueue::max()
{
  
}


template <typename Key>
Key PriorityQueue::delMax()
{
  
}

template <typename Key>
bool PriorityQueue::empty()
{
  
}

template <typename Key>
int PriorityQueue::size()
{
  
}





#endif // __PRIORITYQUEUE_H__
