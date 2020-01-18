#ifndef _LINKED_BINARY_TREE_H_
#define _LINKED_BINARY_TREE_H_

#include "binarytree.h"
#include "arrayqueue.h"
template<typename T>
struct tree_node_t
{
  T element;
  tree_node_t *left, *right;
  tree_node_t()
  {
    left = right = nullptr;
  }
  tree_node_t(const T &element_) : element(element_)
  {
  }

  tree_node_t(const tree_node_t &node_)
  {
    element = node_.element;
    left = node_.left;
    right = node_.right;
  }
  tree_node_t& operator=(const tree_node_t &node_)
  {
    element = node_.element;
    left = node_.left;
    right = node_.right;
    return *this;
  }
};
template<typename E>
class LinkedBinaryTree : public BinaryTree<E>
{
 public:
  bool empty() const;
  int size()  const;
  int level_height() const;
  void print_tree() const;
  void preOrder(void (*)(E&)) const;
  void inOrder(void (*)(E&)) const;
  void postOrder(void (*)(E&)) const;
  void levelOrder(void (*)(E&)) const;
 private:
  static void (*__visit)(E&);
 protected:
  tree_node_t<E> *__root;
  int __size;
 private:
  static void preOrder(tree_node_t<E>*);
  static void inOrder(tree_node_t<E>*);
  static void postOrder(tree_node_t<E>*);
  static void levelOrder(tree_node_t<E>*);
};

template<typename E>
void (*LinkedBinaryTree<E>::__visit)(E&) = nullptr;

template<typename E>
bool LinkedBinaryTree<E>::empty() const
{
  return __size == 0;
}

template<typename E>
int LinkedBinaryTree<E>::size() const
{
  return __size;
}

template<typename E>
int LinkedBinaryTree<E>::level_height() const
{
  int height = 0;
  ArrayQueue<tree_node_t<E>*> *level, *next_level, *tmp;
  level = new ArrayQueue<tree_node_t<E>*>();
  next_level = new ArrayQueue<tree_node_t<E>*>();
  if (__root != nullptr)
    level->push(__root);
  while (level->empty() != true)
  {
    while (level->empty() != true)
    {
      tree_node_t<E> *tree = level->pop();
      if (tree->left != nullptr)
        next_level->push(tree->left);
      if (tree->right != nullptr)
        next_level->push(tree->right);
    }
    tmp = level;
    level = next_level;
    next_level = tmp;
    height++;
  }
  delete level;
  delete next_level;
  return height;
}

template<typename E>
void LinkedBinaryTree<E>::print_tree() const
{
  // int height = level_hegiht();
}

template<typename E>
void LinkedBinaryTree<E>::preOrder(void (*visit)(E&)) const
{
  LinkedBinaryTree<E>::__visit = visit;
  preOrder(__root);
}

template<typename E>
void LinkedBinaryTree<E>::inOrder(void (*visit)(E&)) const
{
  LinkedBinaryTree<E>::__visit = visit;
  inOrder(__root);
}

template<typename E>
void LinkedBinaryTree<E>::postOrder(void (*visit)(E&)) const
{
  LinkedBinaryTree<E>::__visit = visit;
  postOrder(__root);
}

template<typename E>
void LinkedBinaryTree<E>::levelOrder(void (*visit)(E&)) const
{
  LinkedBinaryTree<E>::__visit = visit;
  levelOrder(__root);
}

template<typename E>
void LinkedBinaryTree<E>::preOrder(tree_node_t<E>* tree)
{
  if (tree != nullptr)
  {
    LinkedBinaryTree<E>::__visit(tree->element);
    preOrder(tree->left);
    preOrder(tree->right);
  }
}

template<typename E>
void LinkedBinaryTree<E>::inOrder(tree_node_t<E>* tree)
{
  if (tree != nullptr)
  {
    inOrder(tree->left);
    LinkedBinaryTree<E>::__visit(tree->element);
    inOrder(tree->right);
  }
}

template<typename E>
void LinkedBinaryTree<E>::postOrder(tree_node_t<E>* tree)
{
  if (tree != nullptr)
  {
    postOrder(tree->left);
    postOrder(tree->right);
    LinkedBinaryTree<E>::__visit(tree->element);
  }
}

template<typename E>
void LinkedBinaryTree<E>::levelOrder(tree_node_t<E>* tree)
{
  ArrayQueue<tree_node_t<E>*> queue;
  while (tree != nullptr)
  {
    LinkedBinaryTree<E>::__visit(tree->element);
    if (tree->left != nullptr)
      queue.push(tree->left);
    if (tree->right != nullptr)
      queue.push(tree->right);
    if (queue.empty())
    {
      tree = nullptr;
    }
    else
    {
      tree = queue.pop();
    }
  }
}

#endif // _LINKED_BINARY_TREE_H_
