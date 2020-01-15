#ifndef _AVLTREE_H_
#define _AVLTREE_H_
#include "indexbstree.h"
template<class T>
struct binary_tree_node_strucrt
{
  T element;
  binary_tree_node_struct<T> *left, *right;
  binary_tree_node_struct()
  {
    left = right = NULL;
  }
  binary_tree_node_struct(const binary_tree_node_struct &node_)
  {
    element = node_.element;
    left = node_.left;
    right = node_.right;
  }
  binary_tree_node_struct& operator=(const binary_tree_node_struct &node_)
  {
    element = node_.element;
    left = node_.left;
    right = node_.right;
    return *this;
  }
};
typedef struct binary_tree_node_struct tree_node_t;

template<class K, class E>
class avlTree : public indexedBSTree<K, E>
{
 private:
  tree_node_t __root;
 public:
  std::pair<const K, E>* get(int) const;
};

template<class K, class E>
std::pair<const K, E>* get(int index) const
{
  
}

#endif // _AVLTREE_H_
