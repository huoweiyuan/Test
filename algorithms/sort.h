#ifndef _SORT_H_
#define _SORT_H_
#include <vector>
#include <iostream>
template <typename T>
class Comparable
{
 public:
  virtual bool operator==(const T&) const = 0;
  virtual bool operator>(const T&) const = 0;
  virtual bool operator>=(const T&) const = 0;
  virtual bool operator<(const T&) const = 0;
  virtual bool operator<=(const T&) const = 0;
};

template <typename T>
class Sort
{
 public:
  virtual void sort(std::vector<Comparable<T> > &a) = 0;

  bool less(const Comparable<T> &v, const Comparable<T> &w) const
  {
    return v < w;
  }

  /*exchange a[i] and a[j]*/
  void exch(std::vector<Comparable<T> > &a, int i, int j)
  {
    T t = a[i];
    a[i] = a[j];
    a[j] = t;
  }

  void show(const std::vector<Comparable<T> > &a) const
  {
    for (unsigned i = 0; i < a.size(); i++)
    {
      std::cout << a[i] << " ";
    }
    std::cout << std::endl;
  }

  bool isSorted(const std::vector<Comparable<T> > &a) const
  {
    for (unsigned i = 1; i < a.size(); i++)
    {
      if (less(a[i], a[i - 1])) return false;
    }
    return true;
  }
};

#endif // _SORT_H_
