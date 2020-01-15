#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_
#include "linkedbinarytree.h"
#include "bstree.h"
#include <iostream>
template<typename K, typename E>
class BinarySearchTree : public bsTree<K, E>,
                         public LinkedBinaryTree<std::pair<K, E>>
{
 public:	
  bool empty() const;
  int size() const;
  std::pair<K, E>* find(const K&) const;
  int erase(const K&);
  void insert(const std::pair<K ,E>&);
 private:
  void __change(tree_node_t<std::pair<K, E>> *, tree_node_t<std::pair<K, E>> *);
 public:
  void ascend() const;
 private:
  static void __output(std::pair<K, E>&);
};

template<typename K, typename E>
void BinarySearchTree<K, E>::__output(std::pair<K, E> &element)
{
  std::cout << element.second << std::endl;
}

template<typename K, typename E>
void BinarySearchTree<K, E>::ascend() const
{
  this->inOrder(__output); // must qualify identifier to find this declaration in dependent base class
}

template<typename K, typename E>
bool BinarySearchTree<K, E>::empty() const
{
  return LinkedBinaryTree<std::pair<K, E>>::empty();
}

template<typename K, typename E>
int BinarySearchTree<K, E>::size() const
{
  return LinkedBinaryTree<std::pair<K, E>>::size();
}

template<typename K, typename E>
std::pair<K, E>* BinarySearchTree<K, E>::find(const K &key) const
{
  tree_node_t<std::pair<K, E>> *tree = nullptr;
  tree = LinkedBinaryTree<std::pair<K, E>>::__root;
  while (tree != nullptr)
  {
    if (tree->element.first < key)
    {
      tree = tree->right;
    }
    else if (tree->element.first > key)
    {
      tree = tree->left;
    }
    else
    {
      return &(tree->element);
    }
  }
  return nullptr;
}

template<typename K, typename E>
void BinarySearchTree<K, E>::__change(tree_node_t<std::pair<K, E>> *p_node,
                                      tree_node_t<std::pair<K, E>> *tree)
{
  tree_node_t<std::pair<K, E>> *search = tree->left;
  while (search->right != nullptr)
  {
    search = search->right;
  }
  if (search != nullptr)
  {
    if (p_node->element.first < tree->element.first)
    {

    }
    else if (p_node->element.first > tree->element.first)
    {
      
    }
    else
    {
      
    }
  }
}

template<typename K, typename E>
int BinarySearchTree<K, E>::erase(const K &key)
{
  tree_node_t<std::pair<K, E>> *tree = nullptr, *p_node = nullptr;
  p_node = tree = LinkedBinaryTree<std::pair<K, E>>::__root;
  bool left_side = false;
  while (tree != nullptr)
  {
    if (tree->element.first < key)
    {
      p_node = tree;
      tree = tree->right;
      left_side = false;
    }
    else if (tree->element.first > key)
    {
      p_node = tree;
      tree = tree->left;
      left_side = true;
    }
    else
    {
      tree_node_t<std::pair<K, E>> *p_left, *left_max;
      p_left = left_max = p_left->left;
      while (left_max->right != nullptr)
      {
        p_left = left_mex;
        left_max = left_max->right;
      }
      if (left_size == true)
      {
        p_node->left = left_max;
      }
      p_left->right = ;
      
      delete tree;
      return 1;
    }
  }
  return 0;
}

template<typename K, typename E>
void BinarySearchTree<K, E>::insert(const std::pair<K ,E> &element)
{
  tree_node_t<std::pair<K, E>> *tree = nullptr, *p_node = nullptr;
  tree = LinkedBinaryTree<std::pair<K, E>>::__root;
  while (tree != nullptr)
  {
    p_node = tree;
    if (tree->element.first < element.first)
    {
      tree = tree->right;
    }
    else if (tree->element.first > element.first)
    {
      tree = tree->left;
    }
    else
    {
      tree->element.second = element.second;
      return;
    }
  }
  tree_node_t<std::pair<K, E>> *node = nullptr;
  node = new tree_node_t<std::pair<K, E>>(element);
  if (p_node == nullptr)
  {
    LinkedBinaryTree<std::pair<K, E>>::__root = node;
  }
  else if (p_node->element.first < element.first)
  {
    p_node->right = node;
  }
  else
  {
    p_node->left = node;
  }
  LinkedBinaryTree<std::pair<K, E>>::__size++;
}
#endif // _BINARY_SEARCH_TREE_H_



























