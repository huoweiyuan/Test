#ifndef _RBTREE_H_
#define _RBTREE_H_
namespace bfzq
{
enum Color {RED, BLACK};
enum RBTYPE {LLr, LRr, RRr, RLr, LLb, LRb, RRb, RLb, Other};
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
  void set_red_color(struct rb_node_struct<T>*);
  void set_black_color(struct rb_node_struct<T>*);
  bool is_red_color(struct rb_node_struct<T>*);
  bool is_black_color(struct rb_node_struct<T>*);
  RBTYPE get_u_type(struct rb_node_struct<T>*);
 private:
  struct rb_node_struct<T> *root__;

  //
  template<typename V>
  friend const struct rb_node_struct<V>* get_tree(const RBTree<V>&);
};

template<typename T>
bool RBTree<T>::is_red_color(struct rb_node_struct<T>* u)
{
  return u->color == RED;
}
template<typename T>
bool RBTree<T>::is_black_color(struct rb_node_struct<T>* u)
{
  return u->color == BLACK;
}

template<typename T>
RBTYPE RBTree<T>::get_u_type(struct rb_node_struct<T> *u)
{
  if (u->parent == nullptr || is_black_color(u->parent))
  {
    return Other;
  }
  else
  {
    struct rb_node_struct<T> *pu = u->parent;
    struct rb_node_struct<T> *gu = pu->parent;
    // 叔父是红色
    if (pu == gu->left)
    {
      struct rb_node_struct<T> *uncle = gu->right;
      if (uncle->color == RED) // LXr 型
      {
        if (pu->left == u) // LLr 型
        {
          return LLr;
        }
        else // LRr 型
        {
          return LRr;
        }
      }
      else // LXb 型
      {
        if (pu->left == u) // LLr 型
        {
          return LLb;
        }
        else // LRr 型
        {
          return LRb;
        }
      }
    }
    else
    {
      struct rb_node_struct<T> *uncle = gu->left;
      if (uncle->color == RED) // RXr 型
      {
        if (pu->left == u) // RLr 型
        {
          return RLr;
        }
        else // RRr 型
        {
          return RRr;
        }
      }
      else // RXb 型
      {
        if (pu->left == u) // RLb 型
        {
          return RLb;
        }
        else // RRb 型
        {
          return RRb;
        }
      }
    }
  }
}

template<typename T>
void RBTree<T>::insert(const T &element)
{
  struct rb_node_struct<T> *pu = nullptr, *tmp = root__;
  struct rb_node_struct<T> *u = nullptr;
  while (tmp != nullptr)
  {
    pu = tmp;
    if (element < tmp->element)
    {
      tmp = tmp->left;
      if (tmp == nullptr)
      {
        u = new struct rb_node_struct<T>();
        rb_node_init(u);
        pu->left = u;
      }
    }
    else if (element > tmp->element)
    {
      tmp = tmp->right;
      if (tmp == nullptr)
      {
        u = new struct rb_node_struct<T>();
        rb_node_init(u);
        pu->right = u;
      }
    }
    else
    {
      // element == tmp->element
      return;
    }
  }
  if (pu == nullptr) // root__ == nullptr
  {
    u = new struct rb_node_struct<T>();
    rb_node_init(u);
    // u->color = BLACK;
  }
  set_red_color(u);
  u->element = element;
  u->parent = pu;
  // TODO : change color or rotation
  root__ = rb_insert_fix(u);
}

template<typename T>
struct rb_node_struct<T>* RBTree<T>::rb_insert_fix(struct rb_node_struct<T> *u)
{
  RBTYPE type;
  while ((type = get_u_type(u)) != Other)
  {
    switch (type)
    {
      case LLr:
      case LRr:
      case RLr:
      case RRr:
        {
          break;
        }
    }
  }
  if (u->parent == nullptr) set_black_color(u);
  while (u->parent != nullptr)
    u = u->parent;
  return u;
}

template<typename T>
void RBTree<T>::set_red_color(struct rb_node_struct<T> *node)
{
  node->color = RED;
}

template<typename T>
void RBTree<T>::set_black_color(struct rb_node_struct<T> *node)
{
  node->color = BLACK;
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
