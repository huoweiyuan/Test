#ifndef _AVL_H_
#define _AVL_H_

template<typename T>
struct tree_node_struct
{
  T element;
  int bf;
  struct tree_node_struct *left;
  struct tree_node_struct *right;
};

template<typename E>
class avl
{
private:
  struct tree_node_struct<E> *root;
public:
  int erase(const E&);
  void insert(const E&);
};

template<typename E>
int avl<E>::erase(const E& e)
{
  return 0;
}

template<typename E>
void avl<E>::insert(const E& e)
{
  
}
#endif // _AVL_H_
