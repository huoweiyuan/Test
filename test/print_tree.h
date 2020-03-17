#ifndef _PRINT_TREE_H_
#define _PRINT_TREE_H_
#include <stdio.h>
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

/* template<typename T> */
/* void real_print_tree(T* tree, int height) */
/* { */
/*   if (tree != NULl) */
/*   { */
/*     print_symbol(' ', 3 * height); */
/*     printf("%c", tree->element) */
    
/*   } */
/* } */

void print_symbol(const char &symbol, const int &count)
{
  for (int i = 0; i < count; i++)
  {
    printf("%c", symbol);
  }
}
template<typename T>
void print_tree(T* tree_, int size_)
{
  T* tree = tree_;
  int size = size_;
  int height = tree_height<T>(tree);
  ArrayQueue<T*> queue, print_queue;
  while (size != 0)
  {
    print_queue.push(tree);
    if (tree != nullptr)
    {
      size--;
      if (tree->left != nullptr)
      {
        queue.push(tree->left);
      }
      else
      {
        queue.push(nullptr);
      }
      if (tree->right != nullptr)
      {
        queue.push(tree->right);
      }
      else
      {
        queue.push(nullptr);
      }
    }
    tree = queue.pop();
  }
  int size2 = size_;
  do
  {
    T* tree = print_queue.pop();
    if (tree != nullptr)
    {
      size2--;
      printf("%s", tree->element.second.c_str());
    }
    else
    {
      printf("@");
    }
  }
  while (size_ != 0);
}
#endif // _PRINT_TREE_H_
