#include "binarysearchtree.h"
#include <string>
#include <iostream>
#include "print_tree.h"
int main()
{
  BinarySearchTree<int, std::string> *bstree = new BinarySearchTree<int, std::string>();
  bstree->insert(std::pair<int, std::string>(1,"e"));
  bstree->insert(std::pair<int, std::string>(2,"c"));
  bstree->insert(std::pair<int, std::string>(3,"b"));
  bstree->insert(std::pair<int, std::string>(4,"d"));
  bstree->insert(std::pair<int, std::string>(5,"a"));
  bstree->insert(std::pair<int, std::string>(6,"g"));
  bstree->insert(std::pair<int, std::string>(7,"f"));
  bstree->ascend();
  bstree->erase(2);
  bstree->ascend();
  std::cout << "h1: " << bstree->level_height() << std::endl;
  std::cout << "h2: "
            << tree_height<
              tree_node_t<std::pair<int, std::string> >
    >(get_tree_root(*bstree))
            << std::endl;
  delete bstree;
  return 0;
}
