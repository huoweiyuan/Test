#include <stdio.h>
#include "avl.h"
#include "print_tree.h"
void visit(const avl_node_struct<char> *tree)
{
  printf("%c\n", tree->element);
}

// test insert
void test1()
{
  Avl<char> a;
  a.insert('a');
  a.insert('b');
  a.insert('c');
  a.insert('d');
  a.insert('e');
  printf("%d\n", tree_height<avl_node_struct<char>>(get_tree(a)));
  print_tree<avl_node_struct<char>>(get_tree(a), visit);
  a.erase('c');
  printf("%d\n", tree_height<avl_node_struct<char>>(get_tree(a)));
  print_tree<avl_node_struct<char>>(get_tree(a), visit);
}

void visit2(const avl_node_struct<int> *tree)
{
  printf("%d ", tree->element);
}

// test erase
void test2()
{
  Avl<int> a;
  a.insert(3);
  a.insert(2);
  a.insert(5);
  a.insert(1);
  a.insert(4);
  a.insert(7);
  a.insert(6);
  a.insert(8);
  printf("%d\n", tree_height<avl_node_struct<int>>(get_tree(a)));
  print_tree<avl_node_struct<int>>(get_tree(a), visit2);
  printf("\n");
  a.erase(4);
  printf("%d\n", tree_height<avl_node_struct<int>>(get_tree(a)));
  print_tree<avl_node_struct<int>>(get_tree(a), visit2);
  printf("\n");
  a.erase(7);
  printf("%d\n", tree_height<avl_node_struct<int>>(get_tree(a)));
  print_tree<avl_node_struct<int>>(get_tree(a), visit2);
  printf("\n");
  a.erase(3);
  printf("%d\n", tree_height<avl_node_struct<int>>(get_tree(a)));
  print_tree<avl_node_struct<int>>(get_tree(a), visit2);
  printf("\n");
}

void test3()
{
  Avl<int> a;
  a.insert(3);
  a.insert(2);
  a.insert(1);
  a.insert(6);
  a.insert(5);
  a.insert(8);
  a.erase(3);
  printf("%d\n", tree_height<avl_node_struct<int>>(get_tree(a)));
  print_tree<avl_node_struct<int>>(get_tree(a), visit2);
  printf("\n");

}
int main()
{
  // test1();
  test3();
  return 0;
}
