#ifndef _BTREE_H_
#define _BTREE_H_

#define BTREE_DEFAULT_M (3)

template<typename K, typename V>
class BTree
{
 public:
  BTree();
  BTree(unsigned m);
  ~BTree();

 public:
  V& find(const K &k);
  bool erase(const K &k);
  bool insert(const K &k, const V &v);

 private:

  struct btree_item_t
  {
    K k;
    V v;
  };

  struct btree_node_t
  {
    btree_item_t *btree_item_ptr;
    btree_node_t *btree_node_ptr;
    unsigned item_num;
    bool leaf;
  };

 private:
  const unsigned __m;
  btree_node_t *__root;
};

template<typename K, typename V>
BTree<K, V>::BTree() : __m(BTREE_DEFAULT_M)
{
}

template<typename K, typename V>
BTree<K, V>::BTree(unsigned m)
{
  __m = m;
}

template<typename K, typename V>
BTree<K, V>::~BTree()
{
  // TODO: free __root

}

template<typename K, typename V>
V& BTree<K, V>::find(const K &k)
{

}

#endif // _BTREE_H_
