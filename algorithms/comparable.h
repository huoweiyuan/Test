#ifndef __COMPARABLE_H__
#define __COMPARABLE_H__
#include "sort.h"

class IntComparable : private Comparable<IntComparable>
{
 public:
  int data;
 public:
  bool operator==(const IntComparable &other) const
  {
    return data == other.data;
  }

  bool operator>(const IntComparable &other) const
  {
    return data > other.data;
  }

  bool operator>=(const IntComparable &other) const
  {
    return data >= other.data;
  }

  bool operator<(const IntComparable &other) const
  {
    return data < other.data;
  }

  bool operator<=(const IntComparable &other) const
  {
    return data <= other.data;
  }

  friend std::ostream& operator<<(std::ostream &out, const IntComparable &other);
};

std::ostream& operator<<(std::ostream &out, const IntComparable &other)
{
  out << other.data;
  return out;
}


#endif // __COMPARABLE_H__
