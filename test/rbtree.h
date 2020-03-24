#ifndef _RBTREE_H_
#define _RBTREE_H_
namespace bfzq
{
enum Color {RED, BLACK};
template<typename E>
struct rb_node_struct
{
  E element;
  Color color;
  struct rb_node_struct<E> *left;
  struct rb_node_struct<E> *right;
  struct rb_node_struct<E> *parent;
};

template<typename E>
void rb_node_init(struct rb_node_struct<E> *node)
{
  node->color = BLACK;
  node->left = nullptr;
  node->right = nullptr;
  node->parent = nullptr;
}

template<typename T>
class RBTree
{
 public:
  RBTree() : root__(nullptr) {}
  ~RBTree()
  {
    // TODO:
  }
 public:
  void insert(const T&);
  void erase(const T&);
 private:
  struct rb_node_struct<T>* rb_insert_fix(struct rb_node_struct<T>*);
 private:
  struct rb_node_struct<T> *root__;

  //
  template<typename V>
  friend const struct rb_node_struct<V>* get_tree(const RBTree<V>&);
};

template<typename T>
void RBTree<T>::insert(const T &element)
{
  struct rb_node_struct<T> *pu = nullptr, tmp = root__;
  struct rb_node_struct<T> *u = new struct rb_node_struct<T>();
  rb_node_init(u);
  while (tmp != nullptr)
  {
    pu = tmp;
    if (element < tmp->element)
    {
      tmp = tmp->left;
      if (tmp == nullptr)
        pu->left = u;
    }
    else if (element > tmp->element)
    {
      tmp = tmp->right;
      if (tmp == nullptr)
        pu->right = u;
    }
    else
    {
      // element == tmp->element
      free(u);
      return;
    }
  }
  u->parent = pu;
  if (pu == nullptr)
    root__ = u;
  else
    u->color = RED;
  // TODO : change color or rotation
  root__ = rb_insert_fix(u);
}

template<typename T>
struct rb_node_struct<T>* RBTree<T>::rb_insert_fix(struct rb_node_struct<T> *u)
{
  // TODO:
  return nullptr;
}

template<typename T>
void RBTree<T>::erase(const T &element)
{
  // TODO :
}

template<typename V>
const struct rb_node_struct<V>* get_tree(const RBTree<V> &rbtree)
{
  return rbtree.root__;
}
};
#endif // _RBTREE_H_
