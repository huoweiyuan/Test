#ifndef _PRINT_TREE_H_
#define _PRINT_TREE_H_
#include <stdio.h>
template<typename T>
int tree_height(const T* tree)
{
  if (tree != NULL)
  {
    int left_height = tree_height<T>(tree->left) + 1;
    int right_height = tree_height<T>(tree->right) + 1;
    return left_height > right_height ? left_height : right_height;
  }
  else
  {
    return 0;
  }
}

void print_symbol(const char &symbol, const int &count)
{
  for (int i = 0; i < count; i++)
  {
    printf("%c", symbol);
  }
}
template<typename T>
void print_tree(const T* tree_, void(&visit)(const T *))
{
  if (tree_ != nullptr)
  {
    visit(tree_);
    print_tree(tree_->left, visit);
    print_tree(tree_->right, visit);
  }
}
#endif // _PRINT_TREE_H_
