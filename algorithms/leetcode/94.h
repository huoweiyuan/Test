#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

namespace LC94
{
  struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

  class Solution {
    private:
      void inorderTraversalReal(TreeNode *root, vector<int> &result) {
        if (root == nullptr) {
          return;
        }
        inorderTraversalReal(root->left, result);
        result.push_back(root->val);
        inorderTraversalReal(root->right, result);
      }
    public:
      vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorderTraversalReal(root, result);
        return result;
      }
  };
  
  TEST(LEETCODE, 94) {
    TreeNode *test1 
      = new TreeNode(1, nullptr, new TreeNode(2, new TreeNode(3, nullptr, nullptr), nullptr));
    vector<int> ansower = {1,3,2};
    EXPECT_EQ(ansower, Solution{}.inorderTraversal(test1));
  }
}
