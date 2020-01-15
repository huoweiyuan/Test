#ifndef _BSTREE_H_
#define _BSTREE_H_
#include "dictionary.h"
template<class K, class E>
class bsTree : public dictionary<K, E>
{
public:
  virtual void ascend() const = 0;
};
#endif // _BSTREE_H_
