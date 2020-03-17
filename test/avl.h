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
  struct avl_node_struct<E>* left_left_rotation(struct
                                                avl_node_struct<E> *tree);
};

template<typename E>
int avl<E>::erase(const E& e)
{
  return 0;
}

template<typename E>
struct avl_node_struct<E>* avl<E>::left_left_rotation(struct avl_node_struct<E> *tree)
{
  return nullptr;
}

#define HEIGHT(p) (p == nullptr ? 0 : ((avl_node_struct<E>*)p)->height)
#define MAX(a, b) (a > b ? a : b)
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
  else if (e < tree->element)
  {
    tree->left = avl_insert(tree->left, e);
    // 判断平衡因子
    if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
    {
      if (e < tree->left->element) // 小于左子树，毕进入其左子树
      {
        // TODO: LL旋转
        tree->left = left_left_rotation(tree->left);
      }
      else
      {
        // TODO: LR旋转
        // tree->left = left_right_rotation(tree->left);
      }
    }
  }
  else if (e > tree->element)
  {
    tree->right = avl_insert(tree->right, e);
    // 判断平衡因子
    if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
    {
      if (e > tree->right->element) // 大于右子树，毕进入其右子树
      {
        // TODO: RR旋转
      }
      else
      {
        // TODO: RL旋转
      }
    }
  }
  else
  {
    return nullptr;
  }
  tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right));
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
