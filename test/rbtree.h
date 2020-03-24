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
    struct rb_node_struct *left;
    struct rb_node_struct *right;
  };
  class RBTree
  {
 public:
 private:
    
  };
};
#endif // _RBTREE_H_
