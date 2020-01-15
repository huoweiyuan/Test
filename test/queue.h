#ifndef _QUEUE_H_
#define _QUEUE_H_

template<typename T>
class Queue
{
public:
  virtual ~Queue() {}
  virtual bool empty() const = 0;
  virtual int size() const = 0;
  virtual T& front() const = 0;
  virtual T& back() const = 0;
  virtual T pop() = 0;
  virtual void push(const T&) = 0;
};

#endif // _QUEUE_H_
