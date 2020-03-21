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
class Avl
{
 private:
  struct avl_node_struct<E> *root;
 public:
  Avl():root(nullptr) {}
  ~Avl() {}
 public:
  void erase(const E&);
  int insert(const E&);
 private:
  int balance_factor(const struct avl_node_struct<E>*);
  struct avl_node_struct<E>* pop_least_node(struct avl_node_struct<E>**);
  struct avl_node_struct<E>* avl_insert(struct avl_node_struct<E> *, const E&);
  struct avl_node_struct<E>* avl_erase(struct avl_node_struct<E> *, const E&);
 private:
  struct avl_node_struct<E>* left_left_rotation(struct avl_node_struct<E>*);
  struct avl_node_struct<E>* right_right_rotation(struct avl_node_struct<E>*);
  struct avl_node_struct<E>* left_right_rotation(struct avl_node_struct<E>*);
  struct avl_node_struct<E>* right_left_rotation(struct avl_node_struct<E>*);
  // friend
  template<typename T>
  friend const struct avl_node_struct<T>* get_tree(const Avl<T>&);
};

#define HEIGHT(p) (p == nullptr ? 0 : ((avl_node_struct<E>*)p)->height)
#define MAX(a, b) (a > b ? a : b)

template<typename E>
struct avl_node_struct<E>* Avl<E>::pop_least_node(struct avl_node_struct<E>** tree)
{
  struct avl_node_struct<E> *least_node = nullptr;
  if (*tree == nullptr)
    return nullptr;
  if ((*tree)->left == nullptr)
  {
    // least node is root of right tree
    least_node = *tree;
    *tree = least_node->right;
    return least_node; // return struct avl_node_struct<E>*
  }
  else
  {
    least_node = pop_least_node(&((*tree)->left));
    if ((*tree)->left == least_node)
    {
      // Let least's right child be tree's left child
      (*tree)->left = least_node->right;
    }
  }

  // calculate tree's height
  if ((*tree)->left == nullptr && (*tree)->right == nullptr)
    (*tree)->height = 0;
  else
    (*tree)->height = MAX(HEIGHT((*tree)->left), HEIGHT((*tree)->right)) + 1;

  // calculate rotation
  int bf = balance_factor(*tree);
  //rotation
  if (bf == -2)
  {
    if ((*tree)->right->right != nullptr) // RR rotation
    {
      *tree = right_right_rotation(*tree);
    }
    else // LR rotation
    {
      *tree = left_right_rotation(*tree);
    }
  }
  else if (bf == 2)
  {
    if ((*tree)->left->left != nullptr) // RR rotation
    {
      *tree = right_right_rotation(*tree);
    }
    else // LR rotation
    {
      *tree = left_right_rotation(*tree);
    }
  }
  return least_node;
}

template<typename E>
int Avl<E>::balance_factor(const struct avl_node_struct<E> *tree)
{
  unsigned int left_height = 0, right_height = 0;
  if (tree->left == nullptr)
  {
    left_height = 0;
  }
  else
  {
    left_height = tree->left->height + 1;
  }
  if (tree->right == nullptr)
  {
    right_height = 0;
  }
  else
  {
    right_height = tree->right->height + 1;
  }
  return left_height - right_height;
}

template<typename T>
const struct avl_node_struct<T>* get_tree(const Avl<T> &avl_tree)
{
  return avl_tree.root;
}

template<typename E>
struct avl_node_struct<E>* Avl<E>::avl_erase(struct avl_node_struct<E> *tree,
                                             const E &e)
{
  if (tree == nullptr)
    return nullptr;
  struct avl_node_struct<E> *ret_tree = nullptr;
  if (e < tree->element)
  {
    // into left tree
    tree->left = avl_erase(tree->left, e);
    ret_tree = tree;
  }
  else if (e > tree->element)
  {
    // into right tree
    tree->right = avl_erase(tree->right, e);
    ret_tree = tree;
  }
  else
  {
    // found element
    if (tree->left == nullptr)
    {
      // left tree is empty
      ret_tree = tree->right;
      // tree->right = nullptr;
    }
    else if (tree->right == nullptr)
    {
      // right tree is empty
      ret_tree = tree->left;
    }
    else
    {
      // left tree is note empty, neither dose right tree
      // find least node info right tree
      struct avl_node_struct<E> *least_right_node = pop_least_node(&(tree->right));
      least_right_node->left = tree->left;
      least_right_node->right = tree->right;
      ret_tree = least_right_node;
    }
    // TODO : free tree node
  }
  // calcaulate tree's height
  if (tree->left == nullptr && tree->right == nullptr)
    tree->height = 0;
  else
    tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
  // calculate balance factor
  int bf = balance_factor(tree);
  if (bf == -2)
  {
    // RR or RL rotation
    if (ret_tree->right->right != nullptr) // RR
    {
      ret_tree = right_right_rotation(ret_tree);
    }
    else // RL
    {
      ret_tree = right_left_rotation(ret_tree);
    }
  }
  else if (bf == 2)
  {
    // LL or LR rotation
    if (ret_tree->left->left != nullptr) // LL
    {
      ret_tree = left_left_rotation(ret_tree);
    }
    else // LR
    {
      ret_tree = right_right_rotation(ret_tree);
    }
  }
  return ret_tree;
}

template<typename E>
void Avl<E>::erase(const E& e)
{
  root = avl_erase(root, e);
}

// LL型不平衡
template<typename E>
struct avl_node_struct<E>* Avl<E>::left_left_rotation(struct avl_node_struct<E> *tree)
{
  struct avl_node_struct<E> *root = tree->left;
  tree->left = root->right;
  root->right = tree;
  tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
  root->height = MAX(HEIGHT(root->left), HEIGHT(root->right)) + 1;
  return root;
}

// RR型不平衡
template<typename E>
struct avl_node_struct<E>* Avl<E>::right_right_rotation(
  struct avl_node_struct<E> *tree
                                                        )
{
  struct avl_node_struct<E> *root = tree->right;
  tree->right = root->left;
  root->left = tree;
  tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
  root->height = MAX(HEIGHT(root->left), HEIGHT(root->right)) + 1;
  return root;
}

// LR型不平衡
template<typename E>
struct avl_node_struct<E>* Avl<E>::left_right_rotation(struct avl_node_struct<E> *tree)
{
  tree->left = right_right_rotation(tree->left);
  return left_left_rotation(tree);
}

// RL型不平衡
template<typename E>
struct avl_node_struct<E>* Avl<E>::right_left_rotation(struct avl_node_struct<E> *tree)
{
  tree->right = left_left_rotation(tree->left);
  return right_right_rotation(tree);
}

template<typename E>
struct avl_node_struct<E>* Avl<E>::avl_insert(struct avl_node_struct<E> *tree,
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
    if (balance_factor(tree) == 2)
    {
      if (e < tree->left->element) // 小于左子树，毕进入其左子树
      {
        tree = left_left_rotation(tree);
      }
      else
      {
        tree = left_right_rotation(tree);
      }
    }
  }
  else if (e > tree->element)
  {
    tree->right = avl_insert(tree->right, e);
    // 判断平衡因子
    if (balance_factor(tree) == -2)
    {
      if (e > tree->right->element) // 大于右子树，毕进入其右子树
      {
        tree = right_right_rotation(tree);
      }
      else
      {
        tree = right_left_rotation(tree);
      }
    }
  }
  else
  {
    return nullptr;
  }
  tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
  return tree;
}

template<typename E>
int Avl<E>::insert(const E& e)
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
