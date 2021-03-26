#ifndef __ALGUTIL_H__
#define __ALGUTIL_H__

#include <vector>

/*exchange a[i] and a[j]*/
template <typename T>
void exch(std::vector<T> &a, int i, int j)
{
  T t = a[i];
  a[i] = a[j];
  a[j] = t;
}

template <typename T>
void show(const std::vector<T> &a)
{
  for (unsigned i = 0; i < a.size(); i++)
  {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
}

template <typename T>
bool isSorted(const std::vector<T> &a)
{
  for (unsigned i = 1; i < a.size(); i++)
  {
    if (a[i] < a[i - 1]) return false;
  }
  return true;
}


#endif // __ALGUTIL_H__
