#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_
#include <utility>
template<class K, class E>
class dictionary
{
public:
  virtual ~dictionary() {}
  virtual bool empty() const = 0;
  virtual int size() const = 0;
  virtual std::pair<K, E>* find(const K&) const = 0;
  virtual int erase(const K&) = 0;
  virtual void insert(const std::pair<K, E>&) = 0;
};
#endif // _DICTIONARY_H_
