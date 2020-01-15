#include "binarysearchtree.h"
#include <string>
int main()
{
  BinarySearchTree<int, std::string> *bstree = new BinarySearchTree<int, std::string>();
  bstree->insert(std::pair<int, std::string>(0,"abc"));
  bstree->insert(std::pair<int, std::string>(1,"b"));
  bstree->insert(std::pair<int, std::string>(2,"c"));
  bstree->insert(std::pair<int, std::string>(3,"d"));
  bstree->insert(std::pair<int, std::string>(4,"e"));
  bstree->insert(std::pair<int, std::string>(5,"f"));
  bstree->insert(std::pair<int, std::string>(6,"g"));
  bstree->ascend();
  std::pair<int, std::string> *finder = bstree->find(4);
  std::cout << bstree->size() << " " << finder->second << std::endl;
  delete bstree;
  return 0;
}
