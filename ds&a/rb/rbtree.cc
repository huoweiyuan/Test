#include <stdio.h>
#include "rbtree.h"
#include "print_tree.h"

using bfzq::rb_node_struct;
using bfzq::RBTree;

void visit1(const rb_node_struct<int> *tree)
{
  printf(".element=%d .color=%s\n",
         tree->element, tree->color == bfzq::RED ? "RED" : "BLACK");
}

void test1()
{
  printf("test1\n");
  RBTree<int> *test = new RBTree<int>();
  test->insert(3);
  test->insert(2);
  test->insert(1);
  // test->insert(4);
  print_tree<rb_node_struct<int>>(get_tree(*test), visit1);
  printf("\n");
  delete test;
}

int main()
{
  test1();
  return 0;
}
