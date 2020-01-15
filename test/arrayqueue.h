#ifndef _ARRAY_QUEUE_H_
#define _ARRAY_QUEUE_H_
#include "queue.h"
template<typename T>
class ArrayQueue : public Queue<T>
{
public:
  ArrayQueue() : __size(0) {}
  ~ArrayQueue() {}
private:
  int __size;
  template<typename E>
  struct __queue_node_struct
  {
    E _element;
    __queue_node_struct<E> *next;
    __queue_node_struct()
    {
      next = nullptr;
    }
    __queue_node_struct(const E &element)
    {
      _element = element;
      next = nullptr;
    }
  };
  typedef struct __queue_node_struct<T> __queue_node_t;
  __queue_node_t *__head;
  __queue_node_t *__tail;
public:
  bool empty() const {return __size == 0;}
  int size() const {return __size;}
  T& front() const;
  T& back() const;
  T pop();
  void push(const T&);
};

template<typename T>
T& ArrayQueue<T>::front() const
{
  return __head->_element;
}

template<typename T>
T& ArrayQueue<T>::back() const
{
  return __tail->_element;
}

template<typename T>
T ArrayQueue<T>::pop()
{
  __queue_node_t *tmp;
  tmp = __head;
  __head = tmp->next;
  --__size;
  T t;
  t = tmp->_element;
  delete tmp;
  if (__head == nullptr)
    __tail = nullptr;
  return t;
}

template<typename T>
void ArrayQueue<T>::push(const T &element)
{
  __queue_node_t *node = new __queue_node_t(element);
  if (__head == nullptr)
  {
    __head = node;
    __tail = __head;
  }
  else
  {
    node->next = __head;
    __head = node;
  }
  ++__size;
}

#endif // _ARRAY_QUEUE_H_
