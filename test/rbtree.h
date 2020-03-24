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
};

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
 private:
  struct rb_node_struct<T> *root__;

  template<typename V>
  friend const struct rb_node_struct<V>* get_tree(const RBTree<V> &);
};

template<typename T>
void RBTree<T>::insert(const T &element)
{
  // TODO :
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
