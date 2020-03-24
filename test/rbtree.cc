#include <stdio.h>
#include "rbtree.h"
#include "print_tree.h"

using bfzq::rb_node_struct;
using bfzq::RBTree;

void visit1(const rb_node_struct<int> *tree)
{
  printf(".element=%d .color=%d", tree->element, tree->color);
}

void test1()
{
  printf("test1\n");
  RBTree<int> *test = new RBTree<int>();
  test->insert(3);
  test->insert(2);
  test->insert(1);
  print_tree<rb_node_struct<int>>(get_tree(*test), visit1);
  printf("\n");
  delete test;
}

int main()
{
  test1();
  return 0;
}
