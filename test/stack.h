#ifndef _STACK_H_
#define _STACK_H_
 
template<typename E>
class Stack
{
public:
  E pop();
  void push(const E&);
  bool empty() {return __size == 0;}
private:
  __stack_node_t<E> *__head;
  int __size;
private:
  template<typename T>
  struct __stack_node_struct
  {
    T _element;
    __stack_node_struct<T> *next;
    __stack_node_struct()
    {
      next = NULL;
    }
    __stack_node_struct(const T &element)
    {
      _element = element;
      next = NULL;
    }
  };
  typedef struct __stack_node_struct __stack_node_t;
};

// It is undefined if stack is empty
template<typename E>
E Stack::pop()
{
  __stack_node_t<E> *tmp;
  tmp = __head;
  __head = tmp->next;
  --__size;
  E e = tmp->_element;
  delete tmp;
  return e;
}

template<typename E>
void Stack::push(const E &element)
{
  __stack_node_t<E> *node = new __stack_node_t<E>(element);
  if (__head == NULL)
  {
    __head = node;
  }
  else
  {
    node->next = __head;
    _head = node;
  }
  ++__size;
}

#endif // _STACK_H_
