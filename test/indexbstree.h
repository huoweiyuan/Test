#ifndef _INDEXDSTREE_H_
#define _INDEXDSTREE_H_
#include "bstree.h"
template<class K, class E>
class indexedBSTree : public bsTree<K, E>
{
public:
  virtual std::pair<const K, E>* get(int) const = 0;
  virtual void del(int) = 0;
};
#endif // _INDEXDSTREE_H_
