#include <stdio.h>
#include "rbtree.h"
#include "print_tree.h"

using bfzq::rb_node_struct;
using bfzq::RBTree;

void visit1(const rb_node_struct<double> *tree)
{
  printf(".element=%f .color=%s\n",
         tree->element, tree->color == bfzq::RED ? "RED" : "BLACK");
}

void test1()
{
  printf("test1\n");
  RBTree<double> *test =
    new RBTree<double>();
  test->insert(3);
  test->insert(2);
  test->insert(1);
  test->insert(0);
  test->insert(0.5);
  test->insert(2.5);
  test->insert(4);
  test->insert(5);
  test->insert(6);
  test->erase(6);
  // test->insert(4);
  print_tree<rb_node_struct<double>>(get_tree(*test), visit1);
  printf("\n");
  delete test;
}

int main()
{
  test1();
  return 0;
}
