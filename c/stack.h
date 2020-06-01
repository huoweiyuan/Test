#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>
#include <assert.h>

template<typename T>
class Stack
{  
 private:
  struct node_t
  {
    T e;
    struct node_t *next;
  };

  void node_init(node_t *t)
  {
    if (t != NULL)
    {
      t.next = NULL;
    }
  }

  void node_init(node_t *t, T e)
  {
    if (t != NULL)
    {
      t->e = e;
      t->next = NULL;
    }
  }

  struct node_head_t
  {
    long long count;
    node_t *next;
  };

  void head_init(node_head_t *head)
  {
    if (head == NULL) return;
    head->count = 0;
    head->next = NULL;
  }

  void head_deinit(node_head_t *head)
  {
    if (head == NULL) return;
    node_t *node = head->next;
    node_t *next = NULL;
    while (node != NULL)
    {
      next = node->next;
      free(node);
      node = next;
    }
    head->next = NULL;
    head->count = 0;
  }

 public:
  Stack()
  {
    __head = (node_head_t*)malloc(sizeof(node_head_t));
    head_init(__head);
  }

  ~Stack()
  {
    head_deinit(__head);
    free(__head);
  }

 public:  
  void push(T e)
  {
    node_t *node = (node_t*)malloc(sizeof(node_t));
    node_init(node, e);
    if (__head->next != NULL)
    {
      node->next = __head->next;
    }
    __head->next = node;
    __head->count++;
  }

  T pop()
  {
    assert(__head->next != NULL);
    node_t *node = __head->next;
    __head->next = node->next;    
    T e;
    e = node->e;
    free(node);
    __head->count--;
    return e;
  }
 private:
  node_head_t *__head;
};

#endif // _STACK_H_
