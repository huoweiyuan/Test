#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>
#include <assert.h>
template<typename T>
struct node_t
{
  T e;
  struct node_t *next;
};

template<typename T>
void node_init(node_t<T> *t)
{
  if (t != 0)
  {
    t.next = 0;
  }
}

template<typename T>
void node_init(node_t<T> *t, T e)
{
  if (t != 0)
  {
    t->e = e;
    t->next = 0;
  }
}

template<typename E>
struct node_head_t
{
  long long count;
  node_t<E> *next;
};


template<typename E>
void stack_init(node_head_t<E> &head)
{
  head.count = 0;
  head.next = 0;
}

template<typename E>
void stack_deinit(node_head_t<E> &head)
{
  node_t<E> *node = head.next;
  node_t<E> *next = 0;
  while (node != 0)
  {
    next = node->next;
    free(node);
    node = next;
  }
  head.next = 0;
  head.count = 0;
}

template<typename T>
void push(node_head_t<T> &head, T e)
{
  node_t<T> *node = (node_t<T>*)malloc(sizeof(node_t<T>));
  node_init(node, e);
  if (head.next != 0)
  {
    node->next = head.next;
  }
  head.next = node;
  head.count++;
}

template<typename T>
T pop(node_head_t<T> &head)
{
  assert(head.next != 0);
  node_t<T> *node = head.next;
  head.next = node->next;    
  T e;
  e = node->e;
  free(node);
  head.count--;
  return e;
}

#endif // _STACK_H_
