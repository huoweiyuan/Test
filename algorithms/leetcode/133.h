#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;
// Definition for a Node.
class Node {
 public:
  int val;
  vector<Node*> neighbors;
  Node() {
    val = 0;
    neighbors = vector<Node*>();
  }
  Node(int _val) {
    val = _val;
    neighbors = vector<Node*>();
  }
  Node(int _val, vector<Node*> _neighbors) {
    val = _val;
    neighbors = _neighbors;
  }
};

Node* cloneGraph(Node* node) {
  if (node == nullptr) {
    return nullptr;
  }

  Node *_head = new Node(node->val);
  unordered_map<Node*/* old node */, Node*/* new node */> read;
  queue<Node*> _old_node_cache;
  _old_node_cache.push(node);
  read[node] = _head;
  int count = _old_node_cache.size();
  while (count--) {
    Node *_cur = _old_node_cache.front();
    for_each(_cur->neighbors.begin(), _cur->neighbors.end(),
	     [&_old_node_cache, &_cur, &read](Node *_node) {
	       unordered_map<Node*, Node*>::iterator find = read.find(_node);
	       Node *_new_node = nullptr;
	       if (find == read.end()) {
		 _new_node = new Node(_node->val);
		 read[_node] = _new_node;
		 _old_node_cache.push(_node);
	       } else {
		 _new_node = find->second;
	       }
	       Node *_cur2new_node = read[_cur];
	       // _new_node->neighbors.push_back(_cur2new_node);
	       _cur2new_node->neighbors.push_back(_new_node);
	     });
    _old_node_cache.pop();
    if (count == 0) {
      count = _old_node_cache.size();
    }
  }
  return _head;
}

/*
bool checkEqual(const Node *lnode, const Node *rnode) {
  static unordered_set<Node*> _checked;
  if (lnode == rnode) {
    return false;
  }
  if (lnode->val != rnode->val) {
    return false;
  }
  const vector<Node*>
    &lneighbors = lnode->neighbors,
    &rneighbors = rnode->neighbors;
  vector<Node*>::const_iterator li = lneighbors.begin();
  vector<Node*>::const_iterator ri = rneighbors.begin();
  while (li != lneighbors.end() && ri != rneighbors.end()) {
    if (_checked.find(*li) == _checked.end()) {
      _checked.insert(*li);
      if (checkEqual(*li, *ri) == false) {
	return false;
      }
    }
    li++;
    ri++;
  }
  if (li != lneighbors.end() || ri != rneighbors.end()) {
    return false;
  }
  return true;
}

bool cloneGraphTest(Node *node) {
  Node *_node = cloneGraph(node);
  for
}
*/



TEST(LEETCODE, 133) {
  Node *node1 = new Node(1);
  Node *node2 = new Node(2);
  Node *node3 = new Node(3);
  Node *node4 = new Node(4);
  node1->neighbors.push_back(node2);
  node1->neighbors.push_back(node4);
  node2->neighbors.push_back(node1);
  node2->neighbors.push_back(node3);
  node3->neighbors.push_back(node2);
  node3->neighbors.push_back(node4);
  node4->neighbors.push_back(node1);
  node4->neighbors.push_back(node3);
  cloneGraph(node1);
}
