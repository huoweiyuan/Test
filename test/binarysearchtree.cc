#include "binarysearchtree.h"
#include <string>
int main()
{
  BinarySearchTree<int, std::string> *bstree = new BinarySearchTree<int, std::string>();
  bstree->insert(std::pair<int, std::string>(4,"e"));
  bstree->insert(std::pair<int, std::string>(2,"c"));
  bstree->insert(std::pair<int, std::string>(1,"b"));
  bstree->insert(std::pair<int, std::string>(3,"d"));
  bstree->insert(std::pair<int, std::string>(0,"a"));
  bstree->insert(std::pair<int, std::string>(6,"g"));
  bstree->insert(std::pair<int, std::string>(5,"f"));
  bstree->ascend();
  bstree->erase(2);
  bstree->ascend();
  delete bstree;
  return 0;
}
