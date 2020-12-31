#include "leetcode.h"
#include <gtest/gtest.h>

TEST(LEETCODE, maxSubArray0)
{
  Leetcode leetcode;
  vector<int> input = {-2,1,-3,4,-1,2,1,-5,4};
  int result = 6;
  EXPECT_EQ(result, leetcode.maxSubArray(input));
}

TEST(LEETCODE, climbStairs0)
{
  Leetcode leetcode;
  EXPECT_EQ(2,leetcode.climbStairs(2));
  EXPECT_EQ(3,leetcode.climbStairs(3));
}


TEST(LEETCODE, maxProfit0)
{
  Leetcode leetcode;
  vector<int> input0 = {7,1,5,3,6,4};
  EXPECT_EQ(5, leetcode.maxProfit(input0));
  vector<int> input1 = {7,6,4,3,1};
  EXPECT_EQ(0, leetcode.maxProfit(input1));
  
}

TEST(LEETCODE, maxProfit1)
{
  Leetcode leetcode;
  vector<int> input0 = {3,3,5,0,0,3,1,4};
  EXPECT_EQ(6, leetcode.maxProfit1(input0));
  vector<int> input1 = {1,2,3,4,5};
  EXPECT_EQ(4, leetcode.maxProfit1(input1));
  vector<int> input2 = {7,6,4,3,1};
  EXPECT_EQ(0, leetcode.maxProfit1(input2));
}
// ====
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}
