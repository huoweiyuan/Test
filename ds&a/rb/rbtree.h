#ifndef _RBTREE_H_
#define _RBTREE_H_
namespace bfzq
{
  enum Color {RED = 0, BLACK = 1};
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
      // TODO: free
    }
  public:
    void insert(const T&);
    void erase(const T&);
  private:
    struct rb_node_struct<T>* rb_insert_fix(struct rb_node_struct<T>*);
    // struct rb_node_struct<T>* rb_set_color(struct rb_node_struct<T>*, RBTYPE);
    struct rb_node_struct<T>* left_left_rotation(struct rb_node_struct<T>*);
    struct rb_node_struct<T>* left_right_rotation(struct rb_node_struct<T>*);
    struct rb_node_struct<T>* right_right_rotation(struct rb_node_struct<T>*);
    struct rb_node_struct<T>* right_left_rotation(struct rb_node_struct<T>*);
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

  // template<typename T>
  // struct rb_node_struct<T>* RBTree<T>::rb_set_color(struct rb_node_struct<T>* u,
  //                                                   RBTYPE type)
  // {

  // }

  template<typename T>
  struct rb_node_struct<T>* RBTree<T>::left_left_rotation(struct rb_node_struct<T> *u)
  {
    // LLb型不平衡
    struct rb_node_struct<T> *root = u->left;
    root->parent = u->parent;
    if (root->parent != nullptr)
      root->parent->left == u ?
        root->parent->left = root : root->parent->right = root;
    if (root->right != nullptr)
    {
      u->left = root->right;
      u->left->parent = u;
    }
    else
    {
      u->left = nullptr;
    }
    root->right = u;
    u->parent = root;
    set_black_color(root);
    set_red_color(root->left);
    set_red_color(root->right);
    return root;
  }

  template<typename T>
  struct rb_node_struct<T>* RBTree<T>::left_right_rotation(struct rb_node_struct<T> *u)
  {
    // LRb型不平衡
    return u;
  }

  template<typename T>
  struct rb_node_struct<T>* RBTree<T>::right_right_rotation(struct rb_node_struct<T> *u)
  {
    // RRb型不平衡
    struct rb_node_struct<T> *root = u->right;
    root->parent = u->parent;
    if (root->parent != nullptr)
      root->parent->left == u ?
        root->parent->left = root : root->parent->right = root;
    if (root->left != nullptr)
    {
      u->right = root->left;
      u->right->parent = u;
    }
    else
    {
      u->right = nullptr;
    }
    root->left = u;
    u->parent = root;
    set_black_color(root);
    set_red_color(root->left);
    set_red_color(root->right);
    return root;
  }

  template<typename T>
  struct rb_node_struct<T>* RBTree<T>::right_left_rotation(struct rb_node_struct<T> *u)
  {
    // RLb 型不平衡
    return u;
  }

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
    if (u->parent == nullptr || is_black_color(u->parent) || is_black_color(u))
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
        if (uncle != nullptr && uncle->color == RED) // LXr 型
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
        if (uncle != nullptr && uncle->color == RED) // RXr 型
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
    // change color or rotation
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
        // XYr
      case LLr:
      case LRr:
      {
        set_black_color(u->parent);
        set_black_color(u->parent->parent->right);
        set_red_color(u->parent->parent);
        u = u->parent->parent;
        break;
      }
      case RLr:
      case RRr:
      {
        set_black_color(u->parent);
        set_black_color(u->parent->parent->left);
        set_red_color(u->parent->parent);
        u = u->parent->parent;
        break;
      }
      // XYb
      case LLb:
      {
        u = left_left_rotation(u->parent->parent);
        break;
      }
      case LRb:
      {
        u = left_right_rotation(u->parent->parent);
        break;
      }
      case RLb:
      {
        u = right_left_rotation(u->parent->parent);
        break;
      }
      case RRb:
      {
        u = right_right_rotation(u->parent->parent);
        break;
      }
      default:
        break;
      }
    }
    // 根节点
    if (u->parent == nullptr) set_black_color(u);
    // 找到根节点
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
