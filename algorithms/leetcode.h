#ifndef __LEETCODE_H__
#define __LEETCODE_H__

#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

struct ListNode
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};


struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x , TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Leetcode
{
 public:
  /*

   */
  // std::string longestPalindrome(std::string s);

  /**
     给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

     示例:

     输入: [-2,1,-3,4,-1,2,1,-5,4]
     输出: 6
     解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。

     进阶:

     如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的分治法求解。

     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/maximum-subarray
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
  */
  int maxSubArray(vector<int>& nums)
  {
    if (nums.empty()) return 0;
    int max, tmp_max;
    max = tmp_max = nums[0];
    for (int i = 1; i < nums.size(); i++)
    {
      int tmp = nums[i] + tmp_max;
      if (nums[i] <= tmp) tmp_max = tmp;
      else
	tmp_max = nums[i];
      if (max < tmp_max) max = tmp_max;
    }
    return max;
  }

  int climbStairs(int n)
  {
    int max1 = 1;
    int max2 = 2;
    if (n == 2) return max2;
    if (n == 1) return max1;
    for (int i = 3; i <= n; i++)
    {
      int tmp = max2;
      max2 = max2 + max1;
      max1 = tmp;
    }
    return max2;
  }

  /*

    给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

    如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。

    注意：你不能在买入股票前卖出股票。

     

    示例 1:

    输入: [7,1,5,3,6,4]
    输出: 5
    解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
    注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
    示例 2:

    输入: [7,6,4,3,1]
    输出: 0
    解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
  */
  int maxProfit(vector<int> &prices)
  {
    int max = 0;
    int buy_idx = 0;
    for (int i = 1; i < prices.size(); i++)
    {
      int tmp = prices[i] - prices[buy_idx];
      if(tmp <= 0) buy_idx = i;
      else if (tmp > max) max = tmp;
    }
    return max;
  }

  /*
    给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。

    设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。

    注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

    示例 1:

    输入: [3,3,5,0,0,3,1,4]
    输出: 6
    解释: 在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
    随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。

    示例 2:

    输入: [1,2,3,4,5]
    输出: 4
    解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。   
    注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。   
    因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。

    示例 3:

    输入: [7,6,4,3,1] 
    输出: 0 
    解释: 在这个情况下, 没有交易完成, 所以最大利润为 0。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
  */

  int maxProfit1(vector<int> &prices)
  {
    int max = 0;
    vector<int> max_arr(prices.size(), 0);
    int sell_idx = prices.size() - 1;
    for (int mid_idx = prices.size() - 1; 0 <= mid_idx; mid_idx--)
    {
      int tmp = prices[sell_idx] - prices[mid_idx];
      if(tmp <= 0)
      {
	sell_idx = mid_idx;
      }
      else if (tmp > max)
      {
	max = tmp;	
      }
      max_arr[mid_idx] = max;
    }
    int max1 = 0;
    max = 0;
    int buy_idx = 0;
    for (int mid_idx = 0; mid_idx < prices.size(); mid_idx++)
    {
      int tmp = prices[mid_idx] - prices[buy_idx];
      if(tmp <= 0) buy_idx = mid_idx;
      else if (tmp > max1) max1 = tmp;
      if (max1 + max_arr[mid_idx] > max) max = max1 + max_arr[mid_idx];
    }
    return max;
  }

  // int maxProfit1(vector<int> &prices)
  // {
  //   if (prices.size() == 0) return 0;
  //   vector<vector<int>> dp(prices.size(), vector<int>(5, 0));
  //   dp[0][0] = 0;
  //   dp[0][1] = -prices[0];
  //   dp[0][3] = -prices[0];
  //   for (int i = 1; i < prices.size(); i++) {
  //     dp[i][0] = dp[i - 1][0];
  //     dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
  //     dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + prices[i]);
  //     dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]);
  //     dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + prices[i]);
  //   }
  //   return dp[prices.size() - 1][4];

  // }


  /*
    给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。

    有效字符串需满足：

    左括号必须用相同类型的右括号闭合。
    左括号必须以正确的顺序闭合。

    注意空字符串可被认为是有效字符串。

    示例 1:

    输入: "()"
    输出: true

    示例 2:

    输入: "()[]{}"
    输出: true

    示例 3:

    输入: "(]"
    输出: false

    示例 4:

    输入: "([)]"
    输出: false

    示例 5:

    输入: "{[]}"
    输出: true

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/valid-parentheses
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
  */
  bool isValid(string s)
  {
    stack<char> brackets;
    for (int i = 0; i < s.length(); i++)
    {
      if (brackets.empty()) brackets.push(s[i]);
      else if (brackets.top() == s[i] - 1 ||
	       brackets.top() == s[i] - 2)
      {
	brackets.pop();
      }
      else
      {
	brackets.push(s[i]);
      }
    }
    return brackets.empty();
  }

  /*
    将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

 

    示例：

    输入：1->2->4, 1->3->4
    输出：1->1->2->3->4->4

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/merge-two-sorted-lists
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
  */

  /**
   * Definition for singly-linked list.
   * struct ListNode {
   *     int val;
   *     ListNode *next;
   *     ListNode() : val(0), next(nullptr) {}
   *     ListNode(int x) : val(x), next(nullptr) {}
   *     ListNode(int x, ListNode *next) : val(x), next(next) {}
   * };
   */
  ListNode* mergeTwoList(ListNode *l1, ListNode *l2)
  {
    ListNode *head, *end, *t1, *t2;
    t1 = l1;
    t2 = l2;
    head = end = nullptr;
    while (t1 != nullptr && t2 != nullptr)
    {
      if (t1->val < t2->val)
      {
	if (head == nullptr)
	{
	  end = head = new ListNode(t1->val);
	}
	else
	{
	  end->next = new ListNode(t1->val);
	  end = end->next;
	}
	t1 = t1->next;
      }
      else
      {
	if (head == nullptr)
	{
	  end = head = new ListNode(t2->val);
	}
	else
	{
	  end->next = new ListNode(t2->val);
	  end = end->next;
	}
	t2 = t2->next;
      }
    }

    while (t1 != nullptr)
    {
      if (head == nullptr)
      {
	end = head = new ListNode(t1->val);
      }
      else
      {
	end->next = new ListNode(t1->val);
	end = end->next;
      }
      t1 = t1->next;
      
    }

    while (t2 != nullptr)
    {
      if (head == nullptr)
      {
	end = head = new ListNode(t2->val);
      }
      else
      {
	end->next = new ListNode(t2->val);
	end = end->next;
      }
      t2 = t2->next;
            
    }
    return head;
  }

  /*
    给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。

    注意：答案中不可以包含重复的三元组。

 

    示例：

    给定数组 nums = [-1, 0, 1, 2, -1, -4]，

    满足要求的三元组集合为：
    [
    [-1, 0, 1],
    [-1, -1, 2]
    ]


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/3sum
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
   */
  /// 双指针法
  vector<vector<int>> threeSum(vector<int>& nums)
  {
    vector<vector<int>> out;
    /// skip input size < 3
    if (nums.size() < 3) 
      return out;
    sort(nums.begin(), nums.end());
    // for(auto p : nums)
    //   cout << p << endl;

    for (int i = 0; i < nums.size() - 2; i++)
    {
      if (nums[i] > 0) break;
      if (i > 0 && nums[i] == nums[i - 1]) continue;
      int r = nums.size() - 1;      
      int l = i + 1;
      while (l < r)
      {
	if (l >= r) break;
	if (nums[i] + nums[l] > 0) break;
	int tmp = nums[i] + nums[l] + nums[r];
	if (tmp > 0)
	{
	  r--;
	}
	else if (tmp < 0)
	{
	  l++;
	}
	else
	{
	  out.push_back({nums[i], nums[l], nums[r]});
	  while (l < r && nums[l] == nums[l + 1]) l++;
	  while (l < r && nums[r] == nums[r - 1]) r--;

	  l++;
	  r--;
	}
      }
    }
    // for(auto p : out)
    // {
    //   cout << "{";
    //   for (auto p2 : p)
    // 	cout << p2 << ",";
    //   cout << "},";
    // }
    return out;
  }

  /*
    110, 平衡二叉树
    找出左右子树高度差不超过1的树
   */
  bool isBalanced(TreeNode *root, int &hight)
  {
    if (root == nullptr) return true;
    int left_hight, right_hight, balance;
    left_hight = right_hight = 0;

    if (root->left != nullptr)
      if (isBalanced(root->left, left_hight) != true) return false;

    if (root->right != nullptr)
      if (isBalanced(root->right, right_hight) != true) return false;

    hight = left_hight > right_hight? left_hight + 1: right_hight + 1;
    
    balance = left_hight - right_hight;
    if (balance < -1 || balance > 1)
      return false;
    return true;
  }
  
  bool isBalanced(TreeNode *root)
  {
    int hight = 0;
    return isBalanced(root, hight);
  }
  
  int threeSumClosest(vector<int> &nums, int target)
  {
    int ret = 0;
    int min = INT_MAX;
    ///    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 2; i++)
    {
      for (int j = i + 1; j < nums.size() - 1; j++)
      {
	for (int k = j + 1; k < nums.size(); k++)
	{
	  int tmp = nums[i] + nums[j] + nums[k];
	  int min1 = abs(tmp - target);
	  if (min1 < min)
	  {
	    min = min1;
	    ret = tmp;
	  }
	}
      }
    }
    return ret;
  }

  /*
    94. 二叉树的中序遍历

    给定树的跟节点，返回其中序遍历
    1. root = [1, null, 2, 3]
    out = [1,3,2]
    
    2. root = []
    out = []

    3. root = [1]
    out = [1]

    4. root = [1, 2]
    out = [2, 1]

    5. root = [1, null, 2]
    out = [1, 2]

    简单模式:递归，进阶模式：迭代算法
   */
  vector<int> midprint(vector<int> tree)
  {
    
  }

};

#endif // __LEETCODE_H__
