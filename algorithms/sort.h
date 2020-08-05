#ifndef _SORT_H_
#default _SORT_H_
#include <vector>

template <typename T>
class Sort
{
 public:
  virtual void sort(vector<T> a) = 0;

  bool less(T v, T w)
  {
    return v < w;
  }

  /*exchange a[i] and a[j]*/
  void exch(vector<T> a, const int &i, const int &j)
  {
    T t = a[i];
    a[i] = a[j];
    a[j] = t;
  }

  void show(vector<T> a)
  {
    for (unsigned i = 0; i < a.size(); i++)
    {
      std::cout << a[i] << " ";
    }
    std::cout << std::endl;
  }

  bool isSort(vector<T> a)
  {
    for (unsigned i = 1; i < a.size(); i++)
    {
      if (less(a[i] < a[i - 1])) return false;
    }
    return true;
  }
};

#endif // _SORT_H_
