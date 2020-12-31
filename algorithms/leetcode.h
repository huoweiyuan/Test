#ifndef __LEETCODE_H__
#define __LEETCODE_H__

#include <string>
#include <vector>
using namespace std;
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
};

#endif // __LEETCODE_H__
