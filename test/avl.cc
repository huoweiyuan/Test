#include <stdio.h>
#include "avl.h"
#include "print_tree.h"
void visit(const avl_node_struct<char> *tree)
{
  printf("%c\n", tree->element);
}
void test1()
{
  avl<char> a;
  a.insert('a');
  a.insert('b');
  a.insert('c');
  printf("%d\n", tree_height<avl_node_struct<char>>(get_tree(a)));
  print_tree<avl_node_struct<char>>(get_tree(a), visit);
}
int main()
{
  test1();
  return 0;
}
