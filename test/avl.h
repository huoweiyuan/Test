#ifndef _AVL_H_
#define _AVL_H_
#include <stdlib.h>
template<typename T>
struct avl_node_struct
{
  T element;
  unsigned int height;
  struct avl_node_struct *left;
  struct avl_node_struct *right;
};

template<typename T>
void avl_node_struct_init(avl_node_struct<T> *node)
{
  node->height = 0;
  node->left = nullptr;
  node->right = nullptr;
}
template<typename E>
class avl
{
 private:
  struct avl_node_struct<E> *root;
 public:
  int erase(const E&);
  int insert(const E&);
 private:
  struct avl_node_struct<E>* avl_insert(struct avl_node_struct<E> *tree,
                                        const E&);
};

template<typename E>
int avl<E>::erase(const E& e)
{
  return 0;
}

template<typename E>
struct avl_node_struct<E>* avl<E>::avl_insert(struct avl_node_struct<E> *tree,
                                      const E &e)
{
  if (tree == nullptr)
  {
    tree = (avl_node_struct<E>*)malloc(sizeof(avl_node_struct<E>));
    avl_node_struct_init<E>(tree);
    tree->element = e;
    return tree;
  }
  else
  {
    // TODO
  }
  return tree;
}

template<typename E>
int avl<E>::insert(const E& e)
{
  struct avl_node_struct<E> *tree = nullptr;
  tree = avl_insert(root, e);
  if (tree == nullptr)
    return -1;
  else
    root = tree;
  return 0;
}
#endif // _AVL_H_
