#include <stdio.h>
#include "avl.h"
#include "print_tree.h"
void test1()
{
  avl<char> a;
  a.insert('a');
  a.insert('b');
  a.insert('c');
  printf("%d", tree_height<avl_node_struct<char>>(get_tree(a)));
}
int main()
{
  test1();
  return 0;
}
