#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
template<typename T>
class BinaryTree
{
public:
  virtual ~BinaryTree() {}
  virtual bool empty() const = 0;
  virtual int size() const = 0;
  virtual void preOrder(void (*)(T&)) const = 0;
  virtual void inOrder(void (*)(T&)) const = 0;
  virtual void postOrder(void (*)(T&)) const = 0;
  virtual void levelOrder(void (*)(T&)) const = 0;
};


#endif // _BINARY_TREE_H_
