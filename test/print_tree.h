#ifndef _PRINT_TREE_H_
#define _PRINT_TREE_H_
template<typename T>
int tree_height(T* tree)
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

template<typename T>
void print_tree(T* tree)
{
  
}
#endif // _PRINT_TREE_H_
