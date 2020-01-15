#ifndef _CALCLULATE_H_
#define _CALCLULATE_H_
#include "linkedbinarytree.h"
inline int priority_level(char c)
{
  switch(c)
  {
  case '+':
  case '-':
  {
    return -3;
  }
  case '*':
  case '/':
  case '%':
  {
    return -2;
  }
  default:
    return 0;
  }
}
template<typename T>
class Calculate : public LinkedBinaryTree<T>
{
public:
  void build_calculate(const char*, int);
private:
  void build_calculate(tree_node_t<T> *tree, const char*, int);
};

template<typename T>
void Calculate<T>::build_calculate(const char *expression, int len)
{
  if (LinkedBinaryTree<T>::__root == nullptr)
    LinkedBinaryTree<T>::__root = new tree_node_t<T>();
  build_calculate(LinkedBinaryTree<T>::__root, expression, len);
}

template<typename T>
void Calculate<T>::build_calculate(tree_node_t<T> *tree,
                                   const char *expression, int len)
{
  if (expression[0] == '(')
  {
    int count = 0;
    for (int i = 0; i < len ; i++)
    {
      if (expression[i] == '(') count++;
      else if (expression[i] == ')')
      {
        count--;
        if (count == 0)
        {
          if (i < (len - 1))
            break;
          else
          {
            expression++;
            len -= 2;
          }
        }
      }
    }
  }

  if (len == 1)
  {
    tree->element = expression[0];
    return;
  }
  int root_index = 0;
  int level = 0, tmp_level = 0;
  int skip = 0;
  for (int i = 0; i < len; i++)
  {
    if (expression[i] == '(') skip++;
    if (skip == 0 && (tmp_level = priority_level(expression[i])) <= level
        && tmp_level != 0)
    {
      root_index = i;
      level = tmp_level;
    }
    if (expression[i] == ')') skip--;
  }
  tree->element = expression[root_index];

  int right_index = root_index + 1;
  const char *left_c = nullptr, *right_c = nullptr;
  int left_len = 0, right_len = 0;
  left_c = expression;
  left_len = root_index;
  right_c = expression + right_index;
  right_len = len - right_index;
  if (tree->left == nullptr)
    tree->left = new tree_node_t<T>();
  if (left_len != 0)
    build_calculate(tree->left, left_c, left_len);
  else
    build_calculate(tree->left, "0", 1);
  if (tree->right == nullptr)
    tree->right = new tree_node_t<T>();
  build_calculate(tree->right, right_c, right_len);
}

#endif // _CALCLULATE_H_
